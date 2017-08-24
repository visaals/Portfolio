#pragma once 

#include "GameBase.h"
#include "gamepiece.h"


#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

class NineAlmondsGame : virtual public gamebase {

	friend ostream & operator<< (ostream & os, const NineAlmondsGame & nag);
	friend ofstream & operator<< (ofstream & ofs, const NineAlmondsGame & ofnag);

public:

	NineAlmondsGame();
	NineAlmondsGame(vector<game_piece>, unsigned, unsigned);

	int max_length;

	virtual bool done() override;
	virtual bool stalemate() override;

	virtual void turn();
	virtual int play();

	

	void turnhelper(unsigned & currentXh, unsigned & currentYh);

	bool validmove(const unsigned, const unsigned, const unsigned, const unsigned);
	int turn_prompt();

	virtual void print() override;

	virtual void save() override;
	virtual unsigned getDim();
	virtual string getName();


private:
	vector<game_piece> board;
	unsigned boardwidth;
	unsigned boardheight;


};

ostream & operator<< (ostream &, const NineAlmondsGame &);
ofstream & operator<< (ofstream &, const NineAlmondsGame &);