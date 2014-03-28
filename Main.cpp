using namespace std;

const int BoardSize = 3;
const char FirstSymbol = 'X';
const char SecondSymbol = 'O';
const char EmptySymbol = '-';

enum class BoardState
{
	StillPlaying,
	Player1Wins,
	Player2Wins,
	Draw,
	OpponentCheating,
};

class TicTacToePlayer
{
public:
	TicTacToePlayer(int playerIndex)
	{

	}

	char GetSymbol() const
	{
		return 'X';
	}

	BoardState PlayTurn(char* board)
	{
		return BoardState::OpponentCheating;
	}
};


void PrintBoard(char* board, char* firstName, char* secondName, int turn)
{
	cout << "****************" << endl;
	cout << "Turn: " << turn << endl;
	cout << "First player: " << firstName << endl;
	cout << "Second player: " << secondName << endl;
	cout << "It's " << (turn % 2 == 0 ? firstName : secondName) << "'s turn to play!";
	cout << endl;

	for (int i = 0; i < BoardSize; i++)
	{
		cout << "    ";
		for (int j = 0; j < BoardSize; j++)
		{
			cout << board[i * BoardSize + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
};

bool DetectCheating(char* previousBoard, char* board, char playerSymbol)
{
	// Do magic here
	
	// First detect how many cells have been changed
	// If more than one cell was changed, cheating was commensed
	int changedIndex = -1;
	for (int i = 0; i < BoardSize * BoardSize; i++)
	{
		if (previousBoard[i] != board[i])
		{
			if (changedIndex == -1)
			{
				changedIndex = i;
			}
			else
			{
				return true;
			}
		}
	}
	// If no cells have been changed, that's cheatin
	if (changedIndex == -1)
	{
		return true;
	}
	// If one cell was changed, see if that cell was empty before the turn
	if (previousBoard[changedIndex] != EmptySymbol)
	{
		return true;
	}
	return false;
}

int main()
{
	TicTacToePlayer players[] = { TicTacToePlayer(FirstSymbol), TicTacToePlayer(SecondSymbol) };
	char* playerNames[] = { "Gosho", "Stefan" };
	int activePlayer = -1;

	char board[BoardSize * BoardSize] = { EmptySymbol, EmptySymbol, EmptySymbol, EmptySymbol, EmptySymbol, EmptySymbol, EmptySymbol, EmptySymbol, EmptySymbol };
	char previousBoard[BoardSize * BoardSize];

	BoardState state = BoardState::StillPlaying;
	int turnCounter = 0;

	while (state == BoardState::StillPlaying)
	{
		activePlayer = (activePlayer + 1) % 2;

		PrintBoard(board, playerNames[0], playerNames[1], turnCounter);

		memcpy(previousBoard, board, BoardSize * BoardSize);

		turnCounter++;
		state = players[activePlayer].PlayTurn(board); 


		_sleep(5000);
	}

	int otherPlayer = (activePlayer + 1) % 2;
	// See if someone was cheating
	if ((state == BoardState::Player1Wins && activePlayer == 0) ||
		(state == BoardState::Player2Wins && activePlayer == 1) ||
		state == BoardState::Draw)
	{

		BoardState otherState = players[otherPlayer].PlayTurn(board);
		if (otherState == BoardState::OpponentCheating)
		{
			state = BoardState::OpponentCheating;
		}
		else
		{
			cout << "Players have different opinions on the end state. Winner should be now observed manually" << endl;

			int y;
			cin >> y;

			return;
		}
	}

	if (state == BoardState::OpponentCheating)
	{
		cout << playerNames[otherPlayer] << " claims their opponent is cheating!" << endl;

		bool isReallyCheating = DetectCheating(previousBoard, board, players[activePlayer].GetSymbol());

		if (!isReallyCheating)
		{
			cout << "NONE IS CHEATING, Y DO U BLAME PEOPLE? Y U SO MEAN " << playerNames[otherPlayer] << "?" << endl;
			state = static_cast<BoardState>(activePlayer + 1);
		}
		else
		{
			cout << playerNames[activePlayer] << " is actually cheating, fuck him" << endl;
			state = static_cast<BoardState>(otherPlayer + 1);
		}
	}

	switch (state)
	{
	case BoardState::Player1Wins:
		cout << playerNames[0] << " wins!";
		break;
	case BoardState::Player2Wins:
		cout << playerNames[1] << " wins!";
		break;
	case BoardState::Draw:
		cout << "It's a draw!";
		break;
	case BoardState::OpponentCheating:
		cout << "Cheating confirmed! " << playerNames[0] << " wins!";
		break;
	default:
		break;
	}


	int x;
	cin >> x;

}
