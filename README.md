## K-Means Clustering

Here I implement the sequential and parallel version of, the famous unsupervised algorithm **K-means clustering**, that is used in various application in a variety of areas in engineering.

The goal of the algorithm is to find k partitions (or groups) in an unlabeled set of data points such that points with partition have high similarity while the points belonging to different partitions have lower similarity.

Algorithm:

Given: n (data points), and k (number of clusters)
	1. For a given k, choose k points randomly from the given data-points and call them centroids.
	2. For each point, calculate which centroid it is nearest to (by calculating euclidean distance among point and centroids). One point cannot belong to more than one data points
	3. Let's call each collection of point: A cluster.
	4. For every cluster, calculate its mean and claim it as its centroid.
	5. Go to step-2) until the centroids of clusters are not changing or the clusters remains the same (the stopping criteria.)

So, let us first implement the algorithm sequentially, after that we will structure its parts to parallelize it using openMP and Pthreads.

Assume this to be the function call we have to implement.
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
# each index is a cluster, a each vector of int tells us the data-point it contains
vector<vector<int>> clusterIndex(K);
# centroid points, of all iterations
vector<vector<tuple<float, float, float>>> clusterPoints;
```

We intialise
```c
vector<tuple<float, float, float>> tempVec0;
for(int i=0; i<K; i++){
	tempVec0.push_back(make_tuple((float)get<0>(dataPoints.at(i)), (float)get<1>(dataPoints.at(i)), (float)get<2>(dataPoints.at(i))));
}
clusterPoints.push_back(tempVec0);
```

