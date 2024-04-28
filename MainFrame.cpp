#include "MainFrame.h"
#include "Header.h"

// Defining event table
wxBEGIN_EVENT_TABLE(TicTacToeFrame, wxFrame)
EVT_BUTTON(wxID_ANY, TicTacToeFrame::OnButton_Click)
wxEND_EVENT_TABLE()

// Defining the TicTacToeFrame class
TicTacToeFrame::TicTacToeFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) // Creeting the Interface of 9 buttons
{
    wxGridSizer* gridSizer = new wxGridSizer(3, 3, 0, 0);
    buttons = new wxButton * [9];

    for (int i = 0; i < 9; ++i)
    {
        buttons[i] = new wxButton(this, wxID_ANY, wxEmptyString);
        buttons[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TicTacToeFrame::OnButton_Click, this);
        buttons[i]->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        gridSizer->Add(buttons[i], 1, wxEXPAND | wxALL);
    }

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);

    SetSizer(mainSizer);
    Centre();

    currentPlayer = false;
}

// Defining OnButton_Click() function for event handling
void TicTacToeFrame::OnButton_Click(wxCommandEvent& event) // Called when button is clicked
{
    wxButton* button = static_cast<wxButton*>(event.GetEventObject()); // Getting the clicked button and storing in button
    int buttonIndex = GetButton_Index(button); // Getting the index of button and storing in buttonIndex

    if (button->GetLabel().IsEmpty()) // Executes if the button is not pressed and set the label of button to current player symbol (X or O)
    {
        button->SetLabel(GetCurrent_PlayerSymbol()); // Set the label on the button
        button->Disable(); // Disable the button that as already been assigned with label

        if (CheckWin_Condition()) // Executes when win condition is met
        {
            wxString winner = GetCurrent_PlayerSymbol();
            wxString message = "Player " + winner + " won the game";
            wxMessageBox(message, "Game Over", wxOK | wxICON_INFORMATION);
            // Calling ResetGame() function
            ResetGame();
            return;
        }
        else if (IsBoardFull()) // Executes when draw condition is met
        {
            wxMessageBox("It's a draw!", "Game Over", wxOK | wxICON_INFORMATION);
            // Calling ResetGame() function
            ResetGame();
            return;
        }

        TogglePlayer(); // Executes if the game continues, the current player is toggled to the next player.
    }
}

// Defining GetButton_Index()
int TicTacToeFrame::GetButton_Index(wxButton* button) // Iterates over the array of buttons and find the index of given button
{
    for (int i = 0; i < 9; ++i)
    {
        if (buttons[i] == button)
        {
            return i;
        }

    }
    return -1;
}

// Defining GetCurrent_PlayerSymbol()
wxString TicTacToeFrame::GetCurrent_PlayerSymbol() // Returns O or X based on the currentPlayer variable
{
    return currentPlayer ? "O" : "X";
}

// Defining CheckWin_Condition()
bool TicTacToeFrame::CheckWin_Condition() // Check for win condition in rows, columns and diagonals and search for (O or X) symbols
{
    // Check rows
    for (int i = 0; i < 3; ++i)
    {
        if (buttons[i * 3]->GetLabel() == buttons[i * 3 + 1]->GetLabel() && buttons[i * 3]->GetLabel() == 
            buttons[i * 3 + 2]->GetLabel() && !buttons[i * 3]->GetLabel().IsEmpty())
            return true;
    }

    // Check columns
    for (int i = 0; i < 3; ++i)
    {
        if (buttons[i]->GetLabel() == buttons[i + 3]->GetLabel() && buttons[i]->GetLabel() == buttons[i + 6]->GetLabel() &&
            !buttons[i]->GetLabel().IsEmpty())
            return true;
    }

    // Check diagonals
    if (buttons[0]->GetLabel() == buttons[4]->GetLabel() && buttons[0]->GetLabel() == buttons[8]->GetLabel() && 
        !buttons[0]->GetLabel().IsEmpty())
    {
        return true;
    }
        
    if (buttons[2]->GetLabel() == buttons[4]->GetLabel() && buttons[2]->GetLabel() == buttons[6]->GetLabel() && 
        !buttons[2]->GetLabel().IsEmpty())
    {
        return true;
    }
    return false;
}

// Defining IsBoardFull()
bool TicTacToeFrame::IsBoardFull() // Check if any box is empty 
{
    for (int i = 0; i < 9; ++i)
    {
        if (buttons[i]->GetLabel().IsEmpty())
            return false; // Empty boxes found
    }
    return true; // All boxes are full
}

// Defining TogglePlayer()
void TicTacToeFrame::TogglePlayer() // Flips the current player boolean variables
{
    currentPlayer = !currentPlayer;
}

// Defining ResetGame()
void TicTacToeFrame::ResetGame() // Resets the game by clearing all the labels and setting the boolean of currentPlayer to false
{
    for (int i = 0; i < 9; ++i)
    {
        buttons[i]->SetLabel(wxEmptyString);
        buttons[i]->Enable();
    }
    currentPlayer = false;
}
