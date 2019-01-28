// Sequential: K-Means Clustering Algorithm

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <limits>
#include <functional> 
#include <algorithm>

#include "point.h"
#include "cluster.h"

using namespace std;




void formClusters(vector<Point> points, int d, int K, int maxIterations){
	// Step-1: Get k random points and make them clusters centers

	random_device rd; //obtain random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(0, K-1);

	vector<Cluster> clusters; //vector of clusters
	vector<Point> init = points;

	for(int i=0; i<K; i++){
		int tmp = distr(eng);

		Cluster c(i, init.at(tmp));
		clusters.push_back(c);
		
		init.erase(init.begin() + tmp);
	}

	// Step-2: fill rest of the points into the formed clusters
	for(int i=0; i<points.size(); i++){
		Point pointMark = points.at(i);

	    float maxVal = numeric_limits<float>::max();
		int closestClusterID = -1;
	
		for(int j=0; j<clusters.size(); j++){
			float dist = pointMark.eucledianDistanceFrom((clusters.at(j)).getCenter());
			if(maxVal > dist){
				maxVal = dist;
				closestClusterID = (clusters.at(j)).getClusterID();
			}
		}

		pointMark.setClusterID(closestClusterID);
		(clusters.at(closestClusterID)).addPointToCluster(pointMark);
	}

	// for(int i=0; i<clusters.size();i++){
	// 	(clusters.at(i)).print();
	// }

	//filled all the points in the closest cluster

	// plot here

	//Step-3 calculate mean center of each cluster


	// calculated mean of every cluster
	// now iterate over all points and refill points into cluster

	vector<Point> pointsWithID;
	for(int i=0; i<clusters.size(); i++){
		vector<Point> temp = (clusters.at(i)).getAllPoints();
		for(int j=0; j<temp.size(); j++){
			pointsWithID.push_back(temp.at(j));
		}
	}

	// for(int q=0; q<pointsWithID.size(); q++){
	// 	(pointsWithID.at(q)).print();
	// }

	int pointsMoved = 1;
	while(maxIterations > 0 && pointsMoved != 0){
		pointsMoved = 0;

		for(int i=0; i<clusters.size(); i++){
			vector<Point> clusPoints = (clusters.at(i)).getAllPoints();
			vector<int> sum(d, 0);

			// for(int q=0; q<clusPoints.size(); q++){
			// 	(clusPoints.at(q)).print();
			// }

			for(int j=0; j<clusPoints.size(); j++){
				for(int k=0; k<d; k++){
					sum.at(k) += ((clusPoints.at(j)).getValue()).at(k);
				}
				vector<int> temp = (clusPoints.at(j)).getValue();
			}
			for(int k=0; k<sum.size(); k++){
				sum.at(k)/=d;
			}

			(clusters.at(i)).makeCenter(Point(-1, sum));
		}

		for(int i=0; i<pointsWithID.size(); i++){
			Point pointMark = pointsWithID.at(i);

			int oldClusterID = pointMark.getClusterID();
		
		    float maxVal = numeric_limits<float>::max();
			int closestClusterID = -1;

			for(int j=0; j<clusters.size(); j++){
				float dist = pointMark.eucledianDistanceFrom((clusters.at(j)).getCenter());
				if(maxVal > dist){
					maxVal = dist;
					closestClusterID = (clusters.at(j)).getClusterID();
				}
			}

			if(closestClusterID != oldClusterID){
				// change it
				(clusters.at(oldClusterID)).removePointFromCluster(pointMark.getID());
				(clusters.at(closestClusterID)).addPointToCluster(pointMark);
				pointMark.setClusterID(closestClusterID);
				pointsMoved = pointsMoved + 1;
			}
			// otherwise remains same
		}

		maxIterations = maxIterations - 1;
	}

}

int main(int argc, char *argv[]){
	int d = 3;
	int totalPoints = 9;
	int K = 3;
	int maxIterations = 20;

	if(K > totalPoints){
		return -1;
	}

	//read from file
	ifstream file("./data.txt");
	vector<Point> points;

	for(int i=0; i<totalPoints; i++){
		int a, b, c;
		file>>a>>b>>c;
		vector<int> vec;
		vec.push_back((int)a);
		vec.push_back((int)b);
		vec.push_back((int)c);
		points.push_back(Point(i, vec));
	}

	//got all the points in the vector

	//form clusters
	formClusters(points, d, K, maxIterations);

	return 0;
}