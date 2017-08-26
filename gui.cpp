#include "window.h"

Window::Window(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 300))
{
    wxStatusBar *sb = CreateStatusBar();
    sb->SetStatusText(wxT("White's Turn"));
}