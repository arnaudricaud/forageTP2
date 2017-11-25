#pragma once
#include "cluster.h"
#include "document.h"
#include "Constantes.h"
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
class Cah
{
private:
	vector<Cluster*> clusters;
	vector<Document*> documents;
	vector<int> distanceMatrix;
	int nbWantedClusters;
public:
	Cah(int);
	~Cah();

	void createDitanceMatrix();
	void applyCAH();
	void computeDistanceMatrix();
};
