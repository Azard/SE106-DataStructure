/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: 熊伟伦
 * Student ID: 5120379076
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"
using namespace std;

//find the dest and init
void show_ans(Vector<string>& ans);

//input and start function
void input_words(string& start, string& dest);

void show_ans(Vector<string>& ans) {
	cout << "Found ladder:";
	for (int i = 0; i < ans.size(); i++)
		cout << " " << ans[i] ;
	cout << endl;
}

void input_words(string& start, string& dest) {
	cout << "Enter start word (RETURN to quit):";
	getline(cin, start);
	if (start.size() == 0)
		exit(0);
	cout << "Enter destination word:";
	getline(cin, dest);
}

int main() {
	while(1) {
		/* initialize begin */
		bool find_flag = false;
		Lexicon english("EnglishWords.dat");
		Lexicon used_words;						//save used words
		Queue< Vector<string> > search_queue;	//save words will be search
		Vector<string> trans_vector;			//add new vector to queue
		string start, dest;						//save start and destination words
		input_words(start, dest);				//input words and init
		trans_vector.add(start);
		search_queue.enqueue(trans_vector);
		used_words.add(start);
		/* initialize end  */
		if (start.size() != dest.size() || !english.contains(start) || !english.contains(dest) || start == dest) {
			cout << "No Ladder found." << endl;
			continue;
		}
		while(!search_queue.isEmpty()) {
			trans_vector = search_queue.dequeue();	//remove the first ladder
			string last_word = trans_vector[trans_vector.size()-1];
			string change_word = "";
			if (last_word == dest) {	//if find 
				show_ans(trans_vector);
				find_flag = true;
				break;
			}
			for (int i = 0; i < last_word.length(); i++)
				for (char j = 'a'; j <= 'z'; j++) {
					change_word = last_word;
					change_word[i] = j;
					if (english.contains(change_word) && !used_words.contains(change_word)) {
						Vector<string> copy_ladder = trans_vector;
						copy_ladder.add(change_word);
						used_words.add(change_word);
						search_queue.enqueue(copy_ladder);
					}
				}
		}
		if (!find_flag)
			cout << "No Ladder found." << endl;
	}
	return 0;
}
