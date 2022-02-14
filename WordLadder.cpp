#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

WordLadder::WordLadder(const string &inputFile)
{
	ifstream inF;
	inF.open(inputFile.c_str());
	if(!inF.is_open()) {
		cout << "Opening input file error." << endl;
	}
	else {
		string word;
		while(!inF.eof()) {
			inF >> word;
			if (word.length()!=5) {
				cout << "Error: Word must have 5 characters." << endl;
				return;
			}
			dict.push_back(word);
		}
		inF.close();
	}
}

void WordLadder::outputLadder (const string &start, const string &end, const string &outputFile) {
	ofstream outF;
	outF.open(outputFile.c_str());
	if (!outF.is_open()) {
		cout << "Fail to open output file." << endl;
	}
	queue<stack<string> > initialQ;
	stack<string> initialS;
	string word;
	list<string>::iterator item;
	//find if there exist start word and end word in dictionary
	bool startWord = false, endWord = false;
	for (item=dict.begin(); item!=dict.end(); ++item) {
		if (*item == start) {
			startWord = true;
		}
		if (*item == end) {
			endWord = true;
		}
	}
	if(!startWord || !endWord) {
		cout << "At least one of the words not found in dictionary." << endl;
		return;
	}
	if (start == end)
	{
		outF << start;
		outF.close();
		return;
	}
	//first word in word ladder
	initialS.push(start);
	initialQ.push(initialS);
	while(!initialQ.empty()) {
		word = initialQ.front().top();
		for (item=dict.begin(); item!=dict.end(); ++item) {
			if (check(word,*item)) {
				stack<string> copyS = initialQ.front();
				copyS.push(*item);
				//found end
				if(*item == end) {
					outputToFile(copyS, outF);
					return;
				}
				// push new stack in queue
				initialQ.push(copyS);
				item = dict.erase(item);
				//relocate the pointer due to ++item in for loop
				--item;
			}
		}
		initialQ.pop();
	}
	
	if(outF.is_open()) {
		outF << "No Word Ladder Found.";	
	}
}

bool WordLadder::check (string inWord, string itm) {
	int match = 0;
	for (int i = 0; i < 5; i++) {
		if (inWord[i] == itm[i])
		{
			match++;
		}
	}
	if (match == 4) {
		return true;
	} else {
		return false;
	}
}

void WordLadder::outputToFile(stack<string> stack, ofstream &out) {
	int i = 0;
	vector<string> ladder;
	
	while (!stack.empty()) {
		ladder.push_back(stack.top());
		stack.pop();
		i++;
	}
	
	if (out.is_open()) {
		while(i!=0) {
			i--;
			out << ladder.at(i);
			if (i !=0) {
				out << " ";
			}
		}
	}
}
