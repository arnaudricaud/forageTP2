#pragma once
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "porterWord.h"

using namespace std;

class Porter
{
private:
	map<int, string> words;
	vector<PorterWord*> porterWords;
	string wordFileName;

public:
	Porter(string);
	void applyPorter(string);
	int getConsonantNb(string);
	bool vowelInWord(string word, int suffix);
	bool endDoubleLetter(string word);
	bool isVowel(char letter);
	bool cvcEnd(string word);
	bool wordEndWith(string word, string end);
	string porterProcessStep1(string word, int nbconsonant);
	void writeFinalWords(string);
};
