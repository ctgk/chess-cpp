#include "panel.h"
#include <map>
#include <string>

Panel::Panel(wxFrame *parent, Board *chessboard)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    symbolPath['p'] = wxT("img/black_pawn.png");
    symbolPath['n'] = wxT("img/black_knight.png");
    symbolPath['b'] = wxT("img/black_bishop.png");
    symbolPath['r'] = wxT("img/black_rook.png");
    symbolPath['q'] = wxT("img/black_queen.png");
    symbolPath['k'] = wxT("img/black_king.png");
    symbolPath['P'] = wxT("img/white_pawn.png");
    symbolPath['N'] = wxT("img/white_knight.png");
    symbolPath['B'] = wxT("img/white_bishop.png");
    symbolPath['R'] = wxT("img/white_rook.png");
    symbolPath['Q'] = wxT("img/white_queen.png");
    symbolPath['K'] = wxT("img/white_king.png");
    board = chessboard;
    boardLength = chessboard->Length;
    statusbar = parent->GetStatusBar();
    statusbar->SetStatusText(chessboard->getFEN());
    LoadPiece();

    Connect(wxEVT_PAINT, wxPaintEventHandler(Panel::OnPaint));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Panel::OnMouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(Panel::OnMouseUp));
    Connect(wxEVT_MOTION, wxMouseEventHandler(Panel::OnMove));
}

void Panel::OnPaint(wxPaintEvent& event)
{
    statusbar->SetStatusText(board->getFEN());
    wxPaintDC dc(this);

    for (int i = 0; i < boardLength; i++){
        for (int j = 0; j < boardLength; j++){
            DrawSquare(dc, i, j);
        }
    }

    for(int i = 0; i < symbol.size(); i++){
        symbol[i]->Draw(dc, SquareLength());
    }
}

void Panel::OnMouseDown(wxMouseEvent& event)
{
    for(int i = 0; i < symbol.size(); i++){
        if(symbol[i]->BeginMove(event.GetPosition())){
            origin = board->getNotation(symbol[i]->getBoardY(), symbol[i]->getBoardX());
            break;
        }
    }
}

void Panel::OnMouseUp(wxMouseEvent& event)
{
    for(int i = 0; i < symbol.size(); i++){
        if (symbol[i]->isDragging()){
            int targetX = event.GetPosition().x / SquareLength();
            int targetY = event.GetPosition().y / SquareLength();
            std::string dest = board->getNotation(targetY, targetX);
            bool moved = board->move(origin, dest);
            symbol[i]->FinishMove(event.GetPosition(), moved);
            if(moved) LoadPiece();
            break;
        }
    }
    statusbar->SetStatusText(board->getFEN());
    Refresh(true);
}

void Panel::OnMove(wxMouseEvent& event)
{
    for(int i = 0; i < symbol.size(); i++){
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
    symbol.resize(0);
    char piece;
    for(int i = 0; i < boardLength; i++){
        for(int j = 0; j < boardLength; j++){
            piece = board->getPieceCharAt(i, j);
            if(piece != '-'){
                Symbol* sym = new Symbol(symbolPath[piece]);
                sym->PlaceAt(j, i);
                symbol.push_back(sym);
            }
        }
    }
}
