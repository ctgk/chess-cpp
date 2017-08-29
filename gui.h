#include <wx/wx.h>
#include "board.h"

class GUIBoard : public wxPanel
{
public:
    GUIBoard(wxFrame *parent, Board *chessboard);

protected:
    void OnPaint(wxPaintEvent& event);

private:
    int SquareLength();
    void DrawSquare(wxPaintDC &dc, int x, int y, chessPiece piece);
    void LoadImage();
    wxStatusBar *statusbar;
    Board *board;
    int boardLength;
    wxImage img[12];
};

class GUIWindow : public wxFrame
{
public:
    GUIWindow(const wxString& title);
};
