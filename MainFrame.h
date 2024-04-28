#include "Header.h"

// Declaring a class TicTacToeFrame inherited from wxFrame
class TicTacToeFrame : public wxFrame
{
private:
	// Declaring event handler for button
	void OnButton_Click(wxCommandEvent& evt);

	int GetButton_Index(wxButton* button);

	wxString GetCurrent_PlayerSymbol();

	bool CheckWin_Condition();

	bool IsBoardFull();

	void TogglePlayer();

	void ResetGame();

	wxButton** buttons;
	bool currentPlayer; // False for player X, true for player 0
public:

	// Declaring Default constructor
	TicTacToeFrame(const wxString& title);

	// Declaring event tables
	wxDECLARE_EVENT_TABLE();

};
