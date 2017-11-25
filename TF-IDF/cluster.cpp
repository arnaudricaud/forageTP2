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
				//Si le mot est déjà enregistré, augmente son importance (pondérée!)
				center[key] += 10000 / (double)docs.size();
				totalWeight += 10000 / (double)docs.size();
			} else {
				//Sinon on créé le mot
				center.emplace(key, 10000 / (double)docs.size());
				totalWeight += 10000 / (double)docs.size();
			}
		}
	}

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
