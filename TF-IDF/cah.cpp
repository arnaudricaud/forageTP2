#include "cah.h"

using namespace std;

Cah::Cah(int nb)
{
	this->nbWantedClusters = nb;
	for(int i=0; i< NB_DOCS; i++)
	{
		vector<int> toAdd;
		for(int j=i; j< NB_DOCS; j++)
		{
			toAdd.push_back(0);
		}
		this->distanceMatrix.push_back(toAdd);
	}
}

void Cah::computeDistanceMatrix()
{

}
