/*
 * File: Boggle.cpp
 * ----------------
 * Student ID: 5120379076
 * Name: 熊伟伦
 * This file is the main starter file for Boggle problem.
 */
 
#include <iostream>
#include <vector>
#include <algorithm>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "random.h"
#include "point.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

/* Variables */

Lexicon english("EnglishWords.dat");
bool big_boggle = false;
bool player_config = false;

/* function */

// get input about boggle size and source trace
void getParameter(bool& big_boggle, bool& player_config) {
	string input;
	cout << "You can choose standard Boggle (4x4 grid)" << endl;
	cout << "or Big Boggle (5x5)." << endl;
	while (1) {
		input = getLine("Would you like Big Boggle? [yes|no]:");
		input = toUpperCase(input);
		if (input=="YES" || input=="Y") {
			big_boggle = true;
			break;
		}
		else if (input=="NO" || input=="N") {
			big_boggle=false;
			break;
		}
	}
	cout << "I'll give you a chance to set up the board ";
	cout << "to your specification, which makes it easier to ";
	cout << "confirm your boggle program is working." << endl;
	while(1) {
		input = getLine("Do you want to force the boardconfiguration? [yes|no]:");
		input = toUpperCase(input);
		if (input=="YES" || input=="Y") {
			player_config = true;
			break;
		}
		else if (input=="NO" || input=="N") {
			player_config = false;
			break;
		}
	}
}

//get player input string
string getPlayer_String() {
	cout << "Enter a 16-character stringto identify which letter you ";
	cout << "want on the cubes. The first 4 letters are the cubes on the ";
	cout << "top row left to right, the next 4 letters are the second ";
	cout << "row, and so on" << endl;
	string input;
	while (1) {
		input = getLine("Enter the string:");
		if (big_boggle==true && input.length()==25)
			break;
		if (big_boggle==false && input.length()==16)
			break;
		if (big_boggle==true)
			cout << "String must include 25 characters! Try again.";
		else
			cout << "string must include 16 characters! Try again.";
	}
	return toUpperCase(input);
}

//start the game and graphics
Grid<char> startGame() {
	string src_str = "";
	if (player_config)	// player input string
		src_str = getPlayer_String();
	else {				// AI string
		int temp_num = (big_boggle)? 25:16;
		string *new_cubes;
		if (big_boggle)
			new_cubes =  const_cast<string*>(BIG_BOGGLE_CUBES);
		else
			new_cubes = const_cast<string*>(STANDARD_CUBES);
		string* begin = new_cubes;
		string* end = new_cubes + sizeof(new_cubes)/sizeof(string);
		random_shuffle(begin, end);
		for (int i = 0; i < temp_num; i++)
			src_str += new_cubes[i][randomInteger(0,5)];
	}
	big_boggle == true? drawBoard(5, 5) : drawBoard(4, 4);
	int temp_num = (big_boggle)? 5:4;
	Grid<char> grid(temp_num, temp_num);
	for (int i = 0; i < temp_num; i++)
		for (int j = 0; j < temp_num; j++) {
			grid[i][j] = src_str[temp_num*i+j];
			labelCube(i, j, char(src_str[temp_num*i+j]));
		}
	return grid;
}


void wordHighlight(const Vector<Point>& trace) {
	foreach(Point the_p in trace) {
		highlightCube(the_p.getY(), the_p.getX(), true);
		pause(50);
	}
	pause(250);	
}

void wordLowlight(const Vector<Point>& trace) {
	foreach(Point the_p in trace)
		highlightCube(the_p.getY(), the_p.getX(), false);
}

// player find recursion function
bool player_find(string word, Grid<char>& grid, Vector<Point>& trace) {
	int length = (big_boggle)? 5:4;
	if (trace.isEmpty()) { // find first char
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++)
				if (grid[i][j] == char(word[0])) {
					trace.add(Point(j,i));
					if (player_find(word, grid, trace))
						return true;
					else
						trace.remove(trace.size()-1);
				}
		}
		return false;
	}
	else { // not first char
		char the_char = char(word[trace.size()]);
		int pre_x = trace[trace.size()-1].getX();
		int pre_y = trace[trace.size()-1].getY();
		for (int j = pre_x-1; j <= pre_x+1; j++) {
			for (int i = pre_y-1; i <= pre_y+1; i++) {
				if (0<=i && i<length && 0<=j && j<length && !(j==pre_x && i==pre_y) && grid[i][j] == the_char) {
					bool temp_flag = false;
					foreach(Point the_p in trace)
						if (the_p == Point(j,i))
							temp_flag = true;		// have find this block
					if (temp_flag == false) {			// find it
						trace.add(Point(j,i));
						if (trace.size() == word.size())
							return true;
						if (player_find(word, grid, trace))
							return true;
						else
							trace.remove(trace.size()-1);
					}
				}
			}
		}
		return false;
	}
}

// player turn
Lexicon player_turn(Grid<char>& grid) {
	Lexicon player_words;
	while(1) {
		string input = getLine("Enter a word:");
		Vector<Point> trace;	// word trace
		if (input == "")
			break;
		if (input.length() < 4) {
			cout << "I'm sorry, but we have our standards." << endl;
			cout << "That word doesn't meet the miniumum word length." << endl;
		}
		else if(!english.contains(toLowerCase(input)))
			cout << "It is not a valid word!" << endl;
		else if (player_words.contains(toLowerCase(input)))
			cout << "You've already guessed that!" << endl;
		else {
			if (player_find(toUpperCase(input), grid, trace)) {
				recordWordForPlayer(toLowerCase(input), Player::HUMAN);
				player_words.add(toLowerCase(input));
				wordHighlight(trace);
				wordLowlight(trace);
			}
			else
				cout << "You can't make that word!" << endl;
		}
	}
	return player_words;
}

// computer find
bool computer_find(Grid<char>& grid, Lexicon& player_words, Vector<Point> trace, string word) {
	int length = (big_boggle)? 5:4;
	if (trace.isEmpty()) { // find first char
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				word += grid[i][j];
				trace.add(Point(j,i));
				computer_find(grid, player_words, trace, word);
				word = "";
				trace.clear();
			}
		}
	}

	else { // not first char
		if (!english.containsPrefix(word))
			return false;
		int pre_x = trace[trace.size()-1].getX();
		int pre_y = trace[trace.size()-1].getY();
		for (int j = pre_x-1; j <= pre_x+1; j++) {
			for (int i = pre_y-1; i <= pre_y+1; i++) {
				if (0<=i && i<length && 0<=j && j<length && !(j==pre_x && i==pre_y)) {
					bool temp_flag = false;
					string copy_word = word;
					Vector<Point>copy_trace = trace;
					foreach(Point the_p in copy_trace)
						if (the_p == Point(j,i))
							temp_flag = true;		// have find this block
					if (temp_flag == false) {		// find it
						copy_word += grid[i][j];
						copy_trace.add(Point(j,i));
						if (english.contains(copy_word) && !player_words.contains(copy_word) && copy_word.length()>=4 ) {
							recordWordForPlayer(toLowerCase(copy_word), Player::COMPUTER);
							player_words.add(toLowerCase(copy_word));
							wordHighlight(copy_trace);
							wordLowlight(copy_trace);
						}
						computer_find(grid, player_words, copy_trace, copy_word);
					}
				}
			}
		}
		return false;
	}
}

bool retry() {
	while(1) {
		string input = toUpperCase(getLine("Would you like to play again? [yes|no]:"));
		if (input == "Y" || input == "YES")
			return true;
		if (input == "N" || input == "NO")
			return false;
	}
}

/* Main program */

int main() {
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	initGBoggle(gw);
	welcome();
	giveInstructions();

	do {
		getParameter(big_boggle, player_config);
		Grid<char> grid = startGame();
		Lexicon player_words = player_turn(grid);
		Vector<Point> trace; string word;
		computer_find(grid, player_words, trace, word);
		if (!retry())
			break;
	}while(1);
	return 0;
}
