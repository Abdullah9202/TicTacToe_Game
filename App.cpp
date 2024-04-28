#include "App.h"
#include "MainFrame.h"
#include "Header.h"

wxIMPLEMENT_APP(TicTacToeApp); // Implementing the Application

bool TicTacToeApp::OnInit()
{
    // MainFrame Implementation
    TicTacToeFrame* frame = new TicTacToeFrame("Tic Tac Toe");
    frame->Show(); // Makes MainFrame visible
    return true;
}
