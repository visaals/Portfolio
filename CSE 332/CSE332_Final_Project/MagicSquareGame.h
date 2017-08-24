#pragma once
#include "GameBase.h"
#include<ostream>

using namespace std;



class MagicSquareGame : virtual public gamebase

{
	friend ostream & operator<< (ostream & os, const MagicSquareGame & msg);

	friend ofstream & operator<< (ofstream & ofs, const MagicSquareGame & ofmsg );
public:
	MagicSquareGame();

	MagicSquareGame(vector<magicPiece>, unsigned, unsigned);

	virtual bool done() override;
	virtual bool stalemate() override;
	virtual void prompt(unsigned &);
	virtual void turn();
	virtual void print() override;

	virtual void save() override;

	virtual unsigned getDim();
	virtual string getName(); 

	


private:
	int max_length;
	vector<magicPiece> board;
	vector<magicPiece> remainingPieces;
	unsigned int boardwidth;
	unsigned int boardheight;

};
ostream & operator<< (ostream &, const MagicSquareGame &);
ofstream & operator<< (ofstream &, const MagicSquareGame &);