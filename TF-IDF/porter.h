#pragma once
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

class Porter
{
private:
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
};

