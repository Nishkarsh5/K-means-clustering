// Sequential: K-Means Clustering Algorithm

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <limits>
#include <functional> 
#include <algorithm>
#include <cmath>

#include "point.h"
#include "cluster.h"

using namespace std;




void formClusters(vector<Point> &points, int d, int K, int maxIterations){
	// Step-1: Get k random points and make them clusters centers

	random_device rd; //obtain random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(0, K-1);

	vector<Cluster> clusters; //vector of clusters

	for(int i=0; i<K; i++){
		int tmp = distr(eng);

		Cluster c(i, points.at(tmp));
		clusters.push_back(c);
	}

	// Step-2: fill rest of the points into the formed clusters
	for(int i=0; i<points.size(); i++){
		Point* pointMark = &points.at(i);

	    float maxVal = numeric_limits<float>::max();
		int closestClusterID = -1;
	
		for(int j=0; j<clusters.size(); j++){
			float dist = pointMark->eucledianDistanceFrom((clusters.at(j)).getCenter());
			if(maxVal > dist){
				maxVal = dist;
				closestClusterID = (clusters.at(j)).getClusterID();
			}
		}

		pointMark->setClusterID(closestClusterID);
		(clusters.at(closestClusterID)).addPointToCluster(pointMark);
	}


	int pointsMoved = 1;
	while(maxIterations > 0 && pointsMoved != 0){
		pointsMoved = 0;

		for(int i=0; i<clusters.size(); i++){
			(clusters.at(i)).makeCentroidCenter();
		}

		for(int i=0; i<clusters.size(); i++){

			vector<Point*> pnts = (clusters.at(i)).getAllPoints();
			for(int j=0; j<pnts.size(); j++){
				Point* pointMark = pnts.at(j);
				int oldClusterID = pointMark->getClusterID();

			    float maxVal = numeric_limits<float>::max();
				int closestClusterID = -1;

				for(int q=0; q<clusters.size(); q++){
					float dist = pointMark->eucledianDistanceFrom((clusters.at(q)).getCenter());
					if(maxVal > dist){
						maxVal = dist;
						closestClusterID = (clusters.at(q)).getClusterID();
					}
				}

				if(closestClusterID != oldClusterID){
					// change it
					bool ret = (clusters.at(oldClusterID)).removePointFromCluster(pointMark->getID());
					if(!ret){
						cout<<"Error!"<<endl;
					}
					(clusters.at(closestClusterID)).addPointToCluster(pointMark);
					pointMark->setClusterID(closestClusterID);
					pointsMoved = pointsMoved + 1;
				}
		}

		maxIterations = maxIterations - 1;
	}
}
	ofstream myfile;
	myfile.open("eval.csv");
	myfile<<"Feature1,Feature2,Feature3,Cluster\n";
	for(int i=0; i<clusters.size();i++){	
		vector<Point*> clus = (clusters.at(i)).getAllPoints();

		for(int q=0; q<clus.size(); q++){
			// cout<<i<<" "<<q<<" "<<clus.size()<<endl;
			vector<int> temp = (clus.at(q))->getValue();
			myfile<<temp.at(0)<<","<<temp.at(1)<<","<<temp.at(2)<<","<<i<<endl;
		}
	}

	myfile.close();
}


int main(int argc, char *argv[]){
	int d = 3;
	int totalPoints = 1000000;
	int K = 7;
	int maxIterations = 1;

	if(K > totalPoints){
		return -1;
	}

	//read from file
	ifstream file("./text.txt");
	vector<Point> points;

	for(int i=0; i<totalPoints; i++){
		int a, b, c;
		file>>a>>b>>c;
		vector<int> vec;
		vec.push_back(abs((int)a*50));
		vec.push_back(abs((int)b*50));
		vec.push_back(abs((int)c*50));
		points.push_back(Point(i, vec));
	}

	//got all the points in the vector

	//form clusters
	formClusters(points, d, K, maxIterations);

	return 0;
}