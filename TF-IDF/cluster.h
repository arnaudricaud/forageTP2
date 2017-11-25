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
	map<int, double> center; //int => id des mots!, double => freq/nb docs

public:
	Cluster(int clusterId);
	~Cluster();

	int getId();
	map<int, double> getCenter();
	vector<Document*> getDocs();
	void calculateCenter();
	void clearCenter();
	void clearDocs();
	void addDoc(Document* docId);
	
};

