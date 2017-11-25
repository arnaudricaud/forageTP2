#include "document.h"


using namespace std;

Document::Document(int idDoc)
{
	id = idDoc;
}


Document::~Document()
{
}

void Document::addWord(int wordId)
{
	wordFreq.push_back(wordId);
}

int Document::getId() {
	return id;
}

vector<int> Document::getWords() {
	return wordFreq;
}
