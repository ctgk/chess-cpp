#include "panel.h"

Panel::Panel(wxFrame *parent, Board *chessboard)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    board = chessboard;
    boardLength = chessboard->Length;
    statusbar = parent->GetStatusBar();
    LoadPiece();

    Connect(wxEVT_PAINT, wxPaintEventHandler(Panel::OnPaint));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Panel::OnMouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(Panel::OnMouseUp));
    Connect(wxEVT_MOTION, wxMouseEventHandler(Panel::OnMove));
}

void Panel::OnPaint(wxPaintEvent& event)
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

void Panel::OnMouseDown(wxMouseEvent& event)
{
    for(int i = 0; i < 32; i++){
        if(symbol[i]->BeginMove(event.GetPosition())){
            break;
        }
    }
}

void Panel::OnMouseUp(wxMouseEvent& event)
{
    for(int i = 0; i < 32; i++){
        if (symbol[i]->isDragging()){
            symbol[i]->FinishMove(event.GetPosition());
            if(statusbar->GetStatusText() == wxT("White's Turn")){
                statusbar->SetStatusText(wxT("Black's Turn"));
            } else {
                statusbar->SetStatusText(wxT("White's Turn"));
            }
            int targetX = symbol[i]->getBoardX();
            int targetY = symbol[i]->getBoardY();

            for(int j = 0; j < 32; j++){
                if(j != i && targetX == symbol[j]->getBoardX() && targetY == symbol[j]->getBoardY()){
                    symbol[j]->remove();
                }
            }

            break;
        }
    }
    Refresh(true);
}

void Panel::OnMove(wxMouseEvent& event)
{
    for(int i = 0; i < 32; i++){
        symbol[i]->Move(ScreenToClient(wxGetMousePosition()));
    }
    Refresh(true);
}

int Panel::SquareLength()
{
    int width = GetClientSize().GetWidth();
    int height = GetClientSize().GetHeight();
    int length = std::min(width, height) / boardLength;
    return length;
}

void Panel::DrawSquare(wxPaintDC& dc, int x, int y)
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

void Panel::LoadPiece()
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
