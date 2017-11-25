#pragma once
#include <vector>

using namespace std;
class Document
{
private:
	int id;
	vector<int> wordFreq;

public:
	Document(int idDoc);
	~Document();
	void addWord(int id);
	vector<int> getWords();
};

