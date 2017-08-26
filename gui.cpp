#include "gui.h"

Board::Board(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    statusbar = parent->GetStatusBar();
    Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
}

void Board::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    for (int i = 0; i < BoardLength; i++){
        for (int j = 0; j < BoardLength; j++){
            DrawSquare(dc, i, j);
        }
    }
}

int Board::SquareLength()
{
    int width = GetClientSize().GetWidth();
    int height = GetClientSize().GetHeight();
    return std::min(width, height) / BoardLength;
}

void Board::DrawSquare(wxPaintDC& dc, int x, int y)
{
    static wxColor light = wxColor(255, 222, 173);
    static wxColor dark = wxColor(205, 133, 63);
    int boardtop = GetClientSize().GetHeight() - BoardLength * SquareLength();

    dc.SetPen(*wxTRANSPARENT_PEN);
    if (x % 2 == y % 2){
        dc.SetBrush(wxBrush(light));
    } else {
        dc.SetBrush(wxBrush(dark));
    }
    dc.DrawRectangle(x * SquareLength(), y * SquareLength(), SquareLength(), SquareLength());
}

Window::Window(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{
    wxStatusBar *sb = CreateStatusBar();
    sb->SetStatusText(wxT("White's Turn"));
    Board *board = new Board(this);
    board->SetFocus();
}