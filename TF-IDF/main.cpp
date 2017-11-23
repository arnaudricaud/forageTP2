#include "tfidf.h"
#include "porter.h"



int main()
{
	//Porter* porter = new Porter("../Data/words.txt");

	TfIdf* tfidf = new TfIdf();
	tfidf->FillWords();
	tfidf->ReadInputFiles();
	tfidf->ComputeIdfs();
	tfidf->ComputeTfIdfs();
	tfidf->RemoveWords(2, false);
	tfidf->WriteNewWordsForEachDoc();

}