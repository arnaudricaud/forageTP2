#pragma once
#include <string.h>
#include <vector>


using namespace std;

class PorterWord
{
private:
	vector<int> oldIds;
	string word;

public:

	PorterWord(string porterWord);
	~PorterWord();
	string getWord();
	vector<int> getOldIds();
	void addOldId(int id);
};
