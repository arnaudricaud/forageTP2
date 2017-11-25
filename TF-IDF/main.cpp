#include "tfidf.h"
#include "porter.h"
#include "kmeans.h"
#include "Constantes.h"


int main()
{
	
	/*Porter* porter = new Porter(WORDS_FILE);
	porter->applyPorter(PORTER_WORDS_OUTPUT);*/
	
	/*TfIdf* tfidf = new TfIdf(true);
	tfidf->FillWords();
	tfidf->ReadInputFiles();
	tfidf->ComputeIdfs();
	tfidf->ComputeTfIdfs();
	tfidf->RemoveWords(1.5, false);
	tfidf->WriteNewWordsForEachDoc();*/

	Kmeans* kmeans = new Kmeans(FINAL_TFIDF_FILE, 5);
	kmeans->applyKmeans();
	system("pause");
}
