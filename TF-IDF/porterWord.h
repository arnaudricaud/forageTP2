#pragma once
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

class PorterWord
{
private:
	vector<int> oldIds;
	string word;

public:

	PorterWord(string porterWord);
	PorterWord(string, int);
	~PorterWord();
	string getWord();
	vector<int> getOldIds();
	void addOldId(int id);
	bool idInOldIds(int id);
};
