// Sequential: K-Means Clustering Algorithm

//--------------------- Design
// S is a set of points (each a 3 dimensional vector)
// k is the required number of clusters
// take k values randomly out of S
// find the nearest points
// Create partitions
// find mean in the partitions
// create again partitions
// repeat until convergence/

//---------------------_Code Here ---------------------//

#include <iostream>
#include <vector>
#include <fstream>

#include "point.h"
#include "cluster.h"

using namespace std;


int main(int argc, char *argv[]){
	int totalPoints = 9;
	int dimensionality = 3;
	int k = 3;
	int maxIterations = 5;

	ifstream file("./data.txt");

	vector<Point> points;

	for(int i=0; i<totalPoints; i++){
		int a, b, c;
		file>>a>>b>>c;
		points.push_back(Point(i, make_tuple((int)a, (int)b, (int)c)));
	}
	cout<<points.size()<<endl;
	for(int i=0; i<points.size(); i++){
		(points.at(i)).print();
	}
}