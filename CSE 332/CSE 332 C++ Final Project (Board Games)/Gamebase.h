#pragma once 
// This is the file where we create our Gamebase which is inherited in all subsequent implementations

#include "gamepiece.h"
#include "Lab2Helper.h"

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <istream>
#include <fstream>
#include <memory>
using namespace std;


class gamebase {
	friend ostream & operator<< (ostream &, const gamebase &);
	friend ofstream & operator<< (ofstream &, const gamebase &);

public:
	// default constructor, destructor, and member funcitons as instructed
	gamebase();
	~gamebase();

	static shared_ptr<gamebase> instance();

	void getMaxLength(vector<game_piece> & gpvec);

	virtual bool done()=0;
	virtual void print() =0 ;

	virtual void save()=0;
	virtual bool stalemate()=0;
	virtual int  prompt(unsigned &, unsigned &);
	

	virtual void turn()=0;
	virtual int play();
	virtual unsigned getDim();

	virtual string getName() = 0; 



	static void inputmessage(int argc, char* argv[]);

protected:
	static shared_ptr<gamebase> shared;


	int max_length;
	// variables that are common to all games as instructed in the lab assignment page
	vector<game_piece> board;
	unsigned boardwidth;
	unsigned boardheight;

private:

};


ostream & operator<< (ostream &, const gamebase &);

ofstream & operator <<(ofstream &, const gamebase &);