#include "stdafx.h"
#include "gamepiece.h"


// default constructor
game_piece::game_piece()
	: color(noCol), name(""), display("initial display"), value(0)
{}
// constructing the game_piece for NineAlmonds
game_piece::game_piece(piece_color color, string name, string display)
	: color(color), name(name), display(display), value(0) {}

// default constructor for  magic square game 
magicPiece::magicPiece()
	: name(""), display("initial display"), value(0)
{
}

// constructing the gamepiece  
magicPiece::magicPiece(string name, string display, unsigned value)
	: name(name), display(display), value(value)
{
}


piece_color stringToColor(string & string)
{
	
	if (string == "3")
	{
		return black;
	}
	if (string == "2")
	{
		return white;
	}


	if (string == " " || "	" || "0" )
	{
		return noCol;
	}
	else
	{
		return invalidColor;
	}
}