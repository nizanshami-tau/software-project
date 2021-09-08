"""
Kmeans_pp implementation in Python
finding a good initialization of centroids for the "kmeans" algorithm
Software Project ex. 2

Nizan Shemi
206962912

Amit Elyasi
316291434

"""

import spkmeans as kmeans
import numpy as np
import pandas as pd
import sys


def Kmeans_pp(datapoints, k):
    n = len(datapoints)
    datapoints = np.array([np.array(point) for point in datapoints])
    centroids = [0]
    centroids[0] = np.random.choice(n, 1)[0]
    dists = np.zeros((n, k))
    min_dists = np.zeros(n)
    for z in range(k - 1):
        for i in range(n):
            dists[i][z] = np.inner(datapoints[i] - datapoints[centroids[z]], datapoints[i] - datapoints[centroids[z]])
            min_dists[i] = min(dists[i][0:z + 1])
        dists_sum = np.sum(min_dists)
        probabilities = [dist / dists_sum for dist in min_dists]

        new_centroid_indx = np.random.choice(n, 1, p=probabilities)[0]
        centroids.append(new_centroid_indx)
    return centroids


def arrToSeq(arr):
    return [item for vec in arr for item in vec]


def print_mat(mat):
    mat = np.round(mat, 4)
    for i in range(len(mat)):
        if i > 0:
            print("\n", end="")
        for j in range(len(mat[0])):
            print(format(mat[i][j], ".4f"), end="")
            if j < len(mat[0]) - 1:
                print(",", end="")


def print_diag(diag):
    diag = np.round(diag, 4)
    for i in range(len(diag)):
        if i > 0:
            print("\n", end="")
        for j in range(len(diag)):
            if i == j and abs(diag[i] >= 0.0001):
                print(format(diag[i], ".4f"), end="")
            else:
                print("0.0000", end="")
            if j < len(diag) - 1:
                print(",", end="")


def main():
    np.random.seed(0)
    args = sys.argv

    # reading arguments
    if len(args) != 3:
        print("INPUT ERROR:\nthe number of argument is incorrect")
        return 1
    k, goal, file = args[1], args[2], args[3]
    try:
        k = int(k)
    except ValueError:
        print("INPUT ERROR:\nk has to be an integer")
        return 1
    if k <= 0:
        print("INPUT ERROR:\nk can't be <= 0")
        return 1

    datapoints_table = pd.read_csv(file, header=None)
    datapoints_matrix = datapoints_table.values.tolist()

    if len(datapoints_matrix) <= k:
        print(f"INPUT ERROR:\nthere are less or equal to {k} data points")
        return False

    mat = kmeans.calc_transformation_matrix(k, goal, datapoints_matrix, len(datapoints_matrix[0]),
                                           len(datapoints_matrix))

    if goal != "spk" and goal != "ddg":
        print_mat(mat)
        return

    if goal == "ddg":
        print_diag(mat)
        return

    if k == 0:
        k = len(mat[0])

    centroids_indexes = Kmeans_pp(mat, k)

    ##### assuming datapoints_matrix is 2dim array
    datapoints = arrToSeq(datapoints_matrix)
    centroids = arrToSeq([datapoints_matrix[i] for i in centroids_indexes])

    ## print the centroid indexes
    # print(",".join(str(indx) for indx in centroids_indexes))

    # find the final centroids using K-means algorithm
    centroids = kmeans.fit(k, datapoints, centroids, 300, len(datapoints_matrix))
    print_mat(centroids)


if __name__ == "__main__":
    main()
