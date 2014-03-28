#include <cstring>
#include <cstdlib>
#include <ctime>

namespace niesme
{
	class TicTacToePlayer
	{
		char symbol;
		char oldboard[9];
		int round;

		bool BoardClear(char *board)
		{
			bool emptyBoard = true;

			for(int i = 0;i < 9;i++)
				if(board[i] != '-')
				{
					emptyBoard = false;
					break;
				}

			return emptyBoard;
		}

		bool CheckCheating(char *board)
		{
			if(round == 1)
			{
				if(BoardClear(board))
					return false || symbol == SecondSymbol;
			}

			int changes = 0;

			for(int i = 0;i < 9;i++)
			{
				if(oldboard[i] == '-')
				{
					if(board[i] != '-')
						changes++;
				} else {
					if(oldboard[i] != board[i])
						return true;
				}
			}

			if(changes == 1)
				return false;
			return true;
		}

		BoardState GetState(char *board)
		{
			//check rows
			for(int i = 0;i < 3;i++)
				if(board[i*3] == board[i*3+1] == board[i*3+2])
				{
					if(board[i] == FirstSymbol)
						return BoardState::Player1Wins;
					if(board[i] == SecondSymbol)
						return BoardState::Player2Wins;
				}

			//check columns
			for(int i = 0;i < 3;i++)
				if(board[i] == board[i+3] == board[i+6])
				{
					if(board[i] == FirstSymbol)
						return BoardState::Player1Wins;
					if(board[i] == SecondSymbol)
						return BoardState::Player2Wins;
				}

			//check diagonals
			if(board[0] == board[4] == board[8])
			{
				if(board[0] == FirstSymbol)
					return BoardState::Player1Wins;
				if(board[0] == SecondSymbol)
					return BoardState::Player2Wins;
			}
			if(board[2] == board[4] == board[6])
			{
				if(board[2] == FirstSymbol)
					return BoardState::Player1Wins;
				if(board[2] == SecondSymbol)
					return BoardState::Player2Wins;
			}

			bool boardFull = true;

			for(int i = 0;i < 9;i++)
				if(board[i] == '-')
					boardFull = false;

			if(boardFull)
				return BoardState::Draw;

			return BoardState::StillPlaying;
		}

		bool CompleteTri(char *board)
		{
			//columns
			for(int i = 0;i < 3;i++)
			{
				if(board[i] == board[i+3])
				{
					if(board[i] != '-' && board[i+6] == '-')
					{
						board[i+6] = symbol;
						return true;
					}
				}
				if(board[i+3] == board[i+6])
				{
					if(board[i+3] != '-' && board[i] == '-')
					{
						board[i] = symbol;
						return true;
					}
				}
				if(board[i] == board[i+6])
				{
					if(board[i] != '-' && board[i+3] == '-')
					{
						board[i+3] = symbol;
						return true;
					}
				}
			}

			//rows
			for(int i = 0;i < 3;i++)
			{
				if(board[i*3] == board[i*3+1])
				{
					if(board[i*3] != '-' && board[i*3+2] == '-')
					{
						board[i*3+2] = symbol;
						return true;
					}
				}
				if(board[i*3+1] == board[i*3+2])
				{
					if(board[i*3+1] != '-' && board[i*3] == '-')
					{
						board[i*3] = symbol;
						return true;
					}
				}
				if(board[i*3] == board[i*3+2])
				{
					if(board[i*3] != '-' && board[i*3+1] == '-')
					{
						board[i*3+1] = symbol;
						return true;
					}
				}
			}

			//diagonals
			if(board[0] == board[4])
			{
				if(board[0] != '-' && board[8] == '-')
				{
					board[8] = symbol;
					return true;
				}
			}
			if(board[4] == board[8])
			{
				if(board[4] != '-' && board[0] == '-')
				{
					board[0] = symbol;
					return true;
				}
			}
			if(board[0] == board[8])
			{
				if(board[0] != '-' && board[4] == '-')
				{
					board[4] = symbol;
					return true;
				}
			}

			if(board[2] == board[4])
			{
				if(board[0] != '-' && board[6] == '-')
				{
					board[6] = symbol;
					return true;
				}
			}
			if(board[4] == board[6])
			{
				if(board[4] != '-' && board[2] == '-')
				{
					board[2] = symbol;
					return true;
				}
			}
			if(board[2] == board[6])
			{
				if(board[2] != '-' && board[4] == '-')
				{
					board[4] = symbol;
					return true;
				}
			}

			return false;
		}

		bool SmartMove(char* board)
		{
			if(board[4] == symbol)
			{
				if(board[0] == symbol)
				{
					if(board[2] == EmptySymbol)
					{
						if(board[7] == EmptySymbol)
						{
							if(board[1] == EmptySymbol)
							{
								board[1] = symbol;
								return true;
							}
						}
					}
					if(board[6] == EmptySymbol)
					{
						if(board[5] == EmptySymbol)
						{
							if(board[3] == EmptySymbol)
							{
								board[3] = symbol;
								return true;
							}
						}
					}
				}
			}

			return false;
		}

		public:
		TicTacToePlayer(char _symbol)
		{
			symbol = _symbol;

			round = 0;

			srand(time(0));
			
			for(int i = 0;i < 9;i++)
				oldboard[i] = '-';
		}

		char GetSymbol() const
		{
			return symbol;
		}

		BoardState PlayTurn(char* board)
		{
			round++;

			if(CheckCheating(board))
				return BoardState::OpponentCheating;

			BoardState startState = GetState(board);

			if(startState == BoardState::Player1Wins || startState == BoardState::Player2Wins || startState == BoardState::Draw)
				return startState;

			if(!CompleteTri(board))
			{
				if(!SmartMove(board))
				{
					int pos = 4;

					while(board[pos] != '-')
						pos = rand()%9;

					board[pos] = symbol;
				}
			}

			BoardState endState = GetState(board);

			std::memcpy(oldboard, board, sizeof(char)*9);

			return endState;
		}
	};
}
