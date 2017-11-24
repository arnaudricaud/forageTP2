#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "Constantes.h"
#include "document.h"
#include "cluster.h"

using namespace std;

class Cluster
{
private:
	int id;
	vector<Document*> docs;
	map<int, double> oldCenter;
	

public:
	map<int, double> center; //int => id des mots!, double => freq/nb docs

	Cluster(int clusterId);
	~Cluster();

	int getId();
	map<int, double> getCenter();
	map<int, double> getOldCenter();
	vector<Document*> getDocs();
	void calculateCenter();
	void clearCenter();
	void clearDocs();
	void addDoc(Document* docId);
	
};

