#include "gui.h"

ChessSymbol::ChessSymbol(const wxString path)
{
    dragging = false;
    img = wxImage(path, wxBITMAP_TYPE_ANY);
}

void ChessSymbol::Draw(wxDC& dc, int length)
{
    int size = length * 0.8;
    if(dragging){
        dc.DrawBitmap(
            wxBitmap(img.Scale(size, size)),
            x, y, false
        );
    } else {
        int offset = length * 0.1;
        dc.DrawBitmap(
            wxBitmap(img.Scale(size, size)),
            i * length + offset, j * length + offset, false
        );
    }
}

bool ChessSymbol::BeginMove(wxPoint pt, int length)
{
    int size = length * 0.8;
    int offset = length * 0.1;
    x = i * length + offset;
    y = j * length + offset;
    if(x <= pt.x && pt.x <= x + size && y <= pt.y && pt.y <= y + size){
        x = pt.x - size / 2;
        y = pt.y - size / 2;
        dragging = true;
        return true;
    } else {
        return false;
    }
}

void ChessSymbol::FinishMove(int length)
{
    if(dragging){
        i = (x + length / 2) / length;
        j = (y + length / 2) / length;
        dragging = false;
    }
}

void ChessSymbol::Move(wxPoint pt, int length)
{
    int size = length * 0.8;
    if(dragging){
        x = pt.x - size / 2;
        y = pt.y - size / 2;
    }
}

GUIBoard::GUIBoard(wxFrame *parent, Board *chessboard)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    board = chessboard;
    boardLength = chessboard->Length;
    statusbar = parent->GetStatusBar();
    LoadPiece();

    Connect(wxEVT_PAINT, wxPaintEventHandler(GUIBoard::OnPaint));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(GUIBoard::OnMouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(GUIBoard::OnMouseUp));
    Connect(wxEVT_MOTION, wxMouseEventHandler(GUIBoard::OnMove));
}

void GUIBoard::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    for (int i = 0; i < boardLength; i++){
        for (int j = 0; j < boardLength; j++){
            DrawSquare(dc, i, j);
        }
    }

    for (int i = 0; i < 32; i++){
        symbol[i]->Draw(dc, SquareLength());
    }
}

void GUIBoard::OnMouseDown(wxMouseEvent& event)
{
    for(int i = 0; i < 32; i++){
        if(symbol[i]->BeginMove(event.GetPosition(), SquareLength())){
            break;
        }
    }
}

void GUIBoard::OnMouseUp(wxMouseEvent& event)
{
    for(int i = 0; i < 32; i++){
        symbol[i]->FinishMove(SquareLength());
    }
    Refresh(true);
}

void GUIBoard::OnMove(wxMouseEvent& event)
{
    wxPoint pt = ScreenToClient(wxGetMousePosition());
    for(int i = 0; i < 32; i++){
        symbol[i]->Move(pt, SquareLength());
    }
    Refresh(true);
}

int GUIBoard::SquareLength()
{
    int width = GetClientSize().GetWidth();
    int height = GetClientSize().GetHeight();
    int length = std::min(width, height) / boardLength;
    return length;
}

void GUIBoard::DrawSquare(wxPaintDC& dc, int x, int y)
{
    static wxColor light = wxColor(255, 222, 173);
    static wxColor dark = wxColor(205, 133, 63);
    int boardtop = GetClientSize().GetHeight() - boardLength * SquareLength();

    dc.SetPen(*wxTRANSPARENT_PEN);
    if (x % 2 == y % 2){
        dc.SetBrush(wxBrush(light));
    } else {
        dc.SetBrush(wxBrush(dark));
    }
    dc.DrawRectangle(x * SquareLength(), y * SquareLength(),
        SquareLength(), SquareLength());
}

void GUIBoard::LoadPiece()
{
    wxString path[12] = {
        wxT("img/black_pawn.png"),
        wxT("img/black_knight.png"),
        wxT("img/black_bishop.png"),
        wxT("img/black_rook.png"),
        wxT("img/black_queen.png"),
        wxT("img/black_king.png"),
        wxT("img/white_pawn.png"),
        wxT("img/white_knight.png"),
        wxT("img/white_bishop.png"),
        wxT("img/white_rook.png"),
        wxT("img/white_queen.png"),
        wxT("img/white_king.png")
    };
    int count = 0;
    for(int i = 0; i < boardLength; i++){
        for(int j = 0; j < boardLength; j++){
            chessPiece piece = board->PieceAt(i, j);
            if(piece < 12){
                symbol[count] = new ChessSymbol(path[piece]);
                symbol[count]->PlaceAt(i, j);
                count++;
            }
        }
    }
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{
    wxStatusBar *sb = CreateStatusBar();
    sb->SetStatusText(wxT("White's Turn"));
    Board *board = new Board();
    GUIBoard *guiboard = new GUIBoard(this, board);
    guiboard->SetFocus();
}
