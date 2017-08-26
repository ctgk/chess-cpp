#include "main.h"
#include "gui.h"

IMPLEMENT_APP(ChessApp)

bool ChessApp::OnInit()
{
    wxInitAllImageHandlers();
    GUIWindow *guiwindow = new GUIWindow(wxT("Chess"));
    guiwindow->Show(true);

    return true;
}
