#include "main.h"
#include "gui.h"

IMPLEMENT_APP(ChessApp)

bool ChessApp::OnInit()
{
    Window *window = new Window(wxT("Chess"));
    window->Show(true);

    return true;
}
