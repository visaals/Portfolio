#include "stdafx.h"

#include "GameBase.h"
#include "NineAlmondsGame.h"

#include "MagicSquareGame.h"
#include "ReversiGame.h"


gamebase::gamebase()
{}

gamebase::~gamebase()
{}

shared_ptr<gamebase> gamebase::shared = nullptr;

shared_ptr<gamebase> gamebase::instance()
{
	if (shared != nullptr) {
		return shared;
	}
	else {
		throw BADPOINTER;
	}
}

void gamebase::getMaxLength(vector<game_piece>& gpvec)
{

	// iterating through the vecotor of gamepieces and finding the piece that has the max length and setting that 
	// to be the max length. Return this value
	for (size_t i = 0; i < gpvec.size(); ++i) {
		auto display_len = gpvec[i].display.length();
		if (static_cast<int>(display_len) > max_length) {
			max_length = display_len;
		}
	}
}


int gamebase::play()
{
	print();

	while (!stalemate() && !done())
	{
		try
		{
			turn();	
		}
		catch (enum failuretype q)
		{
			return q;
		}
		catch (...) {
			cout << "Unknown exception" << endl;
		}

	}
	if (stalemate()) {
		cout << "Game has reached stalemate! " << endl;
		return  STALEMATE_RETURN;
	}
	if (done()) {
		cout << "Success! Game Over! The game is done. " << endl;
		return SUCCESS;
	}


	return SUCCESS;
}

unsigned gamebase::getDim()
{
	// getter to access the private variable outside the scope of the class
	return boardwidth;
}



void gamebase::inputmessage(int argc, char * argv[])
{
	if (shared != nullptr) {
		throw BADPOINTER;
	}
	else {

		if (argc != 1) {

			if (strcmp("NineAlmonds", argv[GAME_NAME]) == 0) {
				if (argc != 2) {
					throw INCORRECTNUMARGS;
				}
				try {

					shared = make_shared <NineAlmondsGame>();

				}
				catch (bad_alloc) {
					throw BAD_ALLOCATION;
				}

			}
			else if (strcmp("MagicSquare", argv[GAME_NAME]) == 0) {
				if (argc != 2) {
					throw INCORRECTNUMARGS;
				}

				try {
					shared = make_shared <MagicSquareGame>();

				}
				catch (bad_alloc) {
					throw BAD_ALLOCATION;
				}
			}

			else if (strcmp("Reversi", argv[GAME_NAME]) == 0) {
				if (argc != 4) {
					throw INCORRECTNUMARGS;
				}
				try {
					shared = make_shared <Reversi>(argv[P1NAME], argv[P2NAME]);
				}
				catch (bad_alloc) {
					throw BAD_ALLOCATION;
				}

			}
			else {
				throw INCORRECTLY_FORMATTED_INPUT;
			}
		}
		else {
			throw INCORRECTLY_FORMATTED_INPUT;
		}


	}
}



int gamebase::prompt(unsigned & int1, unsigned & int2)
{
	while (true) {
		string line;
		int successcount = 0;

		cout << "Type coordinates  x,y  x between 0 & " << this->getDim() - 1 << " & y between 0 & " << this->getDim() - 1 << " or 'quit'" << endl;

		getline(cin, line);

		//cin >> line;

		// If user quit, start new prompt 
		if (line == "quit") {
			bool ans = true;
			while (ans) {

				cout << "would you like to save this game?? y/n" << endl;
				string response = "";
				cin >> response;
				if (response ==  "yes" || response == "y" || response == "Yes") {
					//save DATA
					save();
					ans = false;
				}
				else if (response =="No" || response == "n" || response == "no")
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
			cout << "User quit game" << endl;
			break;
		}

		int digitlength = 0;
		// making sure the input is correctly formatted: an ordered pair seperated by a comma 
		if (line.length() == 3) {
			for (char letter : line) {
				if (isdigit(letter))
				{
					digitlength++;
				}
			}
			if (digitlength == 2) {

				for (char & letter : line) {
					if (letter == ',') {
						letter = ' ';
					}
				}
				istringstream iss(line);
				if (iss >> int1) {
					successcount++;
				}
				if (iss >> int2) {
					successcount++;
				}
				if (int1 < 0 || int1 > this->getDim() - 1 || int2 < 0 || int2> this->getDim() - 1) {
					cout << "inputs need to be between 0 and " << this->getDim() - 1 << endl;
					prompt(int1, int2);

				}
			}
			else {
				cout << "INCORRECTLY_FORMATTED_INPUT" << endl;

			}
		}
		else
		{
			cout << "INCORRECTLY_FORMATTED_INPUT" << endl;
		}
		if (successcount == 2) {
			return SUCCESS;
		}
	}
	return QUIT;
}



ofstream & operator<<(ofstream &ofs, const gamebase &bg)
{
	return ofs;
}

ostream & operator<<(ostream & os, const gamebase & gb)
{
	return os;
}