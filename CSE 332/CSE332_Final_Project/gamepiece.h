#pragma once 


#include <string>


using namespace std;
enum piece_color {
	noCol = 0,
	brown = 1,
	white = 2,
	black = 3,
	invalidColor = 4
};

piece_color stringToColor(string &);

struct	game_piece {
	game_piece();

	game_piece(piece_color, string, string);

	game_piece(string, string, unsigned);

	piece_color color;
	string name;
	string display;
	unsigned value;
};

struct magicPiece
{
	magicPiece();
	magicPiece(string, string, unsigned);

	string name;
	string display;
	unsigned value;
};