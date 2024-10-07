#include "main_window.h"

namespace by = asarum::BY;

by::MainWindow::MainWindow(const wxString& title, int width, int height) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width,height))
{
    // center the window on the screen
    Centre();
}

