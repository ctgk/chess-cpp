#include <wx/wx.h>
#include "board.h"

class ChessSymbol
{
public:
    ChessSymbol(const wxString path);
    void PlaceAt(int ii, int jj) { i = ii; j = jj; }
    void Draw(wxDC& dc, int length);
    bool BeginMove(wxPoint pt, int length);
    void FinishMove(int length);
    void Move(wxPoint pt, int length);

private:
    bool dragging;
    int i, j;
    int x, y;
    wxImage img;
};

class GUIBoard : public wxPanel
{
public:
    GUIBoard(wxFrame *parent, Board *chessboard);

protected:
    void OnPaint(wxPaintEvent& event);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void OnMove(wxMouseEvent& event);

private:
    int SquareLength();
    void DrawSquare(wxPaintDC &dc, int x, int y);
    void LoadPiece();
    wxStatusBar *statusbar;
    Board *board;
    int boardLength;
    ChessSymbol *symbol[32];
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
};
