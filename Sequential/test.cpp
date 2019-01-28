
#include <iostream>
#include <vector>
#include <fstream>

#include <tuple>
#include "point.h"
#include "cluster.h"

using namespace std;


int main(int argc, char *argv[]){
	vector<Point> points;
	Point p(1, make_tuple(1,2,3));
	points.push_back(p);
	// points.at(0).print();

	Cluster c(1, points.at(0));
	c.print();
}