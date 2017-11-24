#include "kmeans.h"



Kmeans::Kmeans(string inputFile, int clusternb)
{
	cout << "K-means begin..." << endl;
	cout << "Opening TF-IDF file..." << endl;
	ifstream infile;
	infile.open(inputFile);
	if (!infile)
	{
		cerr << "Error while loading doc " << inputFile << endl;
		return;
	}

	int idDoc, idWord, freqWord;
	int j  = 0;
	int nbDocs = 0;
	//On cr�� les docs auquels on associe chaque mots!
	while (infile >> idDoc >> idWord >> freqWord)
	{
		if (idDoc != j) {
			nbDocs++;
			j = idDoc;
			docs.push_back(new Document(idDoc));
		}
		docs[nbDocs-1]->addWord(idWord);
	}
	cout << "Documents created..." << endl;
	for (int i = 0; i < clusternb; i++) {
		clusters.push_back(new Cluster(i));
	}
	cout << "Clusters created..." << endl;
	//Pour chaque texte, je l'associe � un cluster al�atoirement
	int randCluster;
	srand(time(NULL));
	for (int i = 0; i < docs.size(); i++) {
		randCluster = rand() % clusternb;
		clusters[randCluster]->addDoc(docs[i]);
	}
	//On termine en calculant le premier centre de chaque cluster
	calcClustersCenters();
	cout << "First center calculations has ended..." << endl;
}

Kmeans::~Kmeans()
{
}

void Kmeans::applyKmeans()
{
	bool clusterStabilized = false;
	cout << "Begining kmeans calculation..." << endl;
	int it = 0;
	while (!clusterStabilized) {
		//On retire les documents des clusters:
		clearAllClusters();
		cout <<"clusters vides" << endl;
		//On r�assigne les textes au clusters:
		assignTextToClusters();
		cout <<"clusters remplis" << endl;
		//On recalcule tous les centres:
		calcClustersCenters();
		cout <<"Nouveaux centres ok" << endl;
		//On check si on a atteint notre condition d'arret:
		clusterStabilized = areClusterStabilized();

		cout << "Iteration " << ++it << endl;
	}
	//Une fois termin�, on �crit le r�sultat dans un fichier
	cout << "Writting results..." << endl;
	writeResult();
	cout << "Kmeans Done!" << endl;
}

//On prends les doc et on les associes aux cluster les plus proches
void Kmeans::assignTextToClusters() {
	int closestCluster = 0;
	double maxScore = 0;
	double currentScore;
	for (int i = 0; i < docs.size(); i++) {
		if(i % 100 == 0)
		{
			cout << i << " textes assignes a un cluster" << endl;
		}
		for (int j = 0; j < clusters.size(); j++) {
			//map<int, double> currentCenter = centroids[j];//clusters.at(j)->getCenter();
			currentScore = calcPoidText(i, j);
			if (currentScore > maxScore) {
				maxScore = currentScore;
				closestCluster = j;
			}
		}
		clusters[closestCluster]->addDoc(docs[i]);
	}
}

//On prends les doc et on les associes aux cluster les plus proches
double Kmeans::calcPoidText(int docNb, int clusterNb) {

	vector<int> currentWords = docs[docNb]->getWords();
	double currentScore = 0;

	for (int i = 0; i < currentWords.size(); i++) {
		if (clusters[clusterNb]->center.find(currentWords[i]) != clusters[clusterNb]->center.end()) {
			currentScore += clusters[clusterNb]->center[currentWords[i]];
		}

	}
	return currentScore;
}

bool Kmeans::areClusterStabilized() {
	bool stabilized = true;
	for (int j = 0; j < clusters.size(); j++) {
		if (clusters[j]->getOldCenter() != clusters[j]->getCenter()) {
			stabilized = false;
		}
	}
	return stabilized;
}

void Kmeans::calcClustersCenters() {
	for (int i = 0; i < clusters.size(); i++) {
		clusters[i]->calculateCenter();
	}
}

void Kmeans::clearAllClusters() {
	for (int i = 0; i < clusters.size(); i++) {
		clusters[i]->clearDocs();
	}
}

void Kmeans::writeResult()
{
	ofstream kmeanResultFile;
	kmeanResultFile.open(FINAL_KMEANS_FILE);
	int j = 0;
	for (int i = 0; i < clusters.size(); i++) {
		kmeanResultFile << "Cluster n�" << i << "\r\n";
		kmeanResultFile << "Documents associ�s: ";
		vector<Document*> clusterDocs = clusters[i]->getDocs();
		for (j = 0; j < clusterDocs.size()-1; j++){
			kmeanResultFile << clusterDocs[j]<<", ";
		}
		kmeanResultFile << clusterDocs[j+1] << "\r\n\r\n";
	}
}
