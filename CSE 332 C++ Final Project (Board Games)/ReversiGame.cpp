#include "stdafx.h"
#include "ReversiGame.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

Reversi::Reversi(string p1, string p2)
	: p1name(p1), p2name(p2), boardwidth(r_width), boardheight(r_height)
{

	currentplayer = p1;
	int counter = 0;
	string line;
	string line2;
	string display;
	string name;
	string color;
	string savedName1;
	string savedName2;
	unsigned width;
	unsigned height;
	int b_startx = 3;
	int w_starty = 4;


	fstream file("ReversiGame.txt");
	if (file.is_open())
	{
		int loops = 0;
		while (getline(file, line))
		{
			++loops;
			istringstream iss(line);
			if (line == "NODATA") {
				for (int i = 0;i < r_height*r_height;++i) {
					board.push_back(game_piece(noCol, "empty", " "));
				}

				board[boardwidth * b_startx + b_startx] = game_piece(black, "reversi_black", "X");
				board[boardwidth * w_starty + w_starty] = game_piece(black, "reversi_black", "X");
				board[boardwidth * b_startx + w_starty] = game_piece(white, "reversi_white", "O");
				board[boardwidth * w_starty + b_startx] = game_piece(white, "reversi_white", "O");

			}

			if (line == "ReversiGame") {


				for (int i = 0;i < r_height*r_height;++i) {
					board.push_back(game_piece(noCol, "empty", " "));
				}
				istringstream iss(line);
			}

			if (loops == 2) {
				iss >> savedName1;
				iss >> savedName2;

				cout << "player first: " << savedName1 << endl;
				cout << "player second: " << savedName2 << endl;


				
				if ((savedName1 != p1name && savedName1 != p2name) || (savedName2 != p2name && savedName2 != p1name)) {
					string response;
					cout << "these names don't match the saved game. Would you like to override? y/n" << endl;
					cin >> response;
				
					if (response == "y" || response == "Y") {
						
						for (size_t i = 0;i < boardheight*boardheight;++i) {
							board.push_back(game_piece(noCol, "empty", " "));
						}

						board[boardwidth * b_startx + b_startx] = game_piece(black, "reversi_black", "X");
						board[boardwidth * w_starty + w_starty] = game_piece(black, "reversi_black", "X");
						board[boardwidth * b_startx + w_starty] = game_piece(white, "reversi_white", "O");
						board[boardwidth * w_starty + b_startx] = game_piece(white, "reversi_white", "O");
						break;
					}
					else if (response == "n" || response == "N") {
						throw QUIT;
					}

				}

			}
			if (loops > 2) {
				iss >> color;
				piece_color colorNum = stringToColor(color);
				if (p1name != savedName1) {
					currentplayer = savedName1;
				}
				else if (p1name == savedName1) {
					currentplayer = savedName1;
				}
				if (colorNum == 0) {
					iss >> name;
					display = " ";
					iss >> width;
					iss >> height;

				}
				else
				{
					
					iss >> name;
					iss >> display;
					iss >> width;
					iss >> height;

					
					if (width < boardwidth && height < boardheight)
					{
				
						game_piece curPiece{ colorNum, name, display };
						int index = boardwidth * height + width;
						
						board[index] = curPiece;
						counter++; 
					}

				}
			}
		}





	}
	else
	{
		cerr << "File did not open... Creating new game" << endl;

		for (size_t i = 0;i < boardheight*boardheight;++i) {
			board.push_back(game_piece(noCol, "empty", " "));
		}

		board[boardwidth * b_startx + b_startx] = game_piece(black, "reversi_black", "X");
		board[boardwidth * w_starty + w_starty] = game_piece(black, "reversi_black", "X");
		board[boardwidth * b_startx + w_starty] = game_piece(white, "reversi_white", "O");
		board[boardwidth * w_starty + b_startx] = game_piece(white, "reversi_white", "O");
	
	}
}

void Reversi::print()
{
	cout << *this << endl;
}

void Reversi::save()
{
	ofstream ofs("ReversiGame.txt");
	ofs << *this << endl;
}

bool Reversi::stalemate()
{

	int blackcount = 0;
	int whitecount = 0;
	game_piece testblack = game_piece(black, "reversi_black", "X");
	game_piece testwhite = game_piece(white, "reversi_white", "O");

	for (size_t i = 0; i < board.size(); ++i) {
		if (board[i].color == black) {
			blackcount++;
		}
		if (board[i].color == white) {
			whitecount++;
		}
	}


	if (blackcount == whitecount) { // the board is split 50/50 so we check 

		int pieceCounter = 0;
		for (size_t i = 0; i < board.size(); ++i) {
			if (board[i].display != " ") {
				pieceCounter++;
			}
		}

		if (pieceCounter == board.size()) {
			//if same num of black and white pieces and all the board is filled.
			return true;
		}


		for (size_t i = 0; i < board.size(); ++i) {
			
			if (board[i].display == " ") {
				// getting the coordinates for the blank space and checking if you can move a piece to that space
			
				auto x = i / boardwidth;
				auto y = i % boardwidth;
				if (validmove(testblack, x, y) || validmove(testwhite, x, y)) {
					
					return false;
					// a valid move exists so it's not done
				}
			}
			// if there is no spaces (eg. all spaces are filled) it is done
		}

		//if no valid moves found
		return true;
	}
	else {
		return false;
	}
}

bool Reversi::done()
{
	int blackcount = 0;
	int whitecount = 0;
	game_piece testblack = game_piece(black, "reversi_black", "X");
	game_piece testwhite = game_piece(white, "reversi_white", "O");

	//checking if board is full
	for (size_t i = 0; i < board.size(); ++i) {
		if (board[i].color == black) {
			blackcount++;
		}
		if (board[i].color == white) {
			whitecount++;
		}
	}
	cout << "Black count: " << blackcount << endl;
	cout << "White count: " << whitecount << endl;

	if (blackcount == 0 || whitecount == 0) {
		return true; // no pieces of one color are remaining (eg. all pieces are of the same color)
	}

	int numValidMoves = 0;
	for (size_t i = 0; i < board.size(); ++i) {
		if (board[i].display == " ") {
			// getting the coordinates for the blank space and checking if you can move a piece to that space

			auto x = i / boardwidth;
			auto y = i % boardwidth;
			if (validmove(testblack, x, y) || validmove(testwhite, x, y)) {
				
				numValidMoves++;

				// a valid move exists so it's not done
			}
		}
		// if there is no spaces (eg. all spaces are filled) it is done

	}
	if (numValidMoves == 0) {
		return true;
	}
	else {
		return false;
	}

	return false;
}

// takes in the piece that you want to put down and the coordinates of where you want to place it
bool Reversi::validmove(game_piece p, const unsigned x2, const unsigned y2)
{
	int count = 0;
	
	// checking if x2,y2 is empty
	if (board[boardwidth*y2 + x2].display == " ") {

		// checking for a piece of the opposite color adjacent to selected space
		// with POLAR COORDINATES!

		//edge case
		if (x2 == 7) {
			for (double theta = M_PI / 2.0; theta <= 3.0 * M_PI / 2.0; theta = theta + (M_PI / 4.0)) {
				double polarHeight = round(y2 + sin(theta));
				double polarWidth = round(x2 + cos(theta));

				double angleIndex = boardwidth*polarHeight + polarWidth;

				if (static_cast<unsigned>(angleIndex) > boardheight*boardwidth - 1) {
					
					break;
				}

				// if adjacent space has a piece of opposite color
				if (board[static_cast<unsigned>(angleIndex)].display != p.display && board[static_cast<unsigned>(angleIndex)].display != " ") {
					
					// checking all pieces in that direction (theta) for a piece of the same color as the piece to be placed
					for (double r = 2; r < boardwidth; ++r) {

						double rpolarHeight = round(y2 + r*sin(theta));
						double rpolarWidth = round(x2 + r*cos(theta));

						double awayIndex = boardwidth*rpolarHeight + rpolarWidth;


						if (static_cast<unsigned>(awayIndex) > boardheight*boardwidth - 1) {
							break;
						}
						if (board[static_cast<unsigned>(awayIndex)].display == " ") {
							// if there's a blank space, it is not a valid move. Pieces must be contiguous 
							break;
						}

						// if we find the a piece in that same color, it's a valid move!
						if (board[static_cast<unsigned>(awayIndex)].display == p.display) {
							
							return true;
						}
					}

				}
			}
		}
		//edge case
		if (y2 == 7) {
			for (double theta = M_PI; theta <= 2 * M_PI; theta = theta + (M_PI / 4.0)) {
				double polarHeight = round(y2 + sin(theta));
				double polarWidth = round(x2 + cos(theta));

				double angleIndex = boardwidth*polarHeight + polarWidth;

				if (static_cast<unsigned> (angleIndex) > boardheight*boardwidth - 1) {
					break;
				}

				// if adjacent space has a piece of opposite color
				if (board[static_cast<unsigned>(angleIndex)].display != p.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

					// checking all pieces in that direction (theta) for a piece of the same color as the piece to be placed
					for (double r = 2; r < boardwidth; ++r) {

						double rpolarHeight = round(y2 + r*sin(theta));
						double rpolarWidth = round(x2 + r*cos(theta));

						double awayIndex = boardwidth*rpolarHeight + rpolarWidth;


						if (static_cast<unsigned>(awayIndex) > boardheight*boardwidth - 1) {
							break;
						}
						if (board[static_cast<unsigned>(awayIndex)].display == " ") {
							// if there's a blank space, it is not a valid move. Pieces must be contiguous 
							break;
						}

						// if we find the a piece in that same color, it's a valid move!
						if (board[static_cast<unsigned>(awayIndex)].display == p.display) {
							return true;
						}
					}

				}
			}
		}


		for (double theta = 0; theta < 2 * M_PI; theta = theta + (M_PI / 4.0)) {
			double polarHeight = round(y2 + sin(theta));
			double polarWidth = round(x2 + cos(theta));

			double angleIndex = boardwidth*polarHeight + polarWidth;
			
			if (static_cast<unsigned> (angleIndex) > boardheight*boardwidth - 1) {
				break;
			}

			// if adjacent space has a piece of opposite color
			if (board[static_cast<unsigned>(angleIndex)].display != p.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

				// checking all pieces in that direction (theta) for a piece of the same color as the piece to be placed
				for (double r = 2; r < boardwidth; ++r) {

					double rpolarHeight = round(y2 + r*sin(theta));
					double  rpolarWidth = round(x2 + r*cos(theta));

					double awayIndex = boardwidth*rpolarHeight + rpolarWidth;


					if (static_cast<unsigned>(awayIndex) > boardheight*boardwidth - 1) {
						break;
					}
					if (board[static_cast<unsigned>(awayIndex)].display == " ") {
						// if there's a blank space, it is not a valid move. Pieces must be contiguous 
						break;
					}

					// if we find the a piece in that same color, it's a valid move!
					if (board[static_cast<unsigned>(awayIndex)].display == p.display) {
						return true;
					}
				}
			}

		}
	}
	// if not empty, it's not a valid move
	else {
		return false;
	}

	// there are empty pieces, but we did not find a valid move
	return false;

}

void Reversi::turn()
{

	if (currentplayer == p1name) {

		game_piece piecetomove;
		unsigned x1 = 0;
		unsigned y1 = 0;

		// player 1 is black and moves first
		piecetomove = game_piece(black, "reversi_black", "X");

		// prompting until we get valid coordinates
		bool validCoord = false;
		int retval = 3453;

		do
		{

			cout << currentplayer << ", it is your turn" << endl;

			retval = gamebase::prompt(x1, y1);

			if (retval == QUIT) {
				throw QUIT;
				break;
			}
			if (retval == SUCCESS) {
				if (!validmove(piecetomove, x1, y1)) {
					cout << "Not a valid move... Try again" << endl;
					gamebase::prompt(x1, y1);
					validCoord = false;
				}
				else {
					validCoord = true;
				}
			}
		} while (retval != SUCCESS &&  validCoord);

		// doing the same thing as finding a valid move 

		// putting down piece
		board[boardwidth*y1 + x1] = piecetomove;
		if (x1 == 7) {
			for (double theta = M_PI / 2; theta <= 3 * M_PI / 2; theta = theta + (M_PI / 4.0)) { // iterating by pi/4 in a circle
				double polarHeight = round(y1 + sin(theta));
				double polarWidth = round(x1 + cos(theta));

				double angleIndex = boardwidth*polarHeight + polarWidth;

				if (static_cast<unsigned>(polarHeight) >= boardheight || static_cast<unsigned>(polarWidth) >= boardwidth) {
					break;
				}


				// if the the board's display is not the same as piece to move and it's not empty
				// checking the piece at r=1 distance away at the angle theta
				if (board[static_cast<unsigned>(angleIndex)].display != piecetomove.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

					int middle = 0;
					for (unsigned r = 1; r < boardheight; ++r) {
						double rpolarHeight = round(y1 + r*sin(theta));
						double rpolarWidth = round(x1 + r*cos(theta));


						double awayIndex = boardwidth*rpolarHeight + rpolarWidth;

						// when we find an opposite piece we go from r=2 to the end to find a piece that matches p
						if (static_cast<unsigned>(rpolarHeight) >= boardheight || static_cast<unsigned>(rpolarWidth) >= boardwidth) {
							break;
						}

						if (board[static_cast<unsigned>(awayIndex)].display == piecetomove.display) {
							// decrementing r until it's 0 and changing the pieces between to be equal to the piecetomove
							middle = static_cast<int>(r);
							break;
						}
					}

					while (middle > 0)
					{
						
						board[static_cast<unsigned>(boardwidth*round((y1 + middle*sin(theta))) + round(x1 + middle*cos(theta)))] = piecetomove;
						--middle;

					}

					
				}
			}
		}
		if (y1 == 7) {
			for (double theta = M_PI; theta <= 2 * M_PI; theta = theta + (M_PI / 4.0)) { // iterating by pi/4 in a circle
				double polarHeight = round(y1 + sin(theta));
				double polarWidth = round(x1 + cos(theta));

				double angleIndex = boardwidth*polarHeight + polarWidth;

				if (static_cast<unsigned>(polarHeight) >= boardheight || static_cast<unsigned>(polarWidth) >= boardwidth) {
					continue;
				}


				// if the the board's display is not the same as piece to move and it's not empty
				// checking the piece at r=1 distance away at the angle theta
				if (board[static_cast<unsigned>(angleIndex)].display != piecetomove.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

					int middle = 0;
					for (unsigned r = 1; r < boardheight; ++r) {
						double rpolarHeight = round(y1 + r*sin(theta));
						double rpolarWidth = round(x1 + r*cos(theta));


						double awayIndex = boardwidth*rpolarHeight + rpolarWidth;

						// when we find an opposite piece we go from r=2 to the end to find a piece that matches p
						if (static_cast<unsigned>(rpolarHeight) >= boardheight || static_cast<unsigned>(rpolarWidth) >= boardwidth) {
							continue;
						}

						if (board[static_cast<unsigned>(awayIndex)].display == piecetomove.display) {
							// decrementing r until it's 0 and changing the pieces between to be equal to the piecetomove
							middle = static_cast<int>(r);
							break;
						}
					}

					while (middle > 0)
					{
						
						board[static_cast<unsigned>(boardwidth*round((y1 + middle*sin(theta))) + round(x1 + middle*cos(theta)))] = piecetomove;
						--middle;

					}

				}
			}
		}
		// switching pieces in between
		for (double theta = 0; theta < (2 * M_PI); theta = theta + (M_PI / 4.0)) { // iterating by pi/4 in a circle
			double polarHeight = round(y1 + sin(theta));
			double polarWidth = round(x1 + cos(theta));

			double angleIndex = boardwidth*polarHeight + polarWidth;

			if (static_cast<unsigned>(polarHeight) >= boardheight || static_cast<unsigned>(polarWidth) >= boardwidth) {
				break;
			}


			// if the the board's display is not the same as piece to move and it's not empty
			// checking the piece at r=1 distance away at the angle theta
			if (board[static_cast<unsigned>(angleIndex)].display != piecetomove.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

				int middle = 0;
				for (unsigned r = 1; r < boardheight; ++r) {
					double rpolarHeight = round(y1 + r*sin(theta));
					double rpolarWidth = round(x1 + r*cos(theta));


					double awayIndex = boardwidth*rpolarHeight + rpolarWidth;

					// when we find an opposite piece we go from r=2 to the end to find a piece that matches p
					if (static_cast<unsigned>(rpolarHeight) >= boardheight || static_cast<unsigned>(rpolarWidth) >= boardwidth) {
						break;
					}

					if (board[static_cast<unsigned>(awayIndex)].display == piecetomove.display) {
						// decrementing r until it's 0 and changing the pieces between to be equal to the piecetomove
						middle = static_cast<int>(r);
						break;
					}
				}

				while (middle > 0)
				{
					
					board[static_cast<unsigned>(boardwidth*round((y1 + middle*sin(theta))) + round(x1 + middle*cos(theta)))] = piecetomove;
					--middle;

				}

			}
		}

		print();
		currentplayer = p2name;

	}

	if (currentplayer == p2name) {

		game_piece piecetomove;
		unsigned x1 = 0;
		unsigned y1 = 0;

		// player 1 is black and moves first
		piecetomove = game_piece(white, "reversi_white", "O");

		// prompting until we get valid coordinates
		bool validCoord = false;
		int retval = 3453;

		do
		{

			cout << currentplayer << ", it is your turn" << endl;

			if (done()) {
				throw DONE;
			}

			retval = gamebase::prompt(x1, y1);

			if (retval == QUIT) {
				throw QUIT;
				break;
			}
			if (retval == SUCCESS) {
				if (!validmove(piecetomove, x1, y1)) {
					cout << "Not a valid move... Try again" << endl;
					gamebase::prompt(x1, y1);
					validCoord = false;
				}
				else {
					validCoord = true;
				}
			}
		} while (retval != SUCCESS &&  validCoord);

		// doing the same thing as finding a valid move 

		// putting down piece
		board[boardwidth*y1 + x1] = piecetomove;
		if (x1 == 7) {
			for (double theta = M_PI / 2; theta <= 3 * M_PI / 2; theta = theta + (M_PI / 4.0)) { // iterating by pi/4 in a circle
				double polarHeight = round(y1 + sin(theta));
				double polarWidth = round(x1 + cos(theta));

				double angleIndex = boardwidth*polarHeight + polarWidth;

				if (static_cast<unsigned>(polarHeight) >= boardheight || static_cast<unsigned>(polarWidth) >= boardwidth) {
					break;
				}


				// if the the board's display is not the same as piece to move and it's not empty
				// checking the piece at r=1 distance away at the angle theta
				if (board[static_cast<unsigned>(angleIndex)].display != piecetomove.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

					int middle = 0;
					for (unsigned r = 1; r < boardheight; ++r) {
						double rpolarHeight = round(y1 + r*sin(theta));
						double rpolarWidth = round(x1 + r*cos(theta));


						double awayIndex = boardwidth*rpolarHeight + rpolarWidth;

						// when we find an opposite piece we go from r=2 to the end to find a piece that matches p
						if (static_cast<unsigned>(rpolarHeight) >= boardheight || static_cast<unsigned>(rpolarWidth) >= boardwidth) {
							break;
						}

						if (board[static_cast<unsigned>(awayIndex)].display == piecetomove.display) {
							// decrementing r until it's 0 and changing the pieces between to be equal to the piecetomove
							middle = static_cast<int>(r);
							break;
						}
					}

					while (middle > 0)
					{
						
						board[static_cast<unsigned>(boardwidth*round((y1 + middle*sin(theta))) + round(x1 + middle*cos(theta)))] = piecetomove;
						--middle;

					}

				}
			}
		}
		if (y1 == 7) {
			for (double theta = M_PI; theta <= 2 * M_PI; theta = theta + (M_PI / 4.0)) { // iterating by pi/4 in a circle
				double polarHeight = round(y1 + sin(theta));
				double polarWidth = round(x1 + cos(theta));

				double angleIndex = boardwidth*polarHeight + polarWidth;

				if (static_cast<unsigned>(polarHeight) >= boardheight || static_cast<unsigned>(polarWidth) >= boardwidth) {
					continue;
				}


				// if the the board's display is not the same as piece to move and it's not empty
				// checking the piece at r=1 distance away at the angle theta
				if (board[static_cast<unsigned>(angleIndex)].display != piecetomove.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

					int middle = 0;
					for (unsigned r = 1; r < boardheight; ++r) {
						double rpolarHeight = round(y1 + r*sin(theta));
						double rpolarWidth = round(x1 + r*cos(theta));


						double awayIndex = boardwidth*rpolarHeight + rpolarWidth;

						// when we find an opposite piece we go from r=2 to the end to find a piece that matches p
						if (static_cast<unsigned>(rpolarHeight) >= boardheight || static_cast<unsigned>(rpolarWidth) >= boardwidth) {
							continue;
						}

						if (board[static_cast<unsigned>(awayIndex)].display == piecetomove.display) {
							// decrementing r until it's 0 and changing the pieces between to be equal to the piecetomove
							middle = static_cast<int>(r);
							break;
						}
					}

					while (middle > 0)
					{
						
						board[static_cast<unsigned>(boardwidth*round((y1 + middle*sin(theta))) + round(x1 + middle*cos(theta)))] = piecetomove;
						--middle;

					}

				}
			}
		}
		// switching pieces in between
		for (double theta = 0; theta < (2 * M_PI); theta = theta + (M_PI / 4.0)) { // iterating by pi/4 in a circle
			double polarHeight = round(y1 + sin(theta));
			double polarWidth = round(x1 + cos(theta));

			double angleIndex = boardwidth*polarHeight + polarWidth;

			if (static_cast<unsigned>(polarHeight) >= boardheight || static_cast<unsigned>(polarWidth) >= boardwidth) {
				break;
			}


			// if the the board's display is not the same as piece to move and it's not empty
			// checking the piece at r=1 distance away at the angle theta
			if (board[static_cast<unsigned>(angleIndex)].display != piecetomove.display && board[static_cast<unsigned>(angleIndex)].display != " ") {

				int middle = 0;
				for (unsigned r = 1; r < boardheight; ++r) {
					double rpolarHeight = round(y1 + r*sin(theta));
					double rpolarWidth = round(x1 + r*cos(theta));


					double awayIndex = boardwidth*rpolarHeight + rpolarWidth;

					// when we find an opposite piece we go from r=2 to the end to find a piece that matches p
					if (static_cast<unsigned>(rpolarHeight) >= boardheight || static_cast<unsigned>(rpolarWidth) >= boardwidth) {
						break;
					}

					if (board[static_cast<unsigned>(awayIndex)].display == piecetomove.display) {
						// decrementing r until it's 0 and changing the pieces between to be equal to the piecetomove
						middle = static_cast<int>(r);
						break;
					}
				}

				while (middle > 0)
				{
					
					board[static_cast<unsigned>(boardwidth*round((y1 + middle*sin(theta))) + round(x1 + middle*cos(theta)))] = piecetomove;
					--middle;

				}

			}
		}

		print();
		currentplayer = p1name;

	}
}

unsigned Reversi::getDim()
{
	return boardwidth;
}

ofstream & operator<<(ofstream & ofs, const Reversi & rg)
{

	ofs << "ReversiGame" << endl;

	ofs << rg.currentplayer << " ";
	if (rg.currentplayer == rg.p1name) {
		ofs << rg.p2name << endl;
	}
	else {
		ofs << rg.p1name << endl;
	}

	for (unsigned int w = 0; w < rg.boardwidth; ++w) {
		for (unsigned int h = 0; h < rg.boardheight; ++h) {
			int index = rg.boardwidth * h + w;
			ofs << rg.board[index].color << " " << rg.board[index].name << " " << rg.board[index].display << " " << w << " " << h << endl;
		}
	}
	ofs << endl;
	return ofs;
}

ostream & operator<<(ostream & o, const Reversi & rg)
{
	// this should print out the current board
	if (sizeof(rg.board) > rg.boardwidth*(rg.boardheight - 1) + (rg.boardwidth - 1)) {
		cerr << "there are too many pieces for this board" << endl;
	}
	else {
		for (int y = rg.boardheight - 1; y >= 0;--y) {
			for (unsigned int x = 0;x <= rg.boardwidth - 1;++x) {
				if (x == (rg.boardwidth - 1)) {
					o << rg.board[(rg.boardwidth*y + x)].display << endl;
				}
				else {
					if (x == 0) {
						o << y << "  ";
					}
					o << rg.board[(rg.boardwidth*y + x)].display << "  ";
				}
			}
			o << "  " << endl;
		}
		for (unsigned int i = 0;i <= rg.boardwidth - 1;++i) {
			if (i == (rg.boardwidth - 1)) {

				o << i << endl;
			}
			else {

				if (i == 0) {
					o << "X" << "  ";
				}
				o << i << "  ";
			}
		}
	}
	return o;
}

string Reversi::getName()
{
	string s = "ReversiGame";
	return s;
}

