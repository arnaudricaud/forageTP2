#include "kmeans.h"



Kmeans::Kmeans(string inputFile, int clusternb)
{
	cout << "Ouverture du fichier TF-IDF" << endl;
	ifstream infile;
	infile.open(FINAL_TFIDF_FILE);
	if (!infile)
	{
		cerr << "Error while loading doc " << FINAL_TFIDF_FILE << endl;
		return;
	}
	
	
	int idDoc, idWord, freqWord;
	int j  = 0;
	int nbDocs = 0;
	//On créé les docs auquels on associe chaque mots!
	while (infile >> idDoc >> idWord >> freqWord)
	{
		if (idDoc != j) {
			nbDocs++;
			j = idDoc;
			docs.push_back(new Document(idDoc));
		}
		docs[idDoc]->addWord(idWord);
	}
	

	for (int i = 0; i < clusternb; i++) {


	}
	//Créer des Clusters vides
	//Associer des docs aléatoires
	//Calculer le premier centre
}

Kmeans::~Kmeans()
{
}

void Kmeans::applyKmeans(string outputFile)
{
}
