#include "stdafx.h"
#include "MagicSquareGame.h"
#include "Lab2Helper.h"
#include <string>
#include <sstream>

using namespace std;


MagicSquareGame::MagicSquareGame(vector<magicPiece> vgp, unsigned width, unsigned height)
	: board(vgp), boardwidth(width), boardheight(height)
{
}

MagicSquareGame::MagicSquareGame()
	: boardwidth(m_width), boardheight(m_height)
{

	int counter = 0;
	string line;
	string display;
	string name;
	string color;
	unsigned width;
	unsigned height;

	fstream file("MagicSquareGame.txt");

	if (file.is_open())
	{

		while (getline(file, line))
		{

			istringstream iss(line);


			if (line == "NODATA") {
				cout << "nodata in first line" << endl;
				for (int i = 0; i < m_width*m_height; ++i) {
					board.push_back(magicPiece(" ", " ", 0));

					//inserting into the remaining pieces vector
					string num = to_string(i + 1);
					remainingPieces.push_back(magicPiece(" ", num, i + 1));
				}
			} else {
				if (line == "MagicSquare") {
					for (int i = 0; i < m_width*m_height; ++i) {
						board.push_back(magicPiece(" ", " ", 0));

						//inserting into the remaining pieces vector
						string num = to_string(i + 1);

						remainingPieces.push_back(magicPiece(" ", num, i + 1));
					}

					istringstream iss(line);

				}


				if (iss >> color &&  iss >> display && iss >> width && iss >> height)
				{

					if (width < boardwidth && height < boardheight) {

						//name,display,value
						unsigned display_num = atoi(display.c_str());

						magicPiece curPiece{ "", display, display_num };
						int index = boardwidth * height + width;
						
						board[index] = curPiece;
						counter++;
					}

				}
			
			}

			
			}

			//this for loop erases the correct values from the remainingPieces vector
			for (int i = 0; i < m_width*m_height; ++i) {

				//if the board display contains a number
				if (board[i].display != " ") {
					int used_num = board[i].value;

					for (size_t j = 0; j < remainingPieces.size(); ++j) {
						if (remainingPieces[j].value == used_num) {
							remainingPieces[j] = magicPiece(" ", " ", 0);
						}
					}
				}

			}

			

	}
	else
	{
		cerr << "No save currently exists... creating new game." << endl;
		for (int i = 0; i < m_width*m_height; ++i) {
			board.push_back(magicPiece(" ", " ", 0));

			//inserting into the remaining pieces vector
			string num = to_string(i + 1);
			remainingPieces.push_back(magicPiece(" ", num, i + 1));
		}
		
	}

}

bool MagicSquareGame::done()
{
	int successcout = 0;
	// creating a vector of the sums that must be equal for the game to be done
	vector<int> sums;

	int sum = 0;
	for (unsigned int x = 0; x < boardwidth; ++x) {
		for (unsigned int y = 0; y < boardheight; ++y) {
			if (board[boardwidth*y + x].value != 0) {

				successcout++;
			}
		}
	}
	//if there is an element in every position of the board, the game isn't done
	if (successcout != boardwidth*boardheight) {
		return false;
	}

	else if (successcout == boardwidth*boardheight) {
		//checking x sums
		for (unsigned int x = 0; x < boardwidth; ++x) {
			sum = 0;
			for (unsigned int y = 0;y < boardheight; ++y) {
				sum += board[boardwidth*y + x].value;
			}
			// putting the sums into the sums vec
			sums.push_back(sum);
		}

		//checking y sums
		for (unsigned int y = 0; y < boardheight; ++y) {
			sum = 0;
			for (unsigned int x = 0;x < boardwidth; ++x) {
				sum += board[boardwidth*y + x].value;
			}
			sums.push_back(sum);
		}

		//checking diagonal
		int diag1sum = 0;
		for (unsigned int x = 0; x < boardwidth; ++x) {
			for (unsigned int y = 0;y < boardheight; ++y) {
				if (y == x) { // this is the equation for the first diagonal of the board
					diag1sum += board[boardwidth*y + x].value;
				}
			}

		}
		sums.push_back(diag1sum);

		//checking other diagonal
		int diag2sum = 0;
		for (unsigned int x = 0; x < boardwidth; ++x) {
			for (unsigned int y = 0;y < boardheight; ++y) {
				if (y == (boardheight - x - 1)) { // this is the equation for the second diagonal of the board
					diag2sum += board[boardwidth*y + x].value;
				}
			}
		}
		sums.push_back(diag2sum);

		for (size_t i = 1; i < sums.size();++i) {

			if (sums[i] != sums[i - 1]) {
				// if the sums aren't the `me, the game isn't done
				return false;
			}
		}

	}
	return true;
}
bool MagicSquareGame::stalemate()
{
	//this is only supposed to return false if all the pieces are entered and
	//they do not equal the value expected. According to the directions we do not need to
	//check everytime. I copied the done method and change the two return values at the end

	while (!done()) {
		int successcout = 0;
		vector<int> sums;

		int sum = 0;
		for (unsigned int x = 0; x < boardwidth; ++x) {
			for (unsigned int y = 0; y < boardheight; ++y) {
				if (board[boardwidth*y + x].value != 0) {
					successcout++;
				}
			}
		}
		//if there is not a piece in every place
		if (successcout != boardwidth*boardheight) {
			return false;
		}
		else if (successcout == boardwidth*boardheight) {
			//checking x sums
			for (unsigned int x = 0; x < boardwidth; ++x) {
				sum = 0;
				for (unsigned int y = 0; y < boardheight; y++) {
					sum += board[boardwidth*y + x].value;
				}
				sums.push_back(sum);
			}
			//checking y sums
			for (unsigned int y = 0; y < boardheight; ++y) {
				sum = 0;
				for (unsigned int x = 0; x < boardwidth; ++x) {
					sum += board[boardwidth*y + x].value;
				}
				sums.push_back(sum);
			}
			//checking diagonal
			int diag1sum = 0;
			for (unsigned int x = 0; x < boardwidth; ++x) {
				for (unsigned int y = 0;y < boardheight; ++y) {
					if (y == x) { // this is the equation for the first diagonal of the board
						diag1sum += board[boardwidth*y + x].value;
					}
				}

			}
			sums.push_back(diag1sum);

			//checking other diagonal
			int diag2sum = 0;
			for (unsigned int x = 0; x < boardwidth; ++x) {
				for (unsigned int y = 0;y < boardheight; ++y) {
					if (y == (boardheight - x - 1)) { // this is the equation for the second diagonal of the board
						diag2sum += board[boardwidth*y + x].value;
					}
				}
			}
			sums.push_back(diag2sum);


			for (size_t i = 1; i < sums.size(); ++i) {

				if (sums[i] != sums[i - 1]) {
					return true;
				}
			}

		}

		return false;
	}

	return true;

}

// this is the prompt for the piece to move in the Magic Square game:
// takes in the piece number by reference and stores the value entered by the user in that number
void MagicSquareGame::prompt(unsigned & number)
{

	number = 0;
	bool validInput = false;

	while (!validInput)
	{
		cout << "Please enter the number of an unplayed piece. Or type quit to end the game." << endl;

		string line;
		getline(cin, line);
		// fixing a bug where it reads a blank line
		if (line == "")
		{
			getline(cin, line);
		}

		if (line == "quit")
		{
			bool ans = true;
			while (ans) {

				cout << "would you like to save this game?? y/n" << endl;
				string response = "";
				cin >> response;
				if (response == "yes" || response == "y" || response == "yes") {
					//save DATA
					save();
					ans = false;
				}
				else if (response == "No" || response == "n" || response == "no")
				{
					//save NODATA
					string name = getName() + ".txt";

					ofstream ofs(name);

					ofs << "NODATA" << endl;

					ans = false;
				}
				else {
					cout << "sorry I did not understand. Please say y or n" << endl;
				}
			}
			throw QUIT;
		}

		istringstream buffer(line);
		unsigned int extracted_num;

		if (buffer >> extracted_num)
		{
			if (extracted_num > 0 && extracted_num <= (boardwidth)*(boardheight)) {
				for (size_t i = 0; i < remainingPieces.size(); i++)
				{
					if (remainingPieces[i].value == extracted_num)
					{
						// checking that the piece is within the boundries for allowed pieces and then checking if it has been played before

						number = extracted_num;
						validInput = true;
					}
				}
			}
			else {
				cout << "Please enter an integer between 1 and " << (boardwidth)*(boardheight) << endl;
				break;
			}
		}
		else
		{
			cout << "Please enter a valid integer" << endl;
			break;
		}

	}
}
void MagicSquareGame::turn()
{
	bool validNum = false;
	unsigned numberToMove;

	// prompting until we get a valid move
	do
	{
		MagicSquareGame::prompt(numberToMove);

		if (numberToMove > 0 && numberToMove <= (boardwidth*boardheight)) {
			for (size_t i = 0; i < remainingPieces.size(); i++)
			{
				if (remainingPieces[i].value == numberToMove)
				{
					validNum = true;
				}

			}

		}


	} while (!validNum);


	bool validCoord = false;
	unsigned c1, c2;

	// prompting until we get valid coordinates
	int retval = 3453;
	do
	{

		retval = gamebase::prompt(c1, c2);

		if (retval == QUIT) {
			throw QUIT;
			break;
		}
		if (retval == SUCCESS) {
			if (board[boardwidth*c2 + c1].display != " ") {
				cout << "there's already a piece there... Try again" << endl;
				gamebase::prompt(c1, c2);
				validCoord = true;
			}
		}
	} while (retval != SUCCESS &&  validCoord);

	board[boardwidth*c2 + c1] = remainingPieces[numberToMove - 1];

	// clearing magic piece in the remainingPieces vector

	remainingPieces[numberToMove - 1] = magicPiece("  ", "  ", 0);

	print();


}

void MagicSquareGame::print()
{
	cout << *this << endl;
}

void MagicSquareGame::save()
{

	ofstream ofs("MagicSquareGame.txt");
	ofs << *this << endl;
}
unsigned MagicSquareGame::getDim()
{
	return boardwidth;
}

string MagicSquareGame::getName()
{
	string s = "MagicSquareGame";
	return s;
}

ofstream & operator<<(ofstream & ofs, const MagicSquareGame & ofmsg)
{


	ofs << "MagicSquare" << endl;

	for (unsigned int w = 0; w < ofmsg.boardwidth; ++w) {
		for (unsigned int h = 0; h < ofmsg.boardheight; ++h) {
			int index = ofmsg.boardwidth * h + w;
			ofs << "0" << " " << ofmsg.board[index].name << " " << ofmsg.board[index].display << " " << w << " " << h << endl;
		}
	}

	ofs << endl;
	return ofs;
}


ostream & operator<<(ostream &o, const MagicSquareGame &msg)
{
	// this should print out the current board
	if (msg.board.size() > m_width*m_height) {
		cout << msg.board.size() << " " << msg.boardheight << " " << msg.boardwidth << endl;
		cerr << "there are too many pieces for this board" << endl;
	}
	else {

		for (int y = msg.boardheight - 1; y >= 0;--y) {
			for (unsigned int x = 0;x <= msg.boardwidth - 1;++x) {
				if (x == (msg.boardwidth - 1)) {
					// printing the piece at the proper location in the gameboard vector
					o << msg.board[(msg.boardwidth*y + x)].display << endl;
				}
				else {
					if (x == 0) {
						o << y << " ";
					}
					o << msg.board[(msg.boardwidth*y + x)].display << " ";
				}
			}
			o << " " << endl;
		}
		for (unsigned int i = 0;i <= msg.boardwidth - 1;++i) {
			if (i == (msg.boardwidth - 1)) {

				o << i << endl;
			}
			else {

				if (i == 0) {
					o << "X" << " ";
				}
				o << i << " ";
			}
		}
		cout << "Pieces left: ";
		for (unsigned int i = 0; i < msg.boardwidth*msg.boardheight; ++i) {
			cout << msg.remainingPieces[i].display << " ";
		}
		cout << endl;
	}
	return o;
}