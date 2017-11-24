#include "porterWord.h"


using namespace std;



PorterWord::PorterWord(string porterWord)
{
	word = porterWord;
}

PorterWord::PorterWord(string porterWord, int id)
{
	word = porterWord;
	oldIds.push_back(id);
}


PorterWord::~PorterWord()
{
}

string PorterWord::getWord()
{
	return word;
}

vector<int> PorterWord::getOldIds()
{
	return oldIds;
}

void PorterWord::addOldId(int id)
{
	oldIds.push_back(id);
}

bool PorterWord::idInOldIds(int id)
{
	if(find(oldIds.begin(), oldIds.end(), id) != oldIds.end())
	{
		return true;
	}
	return false;
}
