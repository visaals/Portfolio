#pragma once
#include "Gamebase.h"



class  Reversi : public gamebase {
	friend ostream & operator<< (ostream & o, const Reversi & rg);
	friend ofstream & operator<< (ofstream & ofs, const Reversi & rg);

public:
	Reversi(string p1, string p2);

	virtual void print() override;
	virtual void save() override;

	virtual bool done() override;
	virtual bool stalemate() override;

	virtual void turn();


	bool validmove(game_piece, const unsigned, const unsigned);
	virtual unsigned getDim();

	virtual string getName(); 

private:
	string p1name;
	string p2name;
	string currentplayer;
	vector<game_piece> board;
	unsigned boardwidth;
	unsigned boardheight;

};



ostream & operator<< (ostream &, const Reversi &);
ofstream & operator<< (ofstream &, const Reversi &);

