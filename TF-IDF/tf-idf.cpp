#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>
#include "Constantes.h"

using namespace std;

class TfIdf
{
private:
	string inputFilePart1;
	string inputFilePart2;
	vector< map<int, int> > docTermFrequency;
	vector< map<int, int> > tfidfValues;
	map<int, int> wordFreqCorpus;

public:
	TfIdf()
	{

	}

	~TfIdf();

	void ReadInputFiles()
	{
		for(int i=1; i<=3; i++)
		{
			ostringstream oss;
			oss << INPUT_PATH_PART1 << i << INPUT_PATH_PART2;
			string filename = oss.str();
			ParseFile(filename);
		}
	}

	void pause()
	{
	   std::cin.sync(); // Flush The Input Buffer Just In Case
	   std::cin.ignore(); // There's No Need To Actually Store The Users Input
	}

	void ParseFile(string filename)
	{
		cout << "Loading " << filename <<endl;
		ifstream infile;
		infile.open(filename.c_str());

		if(!infile)
		{
			cerr<<"Error while loading doc " << filename << endl;
			return;
		}

		int docId, wordId, wordFreq;
		infile >> docId >> wordId >> wordFreq;
		int lastIdDoc = docId;
		map<int, int> currentDoc;
		do {
			if(docId != lastIdDoc)
			{
				this->docTermFrequency.push_back(currentDoc);
				currentDoc.clear();
			}
			currentDoc.emplace(wordId, wordFreq);
			this->wordFreqCorpus[wordId]++;;
			lastIdDoc = docId;
		} while(infile >> docId >> wordId >> wordFreq);

		this->docTermFrequency.push_back(currentDoc);
		currentDoc.clear();

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
			this->wordFreqCorpus[idWord = 0];
		}

		wordFile.close();
	}

	void ComputeIdfs()
	{
		for(auto &elem : this->wordFreqCorpus)
		{
			if(elem.second != 0)
			{
				elem.second = log(NB_DOCS / elem.second);
			}
		}
	}

	void ComputeTfIdfs()
	{
		cout<<"Compute TF * IDF" << endl;
		map<int, int> tfIdfForDoc;
		for(auto &vecteur : this->docTermFrequency)
		{
			for(auto &element : vecteur)
			{
				int tfIdfVal = element.second * this->wordFreqCorpus[element.first];
				tfIdfForDoc.emplace(element.first, tfIdfVal);
			}
			tfidfValues.push_back(tfIdfForDoc);
			tfIdfForDoc.clear();
		}
	}

	void RemoveWords(int nbEcartTypeDiff, bool canThrowText)
	{
		cout << "Remove words" << endl;

		vector<int> indexToRemove;
		for(auto &document : this->tfidfValues)
		{
			double moyenne =0, ecartType = 0;

			GetMoyAndEcartType(document, &moyenne, &ecartType);

			bool noInteristingWords = true;

			for(auto &values : document)
			{
				if(values.second < (moyenne + (nbEcartTypeDiff * ecartType)))
				{
					indexToRemove.push_back(values.first);
				}
				else
				{
					noInteristingWords = true;
				}
			}

			if(noInteristingWords && !canThrowText)
			{
				int toKeep = FindMaxIndexInMap(document);
				indexToRemove.erase(remove(indexToRemove.begin(), indexToRemove.end(), toKeep), indexToRemove.end());
			}

			for(int &toRemove : indexToRemove)
			{
				document.erase(toRemove);
			}

			indexToRemove.clear();
		}
	}

	int FindMaxIndexInMap(map<int, int> map)
	{
		int max = INT_MIN;
		int indexTokeep = 0;
		for(auto &values : map)
		{
			if(values.second > max)
			{
				max = values.second;
				indexTokeep = values.first;
			}
		}

		return indexTokeep;
	}

	void GetMoyAndEcartType(map<int, int> serie, double* moy, double* ecartType)
	{
		double sum = 0;
		int nb =0;
		for(auto &values : serie)
		{
			sum += values.second;
			nb ++;
		}
		*moy = sum / nb;
		double sumEcartType = 0;

		for(auto &values : serie)
		{
			sumEcartType += pow(values.second - *moy, 2);
		}
		*ecartType = sqrt((1.0/nb) * sumEcartType);
	}

	void WriteNewWordsForEachDoc()
	{
		cout << "Write new words"<< endl;;
		ofstream tfidfFile;

		tfidfFile.open(FINAL_TFIDF_FILE);

		int nbDoc = 1;
		for(auto &document : this->tfidfValues)
		{
			bool written = false;
			for(auto &values : document)
			{
				tfidfFile << nbDoc << " "<< values.first << " " << values.second << "\r\n";
				written = true;
			}
			if(!written)
			{
				cout<< "Le document " << nbDoc << " n'as aucun mot interessant" << endl;
			}
			nbDoc++;
		}

		tfidfFile.close();
	}
};


int main()
{
	TfIdf* tfidf = new TfIdf();
	tfidf->FillWords();
	tfidf->ReadInputFiles();
	tfidf->ComputeIdfs();
	tfidf->ComputeTfIdfs();
	tfidf->RemoveWords(2, false);
	tfidf->WriteNewWordsForEachDoc();
}
