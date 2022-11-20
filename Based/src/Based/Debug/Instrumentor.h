#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

#include <thread>

namespace Based {

struct ProfileResult {
  std::string Name;
  long long Start, End;
  uint32_t ThreadID;
};

struct InstrumentationSession {
  std::string Name;
};

class Instrumentor {
private:
  InstrumentationSession *m_CurrentSession;
  std::ofstream m_OutputStream;
  int m_ProfileCount;

public:
  Instrumentor() : m_CurrentSession(nullptr), m_ProfileCount(0) {}

  void BeginSession(const std::string &name,
                    const std::string &filepath = "results.json") {
    m_OutputStream.open(filepath);
    WriteHeader();
    m_CurrentSession = new InstrumentationSession{name};
  }

  void EndSession() {
    WriteFooter();
    m_OutputStream.close();
    delete m_CurrentSession;
    m_CurrentSession = nullptr;
    m_ProfileCount = 0;
  }

  void WriteProfile(const ProfileResult &result) {
    if (m_ProfileCount++ > 0)
      m_OutputStream << ",";

    std::string name = result.Name;
    std::replace(name.begin(), name.end(), '"', '\'');

    std::stringstream ss;
    ss << "{"
       << "\"cat\":\"function\","
       << "\"dur\":" << (result.End - result.Start) << ","
       << "\"name\":\"" << name << "\","
       << "\"ph\":\"X\","
       << "\"pid\":0,"
       << "\"tid\":" << result.ThreadID << ","
       << "\"ts\":" << result.Start << "}";

    m_OutputStream << ss.rdbuf();
    m_OutputStream.flush();
  }

  void WriteHeader() {
    m_OutputStream << "{\"otherData\": {}, \"traceEvents\":[";
    m_OutputStream.flush();
  }

  void WriteFooter() {
    m_OutputStream << "]}";
    m_OutputStream.flush();
  }

  static Instrumentor &Get() {
    static Instrumentor instance;
    return instance;
  }
};

class InstrumentationTimer {
public:
  InstrumentationTimer(const char *name) : m_Name(name), m_Stopped(false) {
    m_StartTimepoint = std::chrono::high_resolution_clock::now();
  }

  ~InstrumentationTimer() {
    if (!m_Stopped)
      Stop();
  }

  void Stop() {
    auto endTimepoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(
                          m_StartTimepoint)
                          .time_since_epoch()
                          .count();
    long long end =
        std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
            .time_since_epoch()
            .count();

    uint32_t threadID =
        std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::Get().WriteProfile({m_Name, start, end, threadID});

    m_Stopped = true;
  }

private:
  const char *m_Name;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
  bool m_Stopped;
};
} // namespace Based

#define BSD_PROFILE 1
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
