#include <iostream>
#include <vector>
#include "lab1_pthread.h"
#include "lab1_io.h"
#include <pthread.h>
#include <float.h>

#include <tuple>
#include <cmath>

using namespace std;

pthread_mutex_t lock;

int iter;
int numDataPoints;
int numThreads;
int max_num_iterations = 1000;

vector<tuple<int, int, int>> dataPoints; //collection of datapoints
vector<vector<int>> clusterIndex; //indices of cluster, each cluster vector contains the indices of data points 
vector<vector<tuple<float, float, float>>> clusterPoints; //cluster centroids and also its history
vector<vector<vector<float>>> tempCentroidThreading; //each thread - having a, b, c centroid of cluster, with values (int) it sees
vector<vector<vector<int>>> clusterIndexThreading; //for threading

// get distance from datapoint-clusterpoint or clusterpoint-cluserpoint
float getDistance(tuple<int, int, int> i, tuple<float, float, float> f){
	return sqrt(pow((get<0>(f) - (float)get<0>(i)), 2) + pow((get<1>(f) - (float)get<1>(i)), 2) + pow((get<2>(f) - (float)get<2>(i)), 2));
}
float getDistance(tuple<float, float, float> i, tuple<float, float, float> f){
	return sqrt(pow((get<0>(f) - get<0>(i)), 2) + pow((get<1>(f) - get<1>(i)), 2) + pow((get<2>(f) - get<2>(i)), 2));
}

void* kmeansThread(void *tid){
	int *id = (int*) tid;
	int length_per_thread = numDataPoints/numThreads;
	int start = (*id)*length_per_thread;
	int end;

	if(*id == numThreads-1){
		end = numDataPoints;
	}else{
		end = start + length_per_thread;
	}
	// cout<<"id " <<*id<<" lengthperthread "<<length_per_thread<<endl;
	// cout<<"start "<<start<<" end "<<end<<endl;
	// only loop through the data points each thread had gotten

	// assign each data points to cluster it is closest to
	for(int i=start; i<end; i++){
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
		clusterIndexThreading.at(*id).at(clusI).push_back(i); // pushed datapoint ID into proper cluster into proper thread
	}

	// calculate new centroids by taking a mean
	for(int i=0; i<clusterIndexThreading.at(*id).size(); i++){
		float a=0, b=0, c=0;
		for(int j=0; j<clusterIndexThreading.at(*id).at(i).size(); j++){
			a += (float)get<0>(dataPoints.at(clusterIndexThreading.at(*id).at(i).at(j)));
			b += (float)get<1>(dataPoints.at(clusterIndexThreading.at(*id).at(i).at(j)));
			c += (float)get<2>(dataPoints.at(clusterIndexThreading.at(*id).at(i).at(j)));
		}
		(tempCentroidThreading.at(*id).at(i)).push_back(a);
		(tempCentroidThreading.at(*id).at(i)).push_back(b);
		(tempCentroidThreading.at(*id).at(i)).push_back(c);
		(tempCentroidThreading.at(*id).at(i)).push_back((float)clusterIndexThreading.at(*id).at(i).size());
	}

	return NULL;
}


void printClusterCentroids(vector<tuple<float, float, float>> f){;
	for(int i=0; i<f.size(); i++){
		cout<<get<0>(f.at(i))<<" "<<get<1>(f.at(i))<<" "<<get<2>(f.at(i))<<" :: ";		
	}
	cout<<"\n";
}

void kmeans_pthread(int num_threads, int N, int K, int* data_points, int** data_point_cluster, float** centroids, int* num_iterations )
{

	// --------------------------------------------init variables----------------------------------
	// putting values into global variables

	numThreads = num_threads; 
	numDataPoints = N;

	// cout<<"num of iter: "<<*num_iterations<<endl;
	// cout<<"num threads" <<numThreads<<endl;
	// cout<<"num data points"<<numDataPoints<<endl;

	for(int i=0; i<num_threads; i++){
		vector<vector<int>> temp;
		for(int j=0; j<K; j++){
			vector<int> temp2;
			temp.push_back(temp2);
		}
		clusterIndexThreading.push_back(temp);
	}	
	for(int i=0; i<num_threads; i++){
		vector<vector<float>> temp;
		for(int j=0; j<K; j++){
			vector<float> temp2;
			temp.push_back(temp2);
		}
		tempCentroidThreading.push_back(temp);
	}
	for(int i=0; i<K; i++){
		vector<int> temp;
		clusterIndex.push_back(temp);
	}

	pthread_t kmPthreads[num_threads]; // initalise the thread array 
	int *tid = (int*)malloc(sizeof(int)*num_threads); // allocate its memory
	pthread_mutex_init(&lock, NULL); // initialise the mutex lock


	// --------------------------------------------init values (if needed)--------------------------
	// put data_points in dataPoints vector
	for(int i=0; i<N; i++){
		dataPoints.push_back(make_tuple(data_points[i*3], data_points[i*3+1], data_points[i*3+2]));
	}

	// initialise K random points as cluster centers
	vector<tuple<float, float, float>> tempVec0;
	for(int i=0; i<K; i++){
		tempVec0.push_back(make_tuple((float)get<0>(dataPoints.at(i)), (float)get<1>(dataPoints.at(i)), (float)get<2>(dataPoints.at(i))));
	}
	clusterPoints.push_back(tempVec0);
	iter = 0;

	// for(int i=0; i<clusterPoints.at(iter).size(); i++){
	// 	printClusterCentroids((clusterPoints.at(iter)).at(i));
	// }
	// printClusterCentroids(clusterPoints.at(iter));
	//------------------------------------------- rest thread work ---------------------------------
	while(iter<max_num_iterations){
		// assign each thread to do some work with divided data points
		for(int i=0; i<clusterIndex.size(); i++){
			clusterIndex.at(i).clear();
		}

		for(int i=0; i<num_threads; i++){
			for(int j=0; j<K; j++){
				clusterIndexThreading.at(i).at(j).clear();
			}
		}	
		for(int i=0; i<num_threads; i++){
			for(int j=0; j<K; j++){
				tempCentroidThreading.at(i).at(j).clear();
			}
		}

		for(int i=0; i<num_threads; i++){
			tid[i] = i;
			// cout<<"id-"<<tid[i]<<endl;
			pthread_create(&kmPthreads[i], NULL, kmeansThread, &tid[i]);
		}
		for(int i=0; i<num_threads; i++){
			pthread_join(kmPthreads[i], NULL);
		}

		// wait for each thread to do its work.

		// manipulate output of threads here
		// get all threads clusterIndexThreading and tempCentroidThreading and put them into other variables by manipulating thread results
		for(int i=0; i<num_threads; i++){
			for(int j=0; j<K; j++){
				for(int k=0; k<clusterIndexThreading.at(i).at(j).size(); k++){
					clusterIndex.at(j).push_back(clusterIndexThreading.at(i).at(j).at(k));
				}
			}
		}

		vector<tuple<float, float, float>> newVec;
		for(int i=0; i<K; i++){
			float a=0, b=0, c=0, n=0;
			for(int j=0; j<num_threads; j++){
				a += tempCentroidThreading.at(j).at(i).at(0);
				b += tempCentroidThreading.at(j).at(i).at(1);
				c += tempCentroidThreading.at(j).at(i).at(2);
				n += tempCentroidThreading.at(j).at(i).at(3);
			}
			a = a/n;
			b = b/n;
			c = c/n;
			newVec.push_back(make_tuple(a, b, c));
		}
		clusterPoints.push_back(newVec);
		// printClusterCentroids(clusterPoints.at(iter));

		// check if converged
		float changeInCentroids = 0;
		for(int i=0; i<(clusterPoints.at(iter)).size(); i++){
			changeInCentroids += getDistance(clusterPoints.at(iter).at(i), clusterPoints.at(iter+1).at(i));
		}
		// cout<<"amount "<<changeInCentroids<<"\n";
		iter += 1;
		if(changeInCentroids < 0.01){
			// cout<<"[*] Converged after "<<iter<<" iterations\n";
			break;
		}
	
		// cout<<"[*] Change Amount: "<<changeInCentroids<<endl;
		if(iter > max_num_iterations){
			break;
		}
		// cout<<"iter "<<iter<<endl;
	}

	// put all calculated values into variable as needed (because of the rest of the good written code)
	// cout<<"[*] Formed Cluster Sizes: \n";
	// for(int i=0; i<clusterIndex.size(); i++){
	// 	cout<<clusterIndex.at(i).size()<<" | ";
	// }
	// cout<<"\n";

	// cout<<"[!] Iterations Used: "<<iter<<endl;
	*num_iterations = iter;
	*data_point_cluster = (int*)malloc(sizeof(int)*(N*4));
	*centroids = (float*)malloc(sizeof(float)*(K*3*(iter+1)));


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