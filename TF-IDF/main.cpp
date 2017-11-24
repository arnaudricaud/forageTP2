#include "tfidf.h"
#include "porter.h"
#include "Constantes.h"


int main()
{
	/*
	Porter* porter = new Porter(WORDS_FILE);
	porter->applyPorter(PORTER_WORDS_OUTPUT);
	*/

	TfIdf* tfidf = new TfIdf();
	tfidf->FillWords(true);
	/*
	tfidf->ReadInputFiles();
	tfidf->ComputeIdfs();
	tfidf->ComputeTfIdfs();
	tfidf->RemoveWords(2, false);
	tfidf->WriteNewWordsForEachDoc();
	*/

}
