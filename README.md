# TicTacToe fight to death
---
You are to build an automated TicTacToe player.  

Create a class `TicTacToePlayer` that has the following interface:
```c++
class TicTacToePlayer
{
public:
    TicTacToePlayer(char symbol);
    
	char GetSymbol() const;

	BoardState PlayTurn(char* board);
};
```

Here are the constants we'll be working with:
```c++
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
```

I'll randomly pick the player's order.  
The game will be driven by loop that resembles this one:
```c++
while (state != BoardState::StillPlaying)
{
    nextPlayer.PlayTurn(board);
};

PrintWinner();
```

Things to note:
- I will not check whether a player is cheating UNLESS their opponent says they are i.e. it's up to you to detect whether your enemy has cheated and return `BoardState::OpponentCheating``
- If you claim that your opponent is cheating and he isn't. you lose (instant Karma)
- If you claim your opponent is cheating and he is, you win
- If the game ends and the two players report a different state, the winner is observed by hand.
