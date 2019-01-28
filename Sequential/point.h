#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point{

private:
	int id; //id of the point
	vector<int> value; //value
	int clusterid; //which cluster he is in?

public:
	Point(){}
	Point(int i, vector<int> v){
		this->id = i;
		this->value = v;
		this->clusterid = -1;
	}
	
	int getID(){return id;} //get id of point
	int getClusterID(){return clusterid;} //get cluster id it belongs to
	vector<int> getValue(){
		return value;
	}

	void setClusterID(int i){ this->clusterid = i;} //set cluster id
	void print(){ //print the shit
		cout<<"[*] Point || ID: "<<id<<" | ClusterID: "<<clusterid;
		cout<<"   "<<this->value.at(0)<<" "<<this->value.at(1)<<" "<<this->value.at(2)<<endl;
	}

	float eucledianDistanceFrom(Point p){
		vector<int> v1 = this->value;
		vector<int> v2 = p.getValue();
		float temp = 0;
		for(int i=0; i<v1.size(); i++){
			temp += pow(v1.at(i) - v2.at(i), 2);
		}
		temp = sqrt(temp);
		return temp;
	}
};

#endif
