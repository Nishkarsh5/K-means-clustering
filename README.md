## K-Means Clustering

### Summary

Parallel implementation of **K-means clustering** algorithm in **OpenMP and Pthreads**, and sequential implementation of the same: Because <ins>performance comparison</ins> is one of the goal.

### Algorithm

The goal of the algorithm is to find k partitions (or groups) in an unlabeled set of data points such that points with partition have high similarity while the points belonging to different partitions have lower similarity.

### Verbal Pseudo Code

Given: n (data points), and k (number of clusters)
* 1. For a given k, choose k points randomly from the given data-points and call them *centroids*.
* 2. For each point, calculate which centroid it is nearest to (by calculating *euclidean distance* among point and centroids). One point cannot belong to more than one data points
* 3. Let's call each collection of point: A cluster.
* 4. For every cluster, calculate its *mean* and claim it as its centroid.
* 5. Go to step-2) until the centroids of clusters are not changing or the clusters remains the same (the stopping criteria.)

***

### Directory Structure
#### Files
- `graphs.py`: Used to draw graphs for performance analysis purposes; `graphs` folder contains corresponding graphs.
- `dataset.py`: Can be used to generate datasets.
- `run.sh`: Bash file to compile and execute.

#### Folders: OpenMP, Pthreads, and Sequential (abstract structure: X)
- `main_X.c`: Main file.

- `lab1_io.h`: Header file for taking dataset as input, and outputting as clusters.
- `lab1_io.c`: Implemented functions that are mentioned in header file.

- `lab1_X.h`: Function definitions corresponding to the implementation to X
- `lab1_X.cpp`: Function Implementation

***

### Sequential Implementation:

Assume this to be the *function call* we have to implement:
```c
void kmeans_sequential(int N, int K, int* data_points, int** data_point_cluster, float** centroids, int* num_iterations);

/* The arguments are:
	N 				   : no. of data points (input)
	K 				   : no. of clusters (input)
	data_points 	   : 1D array of data_points (input)
						 format - 1 data point uses 3 consecutive indices, ie
	     				 -----------------------------------------------
						| pt1_x | pt1_y | pt1_z | pt2_x | pt2_y | pt2_z | ...
		 				 -----------------------------------------------
	data_point_cluster : 1D array of data_points and their cluster id (to be computed)
						 format - 1 data point uses 4 consecutive indices, ie
						  -------------------------------------------------------------------------------
						 | pt1_x | pt1_y | pt1_z | pt1_clusterid | pt2_x | pt2_y | pt2_z | pt2_clusterid | ...
	 					  -------------------------------------------------------------------------------
	 					  cluster_id - range between 0 to K-1
	centroids		   : 1D array of centroids of each iteration (to be computed)
						 format - 1 iteration uses K consecutive indices
						 *include initial centroids in the array (the 1st K entries of the array), ie
						  -------------------------------------------------------------------------------------
						 | cent0_init_x | cent0_init_y | cent0_init_z | ... | centK_init_x centK_init_y centK-1_init_z |
						  -------------------------------------------------------------------------------------
						 | cent0_it1_x | cent0_it1_y | cent0_it1_z | ... | centK_it1_x centK_it1_y centK-1_it1_z |
						  -------------------------------------------------------------------------------------
						 | cent0_it2_x | cent0_it2_y | cent0_it2_z | ... | centK_it2_x centK_it2_y centK-1_it2_z | ...
						  -------------------------------------------------------------------------------------
	num_iterations     : no of iterations of k-means algo = (length of centroids array / K) - 1 (to be computed)
*/
```

For a little easiness, in this abstraction, we will use data structures in vector form, and then at the end we will create pointers that point to that memory, and return them.

Let us create some data structures:
```c
# For data points: Assume they are int of dimensionality 3
vector<tuple<int, int, int>> dataPoints;
# Each index is a cluster, a each vector of int tells us the data-point it contains
vector<vector<int>> clusterIndex(K);
# Centroid points, of all iterations
vector<vector<tuple<float, float, float>>> clusterPoints;
```

We intialise cluster *centroids* as:
```c
vector<tuple<float, float, float>> tempVec0;
for(int i=0; i<K; i++){
	tempVec0.push_back(make_tuple((float)get<0>(dataPoints.at(i)), (float)get<1>(dataPoints.at(i)), (float)get<2>(dataPoints.at(i))));
}
clusterPoints.push_back(tempVec0);
```

#### Choosing Centroids

Normally, the centroids can (and should) be chosen randomly for not to lose the generality of the algorithm. But here, because we will also calculate performance between parallel and sequential implementation: We have to keep the initial centroids as the same, for fair (and correct) comparisons.

What one can do is:
* Keep the seed same (this is better)
* Or use some statically defined similarity measure: Like taking the k intial data points as centroids (but we will do this.)

```c
// Loop over maximum iterations

while(iter<max_num_iterations){

	// Find which cluster is closest to every point
	for(int i=0; i<dataPoints.size(); i++){
		int clusI=0;
		float dist=FLT_MAX;

		for(int j=0; j<clusterPoints.at(iter).size(); j++){
			// Get Eucleadian distance
			float temp = getDistance(dataPoints.at(i), clusterPoints.at(iter).at(j));
			if(temp < dist){
				dist = temp;
				clusI = j;
			}
		}
		(clusterIndex.at(clusI)).push_back(i);
	}

	// Calculate new centroids by taking a mean of a updated clusters

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

	// Use new centroids from now
	clusterPoints.push_back(tempVec);

	// Check convergence criteria
	float changeInCentroids = 0;
	for(int i=0; i<(clusterPoints.at(iter)).size(); i++){
		changeInCentroids += getDistance(clusterPoints.at(iter).at(i), clusterPoints.at(iter+1).at(i));
	}

	iter+=1;

	if(changeInCentroids < 0.01){
		// A good time to stop
		break;
	}
}

```

### Parallel Implementation: OpenMP

The algorithm and the implementation of it, remains the same: The necessary changes are shown:

```c
// Initialise threads array and the mutex lock
pthread_t kmPthreads[num_threads]; 
pthread_mutex_init(&lock, NULL); 
```