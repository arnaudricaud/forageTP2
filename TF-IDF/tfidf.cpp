#include "tfidf.h"

using namespace std;



	TfIdf::TfIdf(bool loadPorterWords)
	{
		this->usePorterWords = loadPorterWords;
	}


	void TfIdf::ReadInputFiles()
	{
		for(int i=1; i<=3; i++)
		{
			ostringstream oss;
			oss << INPUT_PATH_PART1 << i << INPUT_PATH_PART2;
			string filename = oss.str();
			ParseFile(filename);
		}
	}

	void TfIdf::pause()
	{
	   std::cin.sync(); // Flush The Input Buffer Just In Case
	   std::cin.ignore(); // There's No Need To Actually Store The Users Input
	}

	void TfIdf::ParseFile(string filename)
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
			if(this->usePorterWords)
			{
				this->wordFreqCorpus[this->oldIdToNewId.find(wordId)->second]++;
				currentDoc[this->oldIdToNewId.find(wordId)->second] += wordFreq;
			}
			else
			{
				this->wordFreqCorpus[wordId]++;
				currentDoc.emplace(wordId, wordFreq);
			}
			lastIdDoc = docId;
		} while(infile >> docId >> wordId >> wordFreq);

		this->docTermFrequency.push_back(currentDoc);
		currentDoc.clear();

		infile.close();
	}

	template <class Container>
	void split(const std::string& str, Container& cont, char delim = ' ')
	{
	    stringstream ss(str);
	    string token;
	    while (getline(ss, token, delim)) {
	        cont.push_back(token);
	    }
	}

	void TfIdf::FillWords()
	{
		ifstream wordFile;

		if(this->usePorterWords)
		{
			cout << "Reading porter output file " << endl;

			wordFile.open(PORTER_WORDS_OUTPUT);

			if(!wordFile)
			{
				cerr<<"Error while loading doc " << PORTER_WORDS_OUTPUT << endl;
				return;
			}

			string line;
			while(!wordFile.eof())
			{
				line.clear();
				getline(wordFile, line);

				vector<string> splited;
				split(line.c_str(), splited, ',');
				int newId = stoi(splited[0]);
				vector<string> oldsIdsString;
				split(splited[1].c_str(), oldsIdsString, ' ');
				for(string oldId : oldsIdsString)
				{
					this->oldIdToNewId.emplace(stoi(oldId), newId);
				}

				this->wordFreqCorpus[newId = 0];
			}
			wordFile.close();
		}
		else
		{
			cout << "Reading original word file..." <<endl;

			wordFile.open(WORDS_FILE);

			if(!wordFile)
			{
				cerr<<"Error while loading doc " << WORDS_FILE << endl;
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
	}

	void TfIdf::ComputeIdfs()
	{
		for(auto &elem : this->wordFreqCorpus)
		{
			if(elem.second != 0)
			{
				elem.second = log(NB_DOCS / elem.second);
			}
		}
	}

	void TfIdf::ComputeTfIdfs()
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

	void TfIdf::RemoveWords(double nbEcartTypeDiff, bool canThrowText)
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

	int TfIdf::FindMaxIndexInMap(map<int, int> map)
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

	void TfIdf::GetMoyAndEcartType(map<int, int> serie, double* moy, double* ecartType)
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

	void TfIdf::WriteNewWordsForEachDoc()
	{
		vector<int> wordId;
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
				if(find(wordId.begin(), wordId.end(), values.first) == wordId.end())
				{
					wordId.push_back(values.first);
				}
			}
			if(!written)
			{
				cout<< "Le document " << nbDoc << " n'as aucun mot interessant" << endl;
			}
			nbDoc++;
		}

		cout << wordId.size() << " mots différents" << endl;

		tfidfFile.close();
	}
