#include <iostream>
#include <vector>
#include "lab1_sequential.h"
#include "lab1_io.h"

#include <tuple>
#include <float.h>
#include <cmath>

using namespace std;

// 1. intialise k random chosen centroids
// 2. calc mean of centroid
// and rearragne points
// till converge

void displayTuple(tuple <int, int, int> dp){
	// display the tuple
	cout<<get<0>(dp)<<" "<<get<1>(dp)<<" "<<get<2>(dp)<<endl;
}

void printClusterCentroids(vector<tuple<float, float, float>> f){;
	for(int i=0; i<f.size(); i++){
		cout<<get<0>(f.at(i))<<" "<<get<1>(f.at(i))<<" "<<get<2>(f.at(i))<<" :: ";		
	}
	cout<<"\n";
}

void printDataPoints(vector<tuple<int, int, int>> f){;
	for(int i=0; i<f.size(); i++){
		cout<<get<0>(f.at(i))<<" "<<get<1>(f.at(i))<<" "<<get<2>(f.at(i))<<endl;		
	}
}


float getDistance(tuple<int, int, int> i, tuple<float, float, float> f){
	return sqrt(pow((get<0>(f) - (float)get<0>(i)), 2) + pow((get<1>(f) - (float)get<1>(i)), 2) + pow((get<2>(f) - (float)get<2>(i)), 2));
}
float getDistance(tuple<float, float, float> i, tuple<float, float, float> f){
	return sqrt(pow((get<0>(f) - get<0>(i)), 2) + pow((get<1>(f) - get<1>(i)), 2) + pow((get<2>(f) - get<2>(i)), 2));
}

void kmeans_sequential(int N,
					int K,
					int* data_points,
					int** data_point_cluster,
					float** centroids,
					int* num_iterations
					){

*num_iterations = 50;

vector<tuple<int, int, int>> dataPoints;
vector<vector<int>> clusterIndex(K);
vector<vector<tuple<float, float, float>>> clusterPoints;

// put data_points in dataPoints vector
for(int i=0; i<N; i++){
	dataPoints.push_back(make_tuple(data_points[i*3], data_points[i*3+1], data_points[i*3+2]));
}

// initialise K random points as cluster centers
vector<tuple<float, float, float>> tempVec0;
for(int i=0; i<K; i++){
	int r = rand() % (N+1);
	tempVec0.push_back(make_tuple((float)get<0>(dataPoints.at(r)), (float)get<1>(dataPoints.at(r)), (float)get<2>(dataPoints.at(r))));
}
clusterPoints.push_back(tempVec0);

// for(int i=0; i<clusterPoints.size(); i++){
// 	cout<<"[*] Initialise Centroid Points\n";
// 	printClusterCentroids(clusterPoints.at(i));
// }

//loop and fill baby
bool convergenceFlag = false;
int iter=0;
while(iter<*num_iterations){
	//loop over points and fill into cluster
	for(int i=0; i<clusterIndex.size(); i++){
		clusterIndex.at(i).clear();
	}

	for(int i=0; i<dataPoints.size(); i++){
		// see which cluster is closest to this point
		int clusI=0;
		float dist=FLT_MAX;
		for(int j=0; j<clusterPoints.at(iter).size(); j++){
			float temp = getDistance(dataPoints.at(i), clusterPoints.at(iter).at(j));
			if(temp < dist){
				dist = temp;
				clusI = j;
			}
		}
		(clusterIndex.at(clusI)).push_back(i);
	}

	// calculate new centroids by taking a mean
	vector<tuple<float, float, float>> tempVec;
	for(int i=0; i<clusterIndex.size(); i++){
		float a=0, b=0, c=0;
		for(int j=0; j<clusterIndex.at(i).size(); j++){
			a += (float)get<0>(dataPoints.at(clusterIndex.at(i).at(j)));
			b += (float)get<1>(dataPoints.at(clusterIndex.at(i).at(j)));
			c += (float)get<2>(dataPoints.at(clusterIndex.at(i).at(j)));
		}
		a = a/clusterIndex.at(i).size();
		b = b/clusterIndex.at(i).size();
		c = c/clusterIndex.at(i).size();
		tempVec.push_back(make_tuple(a, b, c));
	}

	// put new centroids into clusterPoints
	clusterPoints.push_back(tempVec);
	// printClusterCentroids(clusterPoints.at(iter+1));

	// check from how much amount does the centroid changes
	float changeInCentroids = 0;
	for(int i=0; i<(clusterPoints.at(iter)).size(); i++){
		changeInCentroids += getDistance(clusterPoints.at(iter).at(i), clusterPoints.at(iter+1).at(i));
	}
	if(changeInCentroids < 0.01){
		// cout<<"[*] Converged at "<<iter<<" iterations\n";
		break;
	}
	// cout<<"[*] Change Amount: "<<changeInCentroids<<endl;
	iter+=1;
}

// cout<<"[*] Formed Cluster Sizes: \n";
// for(int i=0; i<clusterIndex.size(); i++){
// 	cout<<clusterIndex.at(i).size()<<" | ";
// }
// cout<<"\n";

// cout<<"[!] Iterations Used: "<<iter<<endl;
*data_point_cluster = (int*)malloc(sizeof(int)*(N*4));
*centroids = (float*)malloc(sizeof(float)*(K*3*(*num_iterations+1)));


// put calculated values back into the pointers to continue the already coded post-processing
for(int i=0; i<N; i++){
	*(*data_point_cluster + i*4) = data_points[i*3];
	*(*data_point_cluster + i*4 + 1) = data_points[i*3+1];
	*(*data_point_cluster + i*4 + 2) = data_points[i*3+2];
}

for(int i=0; i<clusterIndex.size(); i++){
	for(int j=0; j<clusterIndex.at(i).size(); j++){
		*(*data_point_cluster + clusterIndex.at(i).at(j)*4 + 3) = i;
	}
}

for(int i=0; i<clusterPoints.size(); i++){
	for(int j=0; j<clusterPoints.at(i).size(); j++){
		*(*centroids + j*3 + i*K*3) = get<0>(clusterPoints.at(i).at(j));
		*(*centroids + j*3 + i*K*3 + 1) = get<1>(clusterPoints.at(i).at(j));
		*(*centroids + j*3 + i*K*3 + 2) = get<2>(clusterPoints.at(i).at(j));
	}
}

}
