// Lab4v2.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "Lab2Helper.h"

#include "GameBase.h"
#include "NineAlmondsGame.h"

using namespace std;

int main(int argc, char* argv[])
{

	// Reading input message
	try {
		gamebase::inputmessage(argc, argv);
	}
	catch (failuretype e) {
		if (e == INCORRECTNUMARGS) {
			cout << "Incorrect number of arguments. Try again." << endl;
			usage(argv[PROGRAM_NAME]);
			return INCORRECTNUMARGS;
		}
		else if (e == INCORRECTLY_FORMATTED_INPUT) {
			cout << "Incorrectly formatted input. Try again." << endl;
			usage(argv[PROGRAM_NAME]);
			return INCORRECTLY_FORMATTED_INPUT;
		}
		else if (e == BAD_ALLOCATION) {
			return BAD_ALLOCATION;
		}
		else {
			return BADPOINTER;

		}

	}
	catch (...) {
		return UNKNOWN_ERROR;
	}

	int result = gamebase::instance()->play();
	if (result == DONE) {
		cout << "Success! Game Over! The game is done." << endl;
	}

	return result;
}



