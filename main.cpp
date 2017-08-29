#include "main.h"
#include "gui.h"

IMPLEMENT_APP(ChessApp)

bool ChessApp::OnInit()
{
    wxInitAllImageHandlers();
    MyFrame *frame = new MyFrame(wxT("Chess"));
    frame->Show(true);

    return true;
}
