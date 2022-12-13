#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>

namespace Based {

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult {
  std::string Name;

  FloatingPointMicroseconds Start;
  std::chrono::microseconds ElapsedTime;
  std::thread::id ThreadID;
};

struct InstrumentationSession {
  std::string Name;
};

class Instrumentor {
private:
  std::mutex m_Mutex;
  InstrumentationSession *m_CurrentSession;
  std::ofstream m_OutputStream;

public:
  Instrumentor() : m_CurrentSession(nullptr) {}

  void BeginSession(const std::string &name,
                    const std::string &filepath = "results.json") {

    std::lock_guard lock(m_Mutex);
    if (m_CurrentSession) {
      // If there is already a current session, then close it before beginning
      // new one. Subsequent profiling output meant for the original session
      // will end up in the newly opened session instead.  That's better than
      // having badly formatted profiling output.
      if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before
                                  // Log::Init()
        BSD_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' "
                       "already open.",
                       name, m_CurrentSession->Name);
      }
      InternalEndSession();
    }
    m_OutputStream.open(filepath);

    if (m_OutputStream.is_open()) {
      m_CurrentSession = new InstrumentationSession({name});
      WriteHeader();
    } else {
      if (Log::GetCoreLogger()) {
        BSD_CORE_ERROR("Instrumentor could not open results file '{0}",
                       filepath);
      }
    }
  }

  void EndSession() {
    std::lock_guard lock(m_Mutex);
    InternalEndSession();
  }

  void WriteProfile(const ProfileResult &result) {
    std::stringstream json;

    std::string name = result.Name;
    std::replace(name.begin(), name.end(), '"', '\'');

    json << std::setprecision(3) << std::fixed << ",{"
         << "\"cat\":\"function\","
         << "\"dur\":" << (result.ElapsedTime.count()) << ","
         << "\"name\":\"" << name << "\","
         << "\"ph\":\"X\","
         << "\"pid\":0,"
         << "\"tid\":" << result.ThreadID << ","
         << "\"ts\":" << result.Start.count() << "}";
    std::lock_guard lock(m_Mutex);
    if (m_CurrentSession) {
      m_OutputStream << json.rdbuf();
      m_OutputStream.flush();
    }
  }

  static Instrumentor &Get() {
    static Instrumentor instance;
    return instance;
  }

private:
  void WriteHeader() {
    m_OutputStream << "{\"otherData\": {}, \"traceEvents\":[{}";
    m_OutputStream.flush();
  }

  void WriteFooter() {
    m_OutputStream << "]}";
    m_OutputStream.flush();
  }

  void InternalEndSession() {
    if (m_CurrentSession) {
      WriteFooter();
      m_OutputStream.close();
      delete m_CurrentSession;
      m_CurrentSession = nullptr;
    }
  }
};

class InstrumentationTimer {
public:
  InstrumentationTimer(const char *name) : m_Name(name), m_Stopped(false) {
    m_StartTimepoint = std::chrono::steady_clock::now();
  }

  ~InstrumentationTimer() {
    if (!m_Stopped)
      Stop();
  }

  void Stop() {
    auto endTimepoint = std::chrono::steady_clock::now();

    auto highResStart =
        FloatingPointMicroseconds{m_StartTimepoint.time_since_epoch()};
    auto elapsedTime =
        std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
            .time_since_epoch() -
        std::chrono::time_point_cast<std::chrono::microseconds>(
            m_StartTimepoint)
            .time_since_epoch();

    Instrumentor::Get().WriteProfile({m_Name, highResStart, elapsedTime, std::this_thread::get_id()});

    m_Stopped = true;
  }

private:
  const char *m_Name;
  std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
  bool m_Stopped;
};
} // namespace Based

#define BSD_PROFILE 0
#if BSD_PROFILE
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) ||    \
    (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define BSD_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define BSD_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define BSD_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) ||              \
    (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define BSD_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define BSD_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define BSD_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define BSD_FUNC_SIG __func__
#else
#define BSD_FUNC_SIG "BSD_FUNC_SIG unknown!"
#endif
#define BSD_PROFILE_BEGIN_SESSION(name, filepath)                              \
  ::Based::Instrumentor::Get().BeginSession(name, filepath)
#define BSD_PROFILE_END_SESSION() ::Based::Instrumentor::Get().EndSession()
#define BSD_PROFILE_SCOPE(name)                                                \
  ::Based::InstrumentationTimer timer##__LINE__(name);
#define BSD_PROFILE_FUNCTION() BSD_PROFILE_SCOPE(BSD_FUNC_SIG)
#else
#define BSD_PROFILE_BEGIN_SESSION(name, filepath)
#define BSD_PROFILE_END_SESSION()
#define BSD_PROFILE_SCOPE(name)
#define BSD_PROFILE_FUNCTION()
#endif
