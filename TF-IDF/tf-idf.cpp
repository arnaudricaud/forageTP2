#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class TfIdf
{
private:
	string finalDocName;
	int nbDocs;
	int nbWordsInitial;
	vector< vector<int> >* docwords;
	vector<string>* words;
	string inputFilePart1;
	string inputFilePart2;
	vector< map<int, int> > docTermFrequency;
	map<int, int> wordFreqCorpus;

public:
	TfIdf()
	{
		this->nbDocs = 128804;
		this->nbWordsInitial = 30799;
		this->docwords = new vector< vector<int> >();
		this->words = new vector<string>();
		this->inputFilePart1 = "../Data/nsfabs_part";
		this->inputFilePart2 = "_out/docwords.txt";
		this->finalDocName = "tfidfs.txt";
	}

	~TfIdf();

	void ReadInputFiles()
	{
		for(int i=1; i<=3; i++)
		{
			ostringstream oss;
			oss << this->inputFilePart1 << i << this->inputFilePart2;
			string filename = oss.str();
			ParseFile(filename);
		}
	}

	void ParseFile(string filename)
	{
		ifstream infile;
		infile.open(filename.c_str());

		if(!infile)
		{
			cerr<<"Error while loading doc " << filename << endl;
			return;
		}

		int docId, wordId, wordFreq, i=0, sum=0;
		infile >> docId >> wordId >> wordFreq;
		int lastIdDoc = docId;
		map<int, int> currentDoc;
		do {
			if(docId != lastIdDoc)
			{
				/*
					Term frequency instead of raw count
				for (map<int,int>::iterator it=currentDoc->begin(); it!=currentDoc->end(); ++it)
				{
					it->second /= sum;
				}*/
				this->docTermFrequency.push_back(currentDoc);
				currentDoc.clear();
				sum=0;
			}
			sum += wordFreq;
			currentDoc.emplace(wordId, wordFreq);
			this->wordFreqCorpus[wordId]++;;
		} while(infile >> docId >> wordId >> wordFreq);

		for(auto &elem : this->wordFreqCorpus)
		{
			elem.second = log(this->nbDocs / elem.second);
		}

		infile.close();
	}

	void FillWords()
	{
		ifstream wordFile;
		wordFile.open("../Data/words.txt");

		if(!wordFile)
		{
			cerr<<"Error while loading doc " << "words.txt" << endl;
			return;
		}

		int idWord;
		string word;
		while(wordFile >> idWord >> word)
		{
			this->words->push_back(word);
			this->wordFreqCorpus[idWord = 0];
		}

		wordFile.close();
	}

	void ComputeValues()
	{
		int nbKept = 0;
		cout<<"ComputeValues";
		for(auto &vecteur : this->docTermFrequency)
		{
			for(auto &element : vecteur)
			{

			}
		}
	}
};


int main()
{
	TfIdf* tfidf = new TfIdf();
	tfidf->FillWords();
	tfidf->ReadInputFiles();
	tfidf->ComputeValues();
}
