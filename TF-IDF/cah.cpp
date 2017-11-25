#include "cah.h"

using namespace std;

Cah::Cah(int nb)
{
	cout << "CAH" << endl;
	this->nbWantedClusters = nb;
	cout << "Load documents..." <<endl;

	ifstream docs;

	docs.open(FINAL_TFIDF_FILE);

	if(!docs)
	{
		cout << "Error while loading docs" << endl;
		return;
	}

	int idDoc, idWord, freqWord;
	int lastIdWord  = 1;
	Document* doc = new Document(lastIdWord);
	while (docs >> idDoc >> idWord >> freqWord)
	{
		if (idDoc != lastIdWord) {
			lastIdWord = idDoc;
			documents.push_back(doc);
			doc = new Document(lastIdWord);
		}
		doc->addWord(idWord);
	}
	documents.push_back(doc);
	cout << "Documents created." << endl;

	cout << "Create a cluster for each doc..." <<endl;

	int i=0;
	for(Document* document : documents)
	{
		Cluster* c = new Cluster(i++);
		c->addDocCah(document);
		clusters.push_back(c);
	}
	cout << i << "clusters" << endl;

	cout << "Clusters created."<< endl;

	cout << "Create distance matrix..."<<endl;

	//createDitanceMatrix();

	cout << "Distance matrix created." <<endl;

	cout << "Begin CAH treatment, until "<< nbWantedClusters << " are found..." << endl;

	applyCAH();
}

void Cah::createDitanceMatrix()
{
	for(int i=0; i<clusters.size()-1; i++)
	{
		for(int j=i; j<clusters.size(); j++)
		{
			this->distanceMatrix.push_back(0);
		}
	}
}

void Cah::applyCAH()
{
	int it = 1;
	while(clusters.size() > nbWantedClusters)
	{
		computeDistanceMatrix();

		cout << "Itération " << it++ << " done."<<endl;
	}
}

void Cah::computeDistanceMatrix()
{
	bool firstTime = (this->distanceMatrix.size() == 0);
	cout << "Max size:" << this->distanceMatrix.max_size() << endl;

	double minDistance = 100000000;
	Cluster* toMerge1 = nullptr;
	Cluster* toMerge2 = nullptr;
	for(int i=0; i<clusters.size()-1; i++)
	{
		Cluster* currentCluster = this->clusters[i];
		if(i%1000 == 0)
		{
			cout << i << "docs passes"<< endl;
		}
		for(int j=i; j<clusters.size(); j++)
		{
			int index = (i * (clusters.size() - 1)) + j;
			if(j != i)
			{
				Cluster* compareTo = this->clusters[j];
				int distance = currentCluster->getDistanceTo(compareTo);
				if(distance < minDistance)
				{

				}
			}
		}
	}
}
