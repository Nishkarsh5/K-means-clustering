#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <vector>
#include "point.h"

using namespace std;

class Cluster{

private:
	int clusterid; //ID of cluster
	Point clusterCenter; //centroid of cluster
	vector<Point> points; // all the points in that cluster

public:
	Cluster(){}
	Cluster(int id, Point p){ //construct a cluster from id and center
		this->clusterid = id;
		clusterCenter = p;
	}

	int getClusterID(){return clusterid;} //get id

	Point getCenter(){return clusterCenter;} // get centroid
	void makeCenter(const Point &c){clusterCenter = c;} //make c centroid

	vector<Point> getAllPoints(){return points;} //get all points in cluster
	void addPointToCluster(Point p){ //add point to cluster
		points.push_back(p);
	}

	bool removePointFromCluster(int id){ //remove point from cluster
		for(int i=0; i<points.size(); i++){
			if((points.at(i)).getID() == id){
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	void print(){ //print the cluster
		cout<<"[.] Cluster || ID: "<<clusterid<<" | Points in cluster: "<<points.size()<<endl;
		cout<<"Cluster Center: ";
		clusterCenter.print();
		
		for(int i=0; i<points.size(); i++){
			(points.at(i)).print();
		}
		cout<<"--------------------------------\n";
	}

};

#endif
