#include "gui_main.h"
#include "main_window.h"

namespace by = asarum::BY;

// Macro created the application instance and starts it
IMPLEMENT_APP(GuiDoc)
    
bool GuiDoc::OnInit()
{
    by::MainWindow *mainWindow = new by::MainWindow(wxT("GuiApp"), 640,480);
    mainWindow->Show(true);

    return true;
}