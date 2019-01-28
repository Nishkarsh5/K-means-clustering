#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <tuple>
#include <vector>
#include "point.h"

using namespace std;

class Cluster{

private:
	int cluserid;
	vector<Point> points;

public:
	Cluster(){}
	Cluster(int id, Point p){
		this->cluserid = id;
		points.push_back(p);
	}

	int getID(){return cluserid;}
	void addPointToCluster(Point p){
		points.push_back(p);
	}

	bool removePointFromCluster(int id){
		for(int i=0; i<points.size(); i++){
			if((points.at(i)).id == id){
				points.erase(points.begin() + i);
			}
		}
	}

	void print(){
		cout<<"ID: "<<cluserid<<endl;
		cout<<"Points in cluster: "<<points.size()<<endl;
	}
};

#endif
