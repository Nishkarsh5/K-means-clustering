#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point{

private:
	int id; //id of the point
	vector<float> value; //value
	int clusterid; //which cluster he is in?

public:
	Point(){}
	Point(int i, vector<float> v){
		this->id = i;
		this->value = v;
		this->clusterid = -1;
	}
	
	int getID(){return id;} //get id of point
	int getClusterID(){return clusterid;} //get cluster id it belongs to
	vector<float> getValue(){
		return value;
	}

	void setClusterID(int i){ this->clusterid = i;} //set cluster id
	void print(){ //print the shit
		cout<<"[*] Point || ID: "<<id<<" | ClusterID: "<<clusterid;
		for(int i=0; i<this->value.size(); i++){
			cout<<"   "<<this->value.at(i);
		}
		cout<<endl;
	}

	float eucledianDistanceFrom(Point p){
		vector<float> v1 = this->value;
		vector<float> v2 = p.getValue();
		float temp = 0;
		for(int i=0; i<v1.size(); i++){
			temp += powf(v1.at(i) - v2.at(i), 2);
		}
		temp = sqrtf(temp);
		return temp;
	}
};

#endif
