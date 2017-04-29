#ifndef Lab2Help_H
#define Lab2Help_H

#include <string>
#include <iostream>
using namespace std;

enum failuretype {
	SUCCESS = 0,
	QUIT,
	INCORRECTLY_FORMATTED_INPUT,
	DONE,
	FAILEXTRACTION,
	TOOMANYPIECES,
	INCORRECTNUMARGS,
	YES,
	NO,
	STALEMATE_RETURN,
	NOT_VALID_MOVE,
	BAD_ALLOCATION,
	UNKNOWN_ERROR,
	GAMEOVER,
	BADPOINTER,
	FILE_FAILED_TO_OPEN,
	FAILED_EXTRACTION,
	NODATA
};

enum files {
	fileName = 1,
	numberOfArgs = 2,

};

enum array_indexes {
	PROGRAM_NAME,
	GAME_NAME,
	P1NAME,
	P2NAME
};

enum dimensions {
	m_width = 3,
	m_height = 3,
	board_width = 5,
	board_height = 5,
	r_width = 8,
	r_height = 8

};


void usage(char * program_name);

#endif // !Lab2Help_H
