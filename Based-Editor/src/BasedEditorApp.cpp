#include "EditorLayer/EditorLayer.h"
#include <Based.h>
#include <Based/Core/EntryPoint.h>

namespace Based
{
    class BasedEditor : public Application
    {
        public:
            BasedEditor() : Application( "Based Editor" ) { PushLayer( new EditorLayer() ); }

            ~BasedEditor() { }
    };

    Application* CreateApplication() { return new BasedEditor(); }
} // namespace Based
