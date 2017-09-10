#include <wx/wx.h>
#include "board.h"

class ChessSymbol
{
public:
    ChessSymbol(const wxString path);
    void PlaceAt(int x, int y) { boardX = x; boardY = y; }
    void Draw(wxDC& dc, int length);
    bool BeginMove(wxPoint pt);
    void FinishMove(wxPoint pt);
    void Move(wxPoint pt);
    bool isDragging() { return dragging; }
    int getBoardX() { return boardX; }
    int getBoardY() { return boardY; }
    void remove() { captured = true; }

private:
    int spacingLength;
    int symbolSize;
    int spacingOffset;
    bool dragging;
    bool captured;
    int boardX, boardY;
    int pixelX, pixelY;
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
