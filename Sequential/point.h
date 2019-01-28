#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <tuple>

using namespace std;

class Point{
private:
	int id; //id of the point
	tuple<int, int, int> value; //value
	int clusterid; //which cluster he is in?

public:
	Point(){}
	Point(int i, tuple<int, int, int> v){
		this->id = i;
		this->value = v;
		this->clusterid = -1;
	} //construct
	
	int getID(){return id;} //get id of point
	int getClusterID(return clusterid;) //get cluster id it belongs to
	tuple<int, int, int> getValue(){
		return value;
	}

	void setCluster(int i){ this->clusterid = i;} //set cluster id
	void print(){ //print the shit
		cout<<"[.] ID: "<<id<<endl;
		cout<<"[.] Value: "<<"("<<get<0>(value)<<", "<<get<1>(value)<<", "<<get<2>(value)<<")"<<endl;
		cout<<"[.] ClusterID: "<<clusterid<<endl;
	}

	float eucledianDistanceFrom(const Point &p){
		tuple<int, int, int> v1 = this->value;
		tuple<int, int, int> v2 = p.getValue();
		return sqrt(pow((get<0>(v1) - get<0>(v2), 2)) + pow((get<1>(v1) - get<1>(v2), 2)) + pow((get<2>(v1) - get<2>(v2), 2)));
	}
};

#endif
