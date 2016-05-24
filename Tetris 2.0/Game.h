#include "Enums.h"  // Our enums header
#include "cBlock.h" // Contains the class that represents a game block
#include "time.h" // We use time(), located in "time.h", to seed our random generator
#include "math.h" // We'll be using the abs() function located in "math.h"
#include <vector> // An STL vector will store the game squares 
#include <string> // Used for any string functionality we require
#include "FontManager.h"
#include "StartMenu.h"
#include "CollisionManager.h"
#include "BackGround.h"
#include "EndMenu.h"

static int force_down_counter = 0; //counts the amount of time that has passed since we moved the focus block down
static int slide_counter = SLIDE_TIME; //keeps track of how much time the player has been allowed to slide the focus block

class Game
{
	public:
		Game();

		void Start(); 
		bool IsExiting();

		void GameLoop();
		void MainGame();
		void HandleGameInput(sf::Event& event);

		void ShowStartMenu(sf::Event& event);
		void ShowEndMenu(sf::Event& event);

		//functions to run when the game ends
		void Win();
		void Lose();
		void HandleWinLoseInput();

		//Each time the focus block is changed and reset to the top of the game area,
		//we need to see if it can still move. 
		//If it can't, we know that the game is over because the squares have built up to high.
		void CheckWin();
		void CheckLoss();

		void HandleBottomCollision(); //call this function when a block can't move anymore

		//functions to check if a line is completed and to change the block the user controls
		void ChangeFocusBlock();
		int CheckCompletedLines();
		void UpdateBlock(); //updates the focus block's position and checks collision
		void GameText(sf::RenderWindow& window); //displays text such as score and other game info
		
		void ShutDown();

	private:
		sf::RenderWindow mainWindow;

		cBlock* g_FocusBlock = NULL;  // The block the player is controlling
		cBlock* g_NextBlock = NULL;  // The next block to be the focus block

		vector<cSquare*> g_OldSquares;     // The squares that no longer form the focus block
		int g_Score;                       // Players current score
		int g_Level;                       // Current level player is on
		int g_FocusBlockSpeed = INITIAL_SPEED; // Speed of the focus block

		enum GameState {
			startMenu, playing, endScreen, exited
		};
		GameState gameState;

		CollisionManager colMngr; 
		Background bkgr; 

		//strings need for game info
		string score;
		string nextScore;
		string level;

		//texts to display score, next score and level
		sf::Text textItems[3]; 
};