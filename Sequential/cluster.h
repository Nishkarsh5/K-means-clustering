#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <tuple>
#include <vector>
#include "point.h"

using namespace std;

class Cluster{

private:
	int cluserid; //ID of cluster
	Point clusterCenter; //centroid of cluster
	vector<Point> points; // all the points in that cluster

public:
	Cluster(){}
	Cluster(int id, Point p){ //construct a cluster from id and center
		this->cluserid = id;
		clusterCenter = p;
	}

	int getClusterID(){return cluserid;} //get id

	Point getCenter(){return clusterCenter;} // get centroid
	void makeCenter(Point c){clusterCenter = c;} //make c centroid

	vector<Point> getAllPoints(){return points;} //get all points in cluster
	void addPointToCluster(Point p){ //add point to cluster
		points.push_back(p);
	}
	bool removePointFromCluster(int id){ //remove point from cluster
		for(int i=0; i<points.size(); i++){
			if((points.at(i)).id == id){
				points.erase(points.begin() + i);
			}
		}
	}

	void print(){ //print the cluster
		cout<<"ID: "<<cluserid<<endl;
		cout<<"Points in cluster: "<<points.size()<<endl;
	}

};

#endif
