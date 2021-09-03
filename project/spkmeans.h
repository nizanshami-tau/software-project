#include <stdio.h> 



/*find the eigangap heuristic and return the number of cluster*/
int calc_eiganvalue_gap(float *mat, float *sorted_eiganvalues, int n);

/* given A real symmetric matrix updates A and a matrix V that A is diagonal and all of A eigenvalues
on the diagonal and V columns is the correspondence eigenvector
*/
void jacobi_algorithm_for_eigenvalues(float *A, float *V, int n);

/*initial V to the uint matrix*/
void form_V(float *mat, int n);

void form_diagonal_mat(float *diagonal_mat, float *weighted_adj_mat , int n);

void form_weighted_adj_mat(float *mat, float *data_points, int dim, int n);

/** given D=diag(diagonal_mat) and W=weights_mat
 * calculates I-DWD into normalized_laplacian */
void calc_normalized_laplacian(float *normalized_laplacian, float *diagonal_mat, float *weights_mat, int dim);

/** given a square matrix (mat), sets row and col to be
 * the indexes of the off-diagonal largest absolute value */
void indexes_of_max_off_diag(float *mat, int *row, int *col, int dim);


/** given a square matrix (mat) ,
 * the indexes of its off-diagonal largest absolute value (i,j)
 * and it's dimension (dim)
 * returns t
 */
float get_t(float *mat, int i, int j, int dim);

/** given t, returns c
 */
float get_c(float t);

/* given matrix mat calculates the off(mat)^2 = notm_f(mat) - sum_(i=1)^n a_ii*/
float calc_off_square(float *mat,int n);

/**
 * given diagonal matrix [n*n] and an empty array [n], fills the array with the diagonal values
 */
void diag_to_array(float *diag, float *arr, int n);

/** given array of length dim, and its dimention, fills the array with integers
 * such that arr[i]=i
 */
void fill_ordered_ints(int *arr, int dim);

/**
 * given an array- arr, and another array- indexes, both of length dim,
 * fills indexes with integers [0,dim-1] such that their order dictates a sorted order on arr values.
 * (using QuickSort algorithm)
 */
void quickSort_indexes(float *arr, int *indexes, int dim);

/** fill given matrix with the data from input file */
void read_data(FILE* fp, float *data_points, char *line, int n, int dim);

/*
* calculate distance between two vectors sqrt(sum_(i=1)^n (v1_i-v2_i)^2) (norm2)
*/
float distance(float *v1, float *v2, int dim,int row_v1, int row_v2);

/** given the eigenvectors matrix [n*n] (as columns), an array [n] that dictates an order on the eigenvalues,
 * n (the mat dimention), k, and a result matrix [n*k],
 * fills the result matrix with the normalized first k eigenvectors as columns
 */
void normalized_k_eigenvectors(float *eigenvecs, int *indexes, int n, int k, float *result);

/**
 * returns arr[i][j]
 */
float get(float* arr, int i, int j, int dim);

/**
 * Sets arr[j][i]=item
 */
void set(float* arr, int i, int j, int dim, float item);

/*return target matrix for goal == "wam" */
float *wam(float *data_points, int n, int dim);

/*return an array that contains the diagnoal of the target mateix for goal == "ddg" */
float *ddg(float *data_points,int n, int dim);

/*return target matrix for goal == "lnorm" */
float *lnorm(float *data_points, int n, int dim);

/*return target matrix in shape (n+1,n) the first row is the eigonvalue the other n row is the eigonvector matrix when the goal == "lnorm" */
float *jacobi(float *data_points, int n);

/*return target matrix T in shape (n,k) when goal == "spk"*/
float *spk(float *data_points, int n , int dim, int *k);


static int kmeans(int k, float* data_points, float* centroids, float* utl ,int max_iter, int dim, int n){

/*
 * assigns data points to their closest cluster (measure distance from the centroid)
 * updates the number of cluster for each data point
 */
static void assign(float* data_points, float* clusters, int dim, int n, int k);


/*
 * re-estimates a centroid for each cluster:
 * for each cluster calculate the average of the points assign to it,
 * updates centroids to be the average vector,
 * returns 1 if the old centroids are equal to the new ones.
 */
static short re_estimate(float* data_points, float* clusters,float *utl, int dim, int n, int k) ;

/*
 * adds vec2 to vec1 coordinate wise
 */
static void vec_sum(float* vec1, float* vec2, int dim, int row_vec1, int row_vec2);

/*
 * zeros a given matrix from row start to row end
 */
static void zero_mat(float* clusters , int dim, int n);
