// Sequential: K-Means Clustering Algorithm

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <limits>

#include "point.h"
#include "cluster.h"

using namespace std;





void formClusters(vector<Point> &points, int K){
	// Step-1: Get k random points and make them clusters centers

	random_device rd; //obtain random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(0, K-1);

	vector<Cluster> clusters; //vector of clusters

	for(int i=0; i<K; i++){
		Cluster c(i, points.at(distr(eng)));
		clusters.push_back(c);
	}

	// Step-2: fill rest of the points into the formed clusters
	for(int i=0; i<points.size(); i++){
		Point pointMark = points.get(i);
		
		vector<tuple<int, float>> closestClusterInfo;
		for(int j=0; j<clusters.size(); j++){
			float dist = pointMark.eucledianDistanceFrom(clusters.at(j).getCenter());
			closestClusterInfo.push_back(make_tuple(clusters.at(j).getClusterID(), dist));
		}

	    float maxVal = numeric_limits<float>::max();
		int closestClusterID = -1;
		for(int j=0; j<closestClusterInfo.size(); j++){
			if(maxVal > get<1>(closestClusterInfo.at(j))){
				closestClusterID = get<0>(closestClusterInfo.at(j));
				maxVal = get<1>(closestClusterInfo.at(j));
			}
		}

		clusters.at(closestClusterID).addPointToCluster(pointMark);
		pointMark.setCluster(closestClusterID);
	}
	//filled all the points in the closest cluster

	// plot here

	//Step-3 calculate mean center of each cluster
	// change centers
	// iterate over all points readjust their parent clusters

	for(int i=0; i<clusters.size(); i++){
		vector<Point> clusPoints = (clusters.get(i)).getAllPoints();
		float m // it can be d dimensional vector change it from the beginning
		for(int j=0; j<clusPoints.size(); j++){

		}
	}



}

int main(int argc, char *argv[]){
	int totalPoints = 9;
	int k = 3;
	int maxIterations = 5;

	if(k > totalPoints){
		return -1;
	}

	//read from file
	ifstream file("./data.txt");
	vector<Point> points;

	for(int i=0; i<totalPoints; i++){
		int a, b, c;
		file>>a>>b>>c;
		points.push_back(Point(i, make_tuple((int)a, (int)b, (int)c)));
	}

	//got all the points in the vector

	//form clusters
	formClusters(points);
}