#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <climits>
#include "porterWord.h"
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
	map<PorterWord*, int> wordPorterFreqCorpus;

public:
	TfIdf();
	void ReadInputFiles();
	void pause();
	void ParseFile(string filename);
	void FillWords(bool);
	void ComputeIdfs();
	void ComputeTfIdfs();
	void RemoveWords(int nbEcartTypeDiff, bool canThrowText);
	int FindMaxIndexInMap(map<int, int> map);
	void GetMoyAndEcartType(map<int, int> serie, double* moy, double* ecartType);
	void WriteNewWordsForEachDoc();
};
