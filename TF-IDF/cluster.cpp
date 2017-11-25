#include "cluster.h"


using namespace std;

Cluster::Cluster(int clusterId)
{
	id = clusterId;
}


Cluster::~Cluster()
{
}

int Cluster::getId()
{
	return id;
}

map<int, double > Cluster::getCenter()
{
	return center;
}

map<int, double> Cluster::getOldCenter()
{
	return oldCenter;
}

vector<Document*> Cluster::getDocs()
{
	return docs;
}

void Cluster::calculateCenter()
{
	oldCenter = center;
	clearCenter();
	totalWeight = 0;
	//Pour chaque doc du cluster:
	for (int i = 0; i < docs.size(); i++) {
		vector<int> words = docs[i]->getWords();
		//Pour chaque mot on l'ajoute dans la liste de mots:
		for (int j = 0; j < words.size(); j++) {
			int key = words[j];
			if (center.find(key) != center.end()) {
				//Si le mot est d�j� enregistr�, augmente son importance (pond�r�e!)
				center[key] += 1 / (double)docs.size();
				totalWeight += 1 / (double)docs.size();
			} else {
				//Sinon on cr�� le mot
				center.emplace(key, 1 / (double)docs.size());
				totalWeight += 1 / (double)docs.size();
			}
		}
	}

}

vector<int> Cluster::getWords()
{
	return this->words;
}

void Cluster::addDocCah(Document* doc)
{
	docs.push_back(doc);
	for(int wordId : doc->getWords())
	{
		this->words.push_back(wordId);
	}
}

double Cluster::getDistanceTo(Cluster* compareTo)
{
	double distance = 0;
	for(int wordId : compareTo->getWords())
	{
		if(find(this->words.begin(), this->words.end(), wordId) != this->words.end())
		{
			distance += 1;
		}
	}
	return distance;
}

void Cluster::clearCenter()
{
	center.clear();
}

void Cluster::clearDocs()
{
	docs.clear();
}

void Cluster::addDoc(Document* doc)
{
	docs.push_back(doc);
}

double Cluster::getTotalWeight() {
	return totalWeight;
}
