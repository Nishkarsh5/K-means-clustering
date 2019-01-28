#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <tuple>

using namespace std;

class Point{
public:
	int id;
	tuple<int, int, int> value;
	int clusterid;

	Point(){}
	Point(int i, tuple<int, int, int> v){this->id = i; this->value = v;}
		
	void setCluster(int i){ this->clusterid = i;}
	void print(){
		cout<<"[.] ID: "<<id<<endl;
		cout<<"[.] Value: "<<"("<<get<0>(value)<<", "<<get<1>(value)<<", "<<get<2>(value)<<")"<<endl;
		cout<<"[.] ClusterID: "<<clusterid<<endl;
	}
};

#endif
