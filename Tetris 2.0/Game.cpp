#include "Game.h"

Game::Game() : g_Score(1), g_Level(1)
{
	//load the font to be used throughout the game
	FontManager::Instance()->LoadText();
	
	srand(time(0));

	// Initialize blocks and set them to their proper locations.
	g_FocusBlock = new cBlock(BLOCK_START_X, BLOCK_START_Y, (BlockType)(rand() % 7));
	g_NextBlock = new cBlock(NEXT_BLOCK_CIRCLE_X, NEXT_BLOCK_CIRCLE_Y, (BlockType)(rand() % 7));

}

void Game::Start()
{
	gameState = playing;

	mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Tetris");

	while (!IsExiting())
	{
		GameLoop(); 
	}

	mainWindow.close(); 
}

bool Game::IsExiting()
{
	if (gameState == exited)
		return true;
	else
		return false;
}

//shows different screens based on the gameState
void Game::GameLoop()
{
	sf::Event currEvent;
	switch (gameState)
	{
		case startMenu:
			ShowStartMenu(currEvent);
			break;
		case playing:
			MainGame();
			break;
		case endScreen:
			ShowEndMenu(currEvent);
			break;
	}
}

//gameplay stuff happens here (drawing, moving, updating blocks, etc)
void Game::MainGame()
{
	while (mainWindow.isOpen())
	{
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mainWindow.close();
				gameState = exited; 
			}

			HandleGameInput(event);
				
		}

		UpdateBlock();

		mainWindow.clear();

		bkgr.DrawBackground(mainWindow, g_Level); //draw the background of the level
		g_FocusBlock->Draw(mainWindow); //draws the block the player is controlling
		g_NextBlock->Draw(mainWindow); //shows the next block that will come out

		// Draw the old squares at the bottom of the level
		for (int i = 0; i < g_OldSquares.size(); i++)
		{
			g_OldSquares[i]->Draw(mainWindow);
		} 

		GameText(mainWindow); //draws the score, level, etc

		mainWindow.display();
	}
}

void Game::UpdateBlock()
{
	
	//In every frame we begin by incrementing force_down_counter. 
	force_down_counter++;

	//We then check to see if it has exceeded our focus block's movement rate (g_FocusBlockSpeed). 
	//If it has, we make sure there won't be a collision and move the focus block down
	if (force_down_counter >= g_FocusBlockSpeed)
	{
		// Always check for collisions before moving anything 
		if (!colMngr.CheckWallCollisions(g_FocusBlock, DOWN) &&
			!colMngr.CheckEntityCollisions(g_FocusBlock, DOWN, g_OldSquares))
		{
			g_FocusBlock->Move(DOWN); // move the focus block
			force_down_counter = 0; // reset our counter
		}
	}

	// Check to see if focus block's bottom has hit something.
	// If it has, we decrement our counter. 
	if (colMngr.CheckWallCollisions(g_FocusBlock, DOWN) ||
		colMngr.CheckEntityCollisions(g_FocusBlock, DOWN, g_OldSquares))
	{
		slide_counter--;
	}
	// If there isn't a collision, we reset our counter. 
	// This is in case the player moves out of a collision. 
	else
	{
		slide_counter = SLIDE_TIME;
	}
	// If the counter hits zero, we reset it and call our 
	// function that handles changing the focus block. 
	if (slide_counter == 0)
	{
		slide_counter = SLIDE_TIME;
		HandleBottomCollision();
	}
	
}

void Game::HandleGameInput(sf::Event& event)
{
	// These variables allow the user to hold the arrow keys down 
	static bool down_pressed = false;
	static bool left_pressed = false;
	static bool right_pressed = false;

	if (event.type == sf::Event::KeyPressed)
	{
		//rotate the block when the user presses up
		if (event.key.code == sf::Keyboard::Up)
		{
			if (!colMngr.CheckRotationCollisions(g_FocusBlock, g_OldSquares))
			{
				g_FocusBlock->Rotate();
			}
			
		}

		// For the left, right, and down arrow keys, we just set a bool variable 
		if (event.key.code == sf::Keyboard::Down)
			down_pressed = true;
		else if (event.key.code == sf::Keyboard::Left)
			left_pressed = true;
		else if (event.key.code == sf::Keyboard::Right)
			right_pressed = true;  

	}

	//when player releases a key press
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Down)
			down_pressed = false;
		else if (event.key.code == sf::Keyboard::Left)
			left_pressed = false;
		else if (event.key.code == sf::Keyboard::Right)
			right_pressed = false;
	}

	// Now we handle the arrow keys, making sure to check for collisions 
	if (down_pressed)
	{
		if (!colMngr.CheckWallCollisions(g_FocusBlock, DOWN) && !colMngr.CheckEntityCollisions(g_FocusBlock, DOWN, g_OldSquares))
		{
			g_FocusBlock->Move(DOWN);
		}
	}
	else if (left_pressed)
	{
		if (!colMngr.CheckWallCollisions(g_FocusBlock, LEFT) && !colMngr.CheckEntityCollisions(g_FocusBlock, LEFT, g_OldSquares))
		{
			g_FocusBlock->Move(LEFT);
		}
	}
	else if (right_pressed)
	{
		if (!colMngr.CheckWallCollisions(g_FocusBlock, RIGHT) && !colMngr.CheckEntityCollisions(g_FocusBlock, RIGHT, g_OldSquares))
		{
			g_FocusBlock->Move(RIGHT);
		}
	}
}

void Game::HandleBottomCollision()
{
	ChangeFocusBlock();

	// Check for completed lines and store the number of lines completed 
	int num_lines = CheckCompletedLines();

	if (num_lines > 0)
	{
		// Increase player's score according to number of lines completed 
		g_Score += POINTS_PER_LINE * num_lines;

		// Check to see if it's time for a new level 
		if (g_Score >= g_Level * POINTS_PER_LEVEL)
		{
			g_Level++;
			CheckWin(); // check for a win after increasing the level 
			g_FocusBlockSpeed -= SPEED_CHANGE; // shorten the focus blocks movement interval
		}
	}

	// Now would be a good time to check to see if the player has lost 
	CheckLoss();
}

// Add the squares of the focus block to g_OldSquares 
// and set the next block as the focus block. 
void Game::ChangeFocusBlock()
{
	// Get an array of pointers to the focus block squares
	cSquare** square_array = g_FocusBlock->GetSquares();

	// Add focus block squares to g_OldSquares 
	for (int i = 0; i<4; i++)
	{
		g_OldSquares.push_back(square_array[i]);
	}

	delete g_FocusBlock; // delete the current focus block
	g_FocusBlock = g_NextBlock; // set the focus block to the next block
	g_FocusBlock->SetupSquares(BLOCK_START_X, BLOCK_START_Y);

	// Set the next block to a new block of random type 
	g_NextBlock = new cBlock(NEXT_BLOCK_CIRCLE_X, NEXT_BLOCK_CIRCLE_Y, (BlockType)(rand() % 7));
}

void Game::GameText(sf::RenderWindow& window)
{
	score = "Score: " + to_string(g_Score);
	nextScore = "Req. Score:" + to_string(g_Level*POINTS_PER_LEVEL);
	level = "Level: " + to_string(g_Level);

	FontManager::Instance()->SetText(textItems[0], score, SCORE_RECT_X, SCORE_RECT_Y, FONT_SIZE, sf::Color::Red, false);
	FontManager::Instance()->SetText(textItems[1], nextScore, NEEDED_SCORE_RECT_X, NEEDED_SCORE_RECT_Y, FONT_SIZE, sf::Color::Red, false);
	FontManager::Instance()->SetText(textItems[2], level, LEVEL_RECT_X, LEVEL_RECT_Y, FONT_SIZE, sf::Color::Red, false);

	for (int i = 0; i < 3; i++)
		window.draw(textItems[i]);
}

// Return amount of lines cleared or zero if no lines were cleared 
int Game::CheckCompletedLines()
{
	// Store the amount of squares in each row in an array
	int squares_per_row[13];

	// The compiler will fill the array with junk values if we don't do this 
	for (int index = 0; index<13; index++)
		squares_per_row[index] = 0;

	int row_size = SQUARE_MEDIAN * 2; // pixel size of one row
	int bottom = GAME_AREA_BOTTOM - SQUARE_MEDIAN; // center of bottom row
	int top = bottom - (12 * row_size); // center of top row

	int num_lines = 0; // number of lines cleared 
	int row; // multipurpose variable

	// Check for full lines 
	for (int i = 0; i<g_OldSquares.size(); i++)
	{
		// Get the row the current square is in 
		row = (g_OldSquares[i]->GetCenterY() - top) / row_size;

		// Increment the appropriate row counter
		squares_per_row[row]++;
	}

	// Erase any full lines
	for (int line = 0; line<13; line++)
	{
		// Check for completed lines 
		if (squares_per_row[line] == SQUARES_PER_ROW)
		{
			// Keep track of how many lines have been completed 
			num_lines++;

			// Find any squares in current row and remove them 
			for (int index = 0; index<g_OldSquares.size(); index++)
			{
				if (((g_OldSquares[index]->GetCenterY() - top) / row_size) == line)
				{
					// delete the square
					delete g_OldSquares[index];
					// remove it from the vector
					g_OldSquares.erase(g_OldSquares.begin() + index);

					index--;
				}
			}
		}
	}

	// Move squares above cleared line down
	for (int index = 0; index<g_OldSquares.size(); index++)
	{
		for (int line = 0; line<13; line++)
		{
			// Determine if this row was filled 
			if (squares_per_row[line] == SQUARES_PER_ROW)
			{
				// If it was, get the location of it within the game area
				row = (g_OldSquares[index]->GetCenterY() - top) / row_size;

				// Now move any squares above that row down one 
				if (row < line)
				{
					g_OldSquares[index]->Move(DOWN);
				}
			}
		}
	}

	return num_lines;
}

void Game::HandleWinLoseInput()
{
	//make the player control the next block when the previous one reaches the bottom
	ChangeFocusBlock();

	// Check for completed lines and store the number of lines completed 
	int num_lines = CheckCompletedLines();

	if (num_lines > 0)
	{
		// Increase player's score according to number of lines completed 
		g_Score += POINTS_PER_LINE * num_lines;

		// Check to see if it's time for a new level 
		if (g_Score >= g_Level * POINTS_PER_LEVEL)
		{
			g_Level++;
			CheckWin(); // check for a win after increasing the level 
			g_FocusBlockSpeed -= SPEED_CHANGE; // shorten the focus blocks movement interval
		}
	}

	// check to see if the player has lost after checking everything else 
	CheckLoss();

}

void Game::CheckWin()
{
	// If current level is greater than number of levels, player has won 
	if (g_Level > NUM_LEVELS)
	{
		cout << "you win"; 
	}
}

void Game::CheckLoss()
{
	// We call this function when the focus block is at the top of that 
	// game area. If the focus block is stuck now, the game is over. 
	if (colMngr.CheckEntityCollisions(g_FocusBlock, DOWN, g_OldSquares))
	{
		// Clear the old squares vector 
		for (int i = 0; i<g_OldSquares.size(); i++)
		{
			delete g_OldSquares[i];
		}
		g_OldSquares.clear();

		cout << "You lose";
	}
}

void Game::ShutDown()
{
	// Get pointers to the squares in our focus and next-in-line block so we 
	// can delete them. We must do this before we delete our blocks so we
	// don't lose references to the squares. Note that these are pointers to
	// arrays of pointers. 
	cSquare** temp_array_1 = g_FocusBlock->GetSquares();
	cSquare** temp_array_2 = g_NextBlock->GetSquares();

	// Delete our blocks 
	delete g_FocusBlock;
	delete g_NextBlock;

	// Delete the temporary arrays of squares 
	for (int i = 0; i<4; i++)
	{
		delete temp_array_1[i];
		delete temp_array_2[i];
	}

	// Delete the squares that are in the game area 
	for (int i = 0; i<g_OldSquares.size(); i++)
	{
		delete g_OldSquares[i];
	}
}

void Game::ShowStartMenu(sf::Event& event)
{
	StartMenu menu; 
	bkgr.DrawBackground(mainWindow, g_Level);
	menu.DrawMenu(mainWindow, event);

	int option = menu.ChooseOption();

	if (menu.close)
		gameState = exited; 

	if (option == 1)
	{
		gameState = playing;
	}
	else if (option == 2)
	{
		gameState = exited; 
	}
}

void Game::ShowEndMenu(sf::Event& event)
{
	EndMenu menu; 
	menu.DrawEndMenu(mainWindow, event); 

	int option = menu.ChooseOption();

	if (menu.close)
		gameState = exited;
	
	if (option == 0)
		gameState = playing;
	else if (option == 1)
		gameState = exited; 
}
