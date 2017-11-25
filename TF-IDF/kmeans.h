#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Constantes.h"
#include "document.h"
#include "cluster.h"

using namespace std;

class Kmeans
{
private:
	vector<Cluster*> clusters;
	vector<Document*> docs;


public:
	Kmeans(string inputFile, int clusterNb);
	~Kmeans();
	void applyKmeans(string outputFile);



};

