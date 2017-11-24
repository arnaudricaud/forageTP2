#pragma once
#include "cluster.h"
#include "Constantes.h"
#include <vector>

using namespace std;
class Cah
{
private:
	vector<Cluster*> clusters;
	vector< vector<int> > distanceMatrix;
	int nbWantedClusters;
public:
	Cah(int);
	~Cah();

	void computeDistanceMatrix();
};
