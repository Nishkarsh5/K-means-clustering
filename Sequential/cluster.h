#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <vector>
#include "point.h"

using namespace std;

class Cluster{

private:
	int dim;
	int clusterid; //ID of cluster
	Point clusterCenter; //centroid of cluster
	vector<Point*> points; // all the points in that cluster

public:
	Cluster(){}
	Cluster(int id, Point p, int d=3){ //construct a cluster from id and center
		this->clusterid = id;
		clusterCenter = p;
		dim = d;
	}

	int getClusterID(){return clusterid;} //get id

	Point getCenter(){return clusterCenter;} // get centroid
	void makeCenter(const Point &c){clusterCenter = c;} //make c centroid

	vector<Point*> getAllPoints(){return points;} //get all points in cluster
	void addPointToCluster(Point* p){ //add point to cluster
		points.push_back(p);
	}

	bool removePointFromCluster(int id){ //remove point from cluster
		int i1 = points.size();
		for(int i=0; i<points.size(); i++){
			if((points.at(i))->getID() == id){
				points.erase(points.begin() + i);
			}
		}
		int i2 = points.size();
		if((i1-i2)!=1){
			cout<<i1-i2<<endl;
			return false;
		}
		return true;
	}

	void makeCentroidCenter(){ //take average of all values at make it center
		vector<float> sum(dim, 0.0);

		for(int i=0; i<points.size(); i++){
			for(int k=0; k<dim; k++){
				sum.at(k) += (points.at(i)->getValue()).at(k);
			}
		}

		for(int k=0; k<sum.size(); k++){
			sum.at(k)/=dim;
		}

		makeCenter(Point(-1, sum));
	}

	void print(){ //print the cluster
		cout<<"[.] Cluster || ID: "<<clusterid<<" | Points in cluster: "<<points.size()<<endl;
		cout<<"Cluster Center: ";
		clusterCenter.print();
		
		for(int i=0; i<points.size(); i++){
			(points.at(i))->print();
		}
		cout<<"--------------------------------\n";
	}

};

#endif
