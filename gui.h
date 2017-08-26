#include <wx/wx.h>

class Board : public wxPanel
{
public:
    Board(wxFrame *parent);

protected:
    void OnPaint(wxPaintEvent& event);

private:
    enum { BoardLength = 8 };
    int SquareLength();
    void DrawSquare(wxPaintDC &dc, int x, int y);
    wxStatusBar *statusbar;
};

class Window : public wxFrame
{
public:
    Window(const wxString& title);
};
