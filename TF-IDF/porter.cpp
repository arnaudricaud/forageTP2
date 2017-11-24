#include "porter.h"


using namespace std;


Porter::Porter(string fileName)
{
	wordFileName = fileName;
}

void Porter::applyPorter(string outputFileName)
{
	//Ouverture du fichier "word"
	cout << "Ouverture du fichier words" << endl;
	ifstream infile;
	infile.open(wordFileName.c_str());
	if (!infile)
	{
		cerr << "Error while loading doc " << wordFileName << endl;
		return;
	}

	//Fichier ouvert: lecture des mots et des ids 1 par 1:
	int idWord;
	string word;
	int consonant;
	string porterWord;
	bool newWord;

	while (infile >> idWord >> word)
	{
		this->words.emplace(idWord, word);
	}

	infile.close();

	cout << "Fermeture du fichier words, lecture terminee " << endl;

	for(auto& wordInput : this->words)
	{
		string currentWord = wordInput.second;
		int currentId = wordInput.first;

		//Comptage du nombre de pseudo-syllabes:
		newWord = true;
		consonant = getConsonantNb(currentWord);
		//On r�cup�re le mot de porter
		porterWord = porterProcessStep1(currentWord, consonant);

		//On regarde s'il existe d�j� dans nos mots, si c'est le cas, on ajoute l'id du mot original � la liste.
		for (int i = 0; i < porterWords.size(); i++) {
			if (porterWord.compare(porterWords[i]->getWord()) == 0) {
				porterWords[i]->addOldId(currentId);
				newWord = false;
				break;
			}
		}
		//Sinon, on cr�� un nouveau mot!
		if (newWord) {
			porterWords.push_back(new PorterWord(porterWord, currentId));
		}

	}

	cout << "nb de mots apr�s Porter: " << porterWords.size() << endl;

	writeFinalWords(outputFileName);
}

int Porter::getConsonantNb(string word)
{
	int nbConsonant = 0;
	//Pour chaque lettre jusqu'� l'avant derni�re
	for (int i = 0; i<word.length()-1; i++) {
		//Si c'est une voyelle puis une consonne:
		if (isVowel(word[i])) {
			if (!isVowel(word[i+1])){
				nbConsonant++;
			}
		}
	}
	return nbConsonant;
}

bool Porter::vowelInWord(string word, int suffix) {
	//On regarde s'il y a une voyelle dans le mot (apr�s avoir retir� le suffixe!)
	//*v*
	for (int i = 0; i < (word.length()-suffix); i++) {
		if (isVowel(word[i])) {
			return true;
		}
	}
	return false;
}

bool Porter::endDoubleLetter(string word) {
	//On regarde si le mot fini par une double consonne
	//*d
	int size = word.length();
	if ((word[size - 1] == word[size - 2]) && (!isVowel(word[size - 1]))) {
		return true;
	}
	return false;
}

bool Porter::isVowel(char letter) {
	letter = tolower(letter);
	if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u') {
		return true;
	} else {
		return false;
	}
}

bool Porter::cvcEnd(string word) {
	int size = word.length();
	if(size >= 3){
		if (wordEndWith(word, "w") || wordEndWith(word, "x")) {
			//Si la derni�re consonne est w ou x:
			return false;
		}
		else if (isVowel(word[size-1]) || !isVowel(word[size - 2]) || isVowel(word[size - 3])) {
			//Si on a pas ce qu'il faut (!CVC)
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool Porter::wordEndWith(string word, string end) {
	for (int i = 1; i <= end.length(); i++) {
		if (word[word.length() - i] != end[end.length() - i]) {
			return false;
		}
	}
	return true;
}

/*
porterProcessStep1
Description:
	Prends un mot et le change en mot de porter.
Param�tres:
	word: Le mot.
	nbconsonant: le nombre de syllabe du mot.
*/
string Porter::porterProcessStep1(string word, int nbconsonant) {
	string porterWord;
	int size = word.length();
	porterWord = word;

	//�tape n�1a:
	if (word.length() > 3) {

		//�tape n�1a:
		// SSES->SS
		// IES->I
		// SS->SS
		// S-> �

		//Si plus de 1 syllabe:
		//EED->EE
		//ED-> �
		//ING-> �
		if (wordEndWith(porterWord,"sses")|| wordEndWith(porterWord, "ies")) {
					//Si le mot fini par SSES ou IES => On supprime les deux derni�res lettres
					porterWord = porterWord.substr(0, size - 2);
					size = size - 2;
		} else if (wordEndWith(porterWord, "s") && !wordEndWith(porterWord, "ss")) {
				//Si le mot fini par S (et non SS) => On supprime la derni�re lettre.
				porterWord = porterWord.substr(0, size - 1);
				size--;
		} else if (nbconsonant > 1) {
			 if (wordEndWith(porterWord, "eed")) {
				//Si le mot fini par EED et qu'on a plus d'une syllabe => On supprime le D!
				porterWord = porterWord.substr(0, size - 1);
				size--;
			}else if (wordEndWith(porterWord, "ing") && vowelInWord(porterWord, 3)) {
				//Si le mot fini par ING et qu'on a plus d'une syllabe => On supprime le ING!
				porterWord = porterWord.substr(0, size - 3);
				size = size - 3;
				/*	AT->ATE
				BL->BLE
				IZ->IZE
				(*d and not (*L or *S or *Z))->single letter
				(m = 1 and *o)->E*/
				if (wordEndWith(porterWord, "at") || wordEndWith(porterWord, "bl") || wordEndWith(porterWord, "iz")) {
					//Si le mot se termine par les truc ci dessus, on ajoute un 'e'
					porterWord += 'e';
					size++;
				}
				else if (endDoubleLetter(porterWord) && !(wordEndWith(porterWord, "l") || wordEndWith(porterWord, "s") || wordEndWith(porterWord, "z"))) {
					//Si le mot se termine par une doule consonne qui n'est pas L,S ou Z:
					porterWord = porterWord.substr(0, size - 1);
					size--;
				}
				else if (getConsonantNb(porterWord) == 1 && cvcEnd(porterWord)) {
					//Si le mot � une syllabe et qu'il fini en CVC:
					porterWord += 'e';
					size++;
				}

			}  else if (wordEndWith(porterWord, "ed") && vowelInWord(porterWord, 2)) {
				//Si le mot fini par ED et qu'on a plus d'une syllabe => On supprime le ED!
				porterWord = porterWord.substr(0, size - 2);
				size = size - 2;
				/*	AT->ATE
				BL->BLE
				IZ->IZE
				(*d and not (*L or *S or *Z))->single letter
				(m = 1 and *o)->E*/
				if (wordEndWith(porterWord, "at") || wordEndWith(porterWord, "bl") || wordEndWith(porterWord, "iz")) {
					//Si le mot se termine par les truc ci dessus, on ajoute un 'e'
					porterWord += 'e';
					size++;
				}
				else if (endDoubleLetter(porterWord) && !((wordEndWith(porterWord, "l")) || (wordEndWith(porterWord, "s")) || (wordEndWith(porterWord, "z")))) {
					//Si le mot se termine par une doule consonne qui n'est pas L,S ou Z:
					porterWord = porterWord.substr(0, size - 1);
					size--;
				}
				else if (getConsonantNb(porterWord) == 1 && cvcEnd(porterWord)) {
					//Si le mot � une syllabe et qu'il fini en CVC:
					porterWord += 'e';
					size++;
				}
			}
		}

		if (wordEndWith(porterWord, "y") && vowelInWord(porterWord,1)) {
			//(*v*) Y->I
			//Si le mot contient une voyelle et fini par Y, on remplace le y par un I

			porterWord[size - 1] = 'i';
		}

	}
	//cout << word << " -> " << porterWord << endl;
	return porterWord;
}

void Porter::writeFinalWords(string outFile)
{
	cout << "Writing porter result to new file..." << endl;

	ofstream output;
	output.open(outFile);

	int i = 1;
	for(PorterWord* porterWord : this->porterWords)
	{
		output << i << ",";
		vector<int> oldIds = porterWord->getOldIds();
		for(int oldId : oldIds)
		{
			output << oldId;
			if(oldId != oldIds.back())
			{
				output << " ";
			}
		}
		output << "," << porterWord->getWord();

		if(porterWord != this->porterWords.back())
		{
			output  << "\r\n";
		}

		i++;
	}

	output.close();
}
