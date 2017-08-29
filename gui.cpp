#include "gui.h"

GUIBoard::GUIBoard(wxFrame *parent, Board *chessboard)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    board = chessboard;
    boardLength = chessboard->Length;
    statusbar = parent->GetStatusBar();
    LoadImage();
    Connect(wxEVT_PAINT, wxPaintEventHandler(GUIBoard::OnPaint));
}

void GUIBoard::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    for (int i = 0; i < boardLength; i++){
        for (int j = 0; j < boardLength; j++){
            DrawSquare(dc, i, j, board->PieceAt(i, j));
        }
    }
}

int GUIBoard::SquareLength()
{
    int width = GetClientSize().GetWidth();
    int height = GetClientSize().GetHeight();
    return std::min(width, height) / boardLength;
}

void GUIBoard::DrawSquare(wxPaintDC& dc, int x, int y, chessPiece piece)
{
    static wxColor light = wxColor(255, 222, 173);
    static wxColor dark = wxColor(205, 133, 63);
    int boardtop = GetClientSize().GetHeight() - boardLength * SquareLength();
    int size, pos;
    size = SquareLength() * 0.8;
    pos = SquareLength() * 0.1;

    dc.SetPen(*wxTRANSPARENT_PEN);
    if (x % 2 == y % 2){
        dc.SetBrush(wxBrush(light));
    } else {
        dc.SetBrush(wxBrush(dark));
    }
    dc.DrawRectangle(x * SquareLength(), y * SquareLength(),
        SquareLength(), SquareLength());
    if (piece < 12){
        dc.DrawBitmap(
            wxBitmap(
                img[piece].Scale(size, size)),
            x * SquareLength() + pos,
            y * SquareLength() + pos,
            false
        );
    }
}

void GUIBoard::LoadImage()
{
    img[0].LoadFile(wxT("img/black_pawn.png"), wxBITMAP_TYPE_PNG);
    img[1].LoadFile(wxT("img/black_knight.png"), wxBITMAP_TYPE_PNG);
    img[2].LoadFile(wxT("img/black_bishop.png"), wxBITMAP_TYPE_PNG);
    img[3].LoadFile(wxT("img/black_rook.png"), wxBITMAP_TYPE_PNG);
    img[4].LoadFile(wxT("img/black_queen.png"), wxBITMAP_TYPE_PNG);
    img[5].LoadFile(wxT("img/black_king.png"), wxBITMAP_TYPE_PNG);
    img[6].LoadFile(wxT("img/white_pawn.png"), wxBITMAP_TYPE_PNG);
    img[7].LoadFile(wxT("img/white_knight.png"), wxBITMAP_TYPE_PNG);
    img[8].LoadFile(wxT("img/white_bishop.png"), wxBITMAP_TYPE_PNG);
    img[9].LoadFile(wxT("img/white_rook.png"), wxBITMAP_TYPE_PNG);
    img[10].LoadFile(wxT("img/white_queen.png"), wxBITMAP_TYPE_PNG);
    img[11].LoadFile(wxT("img/white_king.png"), wxBITMAP_TYPE_PNG);
}

GUIWindow::GUIWindow(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{
    wxStatusBar *sb = CreateStatusBar();
    sb->SetStatusText(wxT("White's Turn"));
    Board *board = new Board();
    GUIBoard *guiboard = new GUIBoard(this, board);
    guiboard->SetFocus();
}
