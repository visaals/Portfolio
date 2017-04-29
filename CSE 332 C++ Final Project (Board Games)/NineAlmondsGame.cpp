#include "stdafx.h"
#include "NineAlmondsGame.h"


NineAlmondsGame::NineAlmondsGame(vector<game_piece> board, unsigned int1, unsigned int2)
	: board(board), boardwidth(int1), boardheight(int2)
{}

NineAlmondsGame::NineAlmondsGame()
	: boardwidth(board_width), boardheight(board_height)
{
	int counter = 0;
	string line;
	
	string display;
	string name;
	string color;
	unsigned width;
	unsigned height;

	fstream file("NineAlmondsGame.txt");

	if (file.is_open())
	{

		while (getline(file, line))
		{

			istringstream iss(line);
			cout << line << endl;


			if (line == "NODATA") {
				for (int i = 0;i < board_height*board_height;++i) {
					board.push_back(game_piece(noCol, "empty", " "));
				}

				for (int i = 6; i < 9;++i) {
					board[i] = (game_piece(brown, "almond", "A"));
				}
				for (int i = 11; i < 14; ++i) {
					board[i] = (game_piece(brown, "almond", "A"));
				}
				for (int i = 16; i < 19; ++i) {
					board[i] = (game_piece(brown, "almond", "A"));
				}
			}

			if (line == "NineAlmonds") {
				for (int i = 0;i < board_height*board_height;++i) {
					board.push_back(game_piece(noCol, "empty", " "));
				}
				istringstream iss(line);
				
			}

			if (iss >> color &&  iss >> name && iss >> display && iss >> width && iss >> height)
			{
				
					if (width < boardwidth && height < boardheight)
					{
						game_piece curPiece{ stringToColor(color), name, display };
						int index = boardwidth * height + width;
					
						board[index] = curPiece;
						counter++;
					}
				
			}
			
		}
	}
	else
	{
		cerr << "File did not open... creating new game." << endl;
		for (int i = 0;i < board_height*board_height;++i) {
			board.push_back(game_piece(noCol, "empty", " "));
		}

		for (int i = 6; i < 9;++i) {
			board[i] = (game_piece(brown, "almond", "A"));
		}
		for (int i = 11; i < 14; ++i) {
			board[i] = (game_piece(brown, "almond", "A"));
		}
		for (int i = 16; i < 19; ++i) {
			board[i] = (game_piece(brown, "almond", "A"));
		}

		
	}
}




bool NineAlmondsGame::done() {
	// using the same indexing method as in lab1 where the index of (x,y) is (board_width)*y+x
	bool res = true;
	for (unsigned int i = 0;i < boardwidth*boardheight;++i) {
		//set it to false i
		if (i == 12) { // check if no piece at middle
			if (board[i].display == " ")
				res = false;
		}
		//otherwise, check if the rest of the game pieces are empty
		else {
			if (board[i].display != " ") {
				res = false;
			}
		}
	}
	return res;
}

bool NineAlmondsGame::validmove(const unsigned x1, const unsigned y1, const unsigned x2, const unsigned y2) {
	unsigned xaverage = (x1 + x2) / 2;
	unsigned yaverage = (y1 + y2) / 2;

	// criteria to be a valid move: 

	if (board[boardwidth*y1 + x1].display != "A") {
		return false;
	}
	if (board[boardwidth*yaverage + xaverage].display != "A") {
		return false;
	}
	if (board[boardwidth*y2 + x2].display == "A") {
		return false;
	}

	// checking diagonal moves


	if (x1 != x2 && y1 != y2) {
		if (!(abs((int)x1 - (int)x2) == 2) || !(abs((int)y1 - (int)y2) == 2)) {
			return false;
		}
	}
	if (abs((int)x2 - (int)x1) > 2 || abs((int)y2 - (int)y1) > 2 || abs((int)x2 - (int)x1) == 1 || abs((int)y2 - (int)y1) == 1) {
		return false;
	}

	// if this is reached, the move is valid
	return true;

}

bool NineAlmondsGame::stalemate() {
	if (done()) {
		return false;
	}

	bool result = true;

	for (unsigned int i = 0; i < boardwidth*boardheight;++i) {

		if (board[i].display == "A") {

			for (unsigned int j = 0; j < boardwidth*boardheight; ++j) {

				if (board[j].display != "A") {


					//change the casts

					unsigned x1 = i % static_cast<int>(boardwidth);
					unsigned y1 = i / static_cast<int>(boardwidth);
					unsigned x2 = j % static_cast<int>(boardwidth);
					unsigned y2 = j / static_cast<int>(boardwidth);

					// if there exists a valid move anywhere in the board for a remaining piece 
					if (validmove(x1, y1, x2, y2)) {
						result = false;
					}
				}
			}
		}
	}
	return result;
}


void NineAlmondsGame::turn() {
	unsigned x1, y1, x2, y2; // where the prompts are stored 
	while (true) {
		if (done()) {
			break;
		}

		if (stalemate()) {
			break;
		}

		cout << "Point 1 (eg. piece you want to move):" << endl;
		int prompt1result = prompt(x1, y1);

		if (prompt1result == QUIT) {
			throw QUIT;
		}
		if (board[boardwidth*y1 + x1].display == " ") {
			cout << "no piece at this point, try again!" << endl;
			break;
		}
		if (prompt1result == SUCCESS) {
			cout << "Point 2 (eg. where you want to move it to):" << endl;
			int prompt2result = prompt(x2, y2);
			if (prompt2result == QUIT) {
				throw QUIT;
			}

			if (prompt2result == SUCCESS) {
				if (validmove(x1, y1, x2, y2)) {

					// here I switch the gamepieces stored at the from and to places in the vector 

					vector<game_piece>temp;
					for (unsigned int i = 0; i <= boardwidth*boardheight;++i) {
						temp.push_back(game_piece(noCol, "", " "));
					}
					unsigned xav = (x1 + x2) / 2;
					unsigned yav = (y1 + y2) / 2;
					temp[boardwidth*y1 + x1] = board[boardwidth*y2 + x2];
					board[boardwidth*y2 + x2] = board[boardwidth*y1 + x1];
					board[boardwidth*y1 + x1] = temp[boardwidth*y1 + x1];

					board[boardwidth*yav + xav] = game_piece(noCol, "empty", " ");


					print();

					// where we keep track of the turn's moves
					string turnHistroy;
					stringstream sstrm;
					sstrm << turnHistroy << y1 << "," << x1;
					sstrm << turnHistroy << " to " << x2 << "," << y2;
					turnHistroy = sstrm.str();
					cout << turnHistroy << '\n' << endl;

					unsigned currentX = x2;
					unsigned currentY = y2;

					if (done()) {
						break;
					}
					if (stalemate()) {
						break;
					}

					// Seeing if you can continue the move 

					int possibleMovescounter = 0;
					for (unsigned int j = 0; j < boardwidth*boardheight; ++j) {

						if (board[j].display != "A") {

							unsigned x2 = j % (int)boardwidth;
							unsigned y2 = j / (int)boardwidth;

							if (validmove(currentX, currentY, x2, y2)) {
								++possibleMovescounter;
							}
						}
					}

					if (possibleMovescounter == 0) {
						cout << "no more possible moves this turn. Move on" << endl;
						break;
					}

					int turn_prompt_resut = turn_prompt();

					while (true) { // want to do this over and over until we are stopped

						if (turn_prompt_resut == NO) {
							break;
						}

						else
						{
							unsigned newX = 0;
							unsigned newY = 0;

							int newPrompt;

							do
							{
								newPrompt = prompt(newX, newY);
								if (newPrompt != QUIT && !validmove(currentX, currentY, newX, newY)) {
									cout << "not a valid move- try again!" << endl;
								}
							} while (!validmove(currentX, currentY, newX, newY));

							if (newPrompt == QUIT) {
								break;
							}

							if (newPrompt == SUCCESS) {
								// continuing the move
								if (validmove(currentX, currentY, newX, newY)) {

									unsigned xav = (currentX + newX) / 2;
									unsigned yav = (currentY + newY) / 2;

									board[boardwidth*newY + newX] = board[boardwidth*currentY + currentX];
									board[boardwidth*currentY + currentX] = game_piece(noCol, "", " ");

									board[boardwidth*yav + xav] = game_piece(noCol, "", " ");


									print();

									stringstream sstrm;
									sstrm << turnHistroy << " to " << newX << "," << newY;

									turnHistroy = sstrm.str();
									cout << turnHistroy << '\n' << endl;

								}
							}

							currentX = newX;
							currentY = newY;
							int counter = 0;

							// checking if turn can possibly be continued
							for (unsigned int j = 0; j < boardwidth*boardheight; ++j) {

								if (board[j].display != "A") {

									unsigned x2 = j % (int)boardwidth;
									unsigned y2 = j / (int)boardwidth;

									if (validmove(currentX, currentY, x2, y2)) {
										++counter;
									}
								}
							}

							if (counter == 0) {
								cout << "no more possible moves this turn. Move on" << endl;
								break;
							}

							if (done()) {
								break;
							}
							if (stalemate()) {
								break;
							}
							turn_prompt_resut = turn_prompt();
						}

					}
				}
				else
				{
					cout << "not a valid move! Try again" << endl;
				}
			}
		}
	}
}

void NineAlmondsGame::turnhelper(unsigned & currentXh, unsigned & currentYh) {
	int turn_prompt_resut = turn_prompt();

	while (true) {

		unsigned newXh = 0;
		unsigned newYh = 0;
		int newPrompt = turn_prompt();


		if (newPrompt == SUCCESS) {
			if (validmove(currentXh, currentYh, newXh, newYh)) {

				unsigned xav = (currentXh + newXh) / 2;
				unsigned yav = (currentYh + newYh) / 2;

				board[boardwidth*newYh + newXh] = board[boardwidth*currentYh + currentXh];
				board[boardwidth*currentYh + currentXh] = game_piece(noCol, "", " ");

				board[boardwidth*yav + xav] = game_piece(noCol, "", " ");

				print();

			}
			else {
				cout << "not a valid move" << endl;
				break;
			}
			currentXh = newXh;
			currentYh = newYh;

			turn_prompt_resut = turn_prompt();
		}
		throw NOT_VALID_MOVE;
	}
}

int NineAlmondsGame::turn_prompt() {
	// seeing if the user wants to continue the turn
	cout << "Do you want to continue this turn? y or n" << endl;
	string response;
	cin >> response;
	if (response == "yes" || response == "Yes" || response == "y") {
		return YES;
	}
	else if (response == "no" || response == "No" || response == "n") {
		return NO;
	}
	else {
		cout << "please either enter y or n" << endl;
		turn_prompt();
	}

	return NO;
}

void NineAlmondsGame::print()
{
	cout << *this << endl;
}

void NineAlmondsGame::save()
{
	
	ofstream ofs("NineAlmondsGame.txt");
	ofs << *this << endl;
}




unsigned NineAlmondsGame::getDim()
{
	return boardwidth;
}

string NineAlmondsGame::getName()
{
	string s = "NineAlmondsGame";
	return s;
}






int NineAlmondsGame::play() {
	int numTurns = 1;
	NineAlmondsGame playing = NineAlmondsGame();

	print();

	while (!done() && !stalemate())
	{
		try
		{
			turn();
			++numTurns;
		}
		catch (enum failuretype q)
		{
			cout << "user quit! Number of turns = " << numTurns << endl;
			return q;
		}

	}
	if (done()) {
		cout << "Game Over! Number of turns = " << numTurns << endl;
		return SUCCESS;
	}
	if (stalemate()) {
		cout << "Game has reached stalemate! Number of turns = " << numTurns << endl;
		return  STALEMATE_RETURN;
	}
	return SUCCESS;
}

ofstream & operator<<(ofstream & ofs, const NineAlmondsGame & ofnag)
{
	ofs << "NineAlmonds" << endl;

	for (unsigned int w = 0; w < ofnag.boardwidth; ++w) {
		for (unsigned int h = 0; h < ofnag.boardheight; ++h) {
			int index = ofnag.boardwidth * h + w;
			ofs << ofnag.board[index].color << " " << ofnag.board[index].name << " " << ofnag.board[index].display << " " << w << " " << h << endl;
		}
	}
	ofs << endl;
	return ofs;
}

ostream & operator<<(ostream & o, const NineAlmondsGame & nag)
{
	// this should print out the current board
	if (sizeof(nag.board) > nag.boardwidth*(nag.boardheight - 1) + (nag.boardwidth - 1)) {
		cerr << "there are too many pieces for this board" << endl;

	}
	else {


		for (int y = nag.boardheight - 1; y >= 0;--y) {
			for (unsigned int x = 0;x <= nag.boardwidth - 1;++x) {
				if (x == (nag.boardwidth - 1)) {
					o << nag.board[(nag.boardwidth*y + x)].display << endl;
				}
				else {
					if (x == 0) {
						o << y << " ";
					}
					o << nag.board[(nag.boardwidth*y + x)].display << " ";
				}
			}
			o << " " << endl;
		}
		for (unsigned int i = 0;i <= nag.boardwidth - 1;++i) {
			if (i == (nag.boardwidth - 1)) {

				o << i << endl;
			}
			else {

				if (i == 0) {
					o << "X" << " ";
				}
				o << i << " ";
			}
		}
	}
	return o;
}