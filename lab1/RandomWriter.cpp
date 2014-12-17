/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name: 熊伟伦
 * Student ID: 5120379076
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"
#include "simpio.h"
using namespace std;
#define MAX_CHAR_NUM 2000

//get filename
void read_file(ifstream& file_input);

//get order number
int read_order();

//build model
void model_read(ifstream& file_input, const int& order, Map<string, Vector<char> >& model);

//write
void random_write(const int& order, Map<string, Vector<char> >& model);

void read_file(ifstream& file_input) {
	while(1) {
		string file_name = getLine("Please enter filename containing source text:");
		file_input.open(file_name.c_str());
		if (file_input)
			break;
	}
}

int read_order() {
	while(1) {
		int order = getInteger("What order to analysis? (a number from 1 to 10):");
		if (order>0 && order<11)
			return order;
		else
			cout << "Try again.\n"; 
	}
}

void model_read(ifstream& file_input, const int& order, Map<string, Vector<char> >& model) {
	char ch;
	string block;
	for (int i = 0; i < order; i++) {	//read first block
		file_input.get(ch);
		block += ch;
	}
	while(file_input.get(ch)) {
		if (model.containsKey(block))	//if exist the block
			model[block].add(ch);
		else {							//if not exist
			Vector<char> temp;
			temp.add(ch);
			model.put(block, temp);		//put into model
		}
		block.erase(0,1);				
		block += ch;
	}
}

void random_write(const int& order, Map<string, Vector<char> >& model) {
	string seed;
	int max_vec = 0;
	int count = order; 
	foreach(string block in model) {	//get init seed
		if (model[block].size() > max_vec) {
			max_vec = model[block].size();
			seed = block;
		}
	}
	cout << seed;
	while(count < MAX_CHAR_NUM) {		//update seed
		if (!model.containsKey(seed))
			break;
		char ch = model[seed][ randomInteger(0, model[seed].size()-1) ];
		cout << ch;
		count++;
		seed.erase(0,1);
		seed += ch;
	}
}

int main() {
	ifstream file_input;
	read_file(file_input);
	int order = read_order();
	cout << "Analyzing ... please wait." << endl;
	Map<string, Vector<char> > model;
	model_read(file_input, order, model);
	file_input.close();
	random_write(order, model);
	exit(0);
	return 0;
}
