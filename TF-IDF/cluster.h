#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include "Constantes.h"
#include "document.h"

using namespace std;

class Cluster
{
private:
	int id;

	map<int, double> oldCenter;
	double totalWeight;
	vector<int> words;

public:
	map<int, double> center; //int => id des mots!, double => freq/nb docs
	vector<Document*> docs;

	Cluster(int clusterId);
	~Cluster();

	int getId();
	map<int, double> getCenter();
	map<int, double> getOldCenter();
	vector<Document*> getDocs();
	vector<int> getWords();
	void calculateCenter();
	void clearCenter();
	void clearDocs();
	void addDoc(Document* docId);
	void addDocCah(Document* docId);
	double getTotalWeight();
	double getDistanceTo(Cluster*);
};
