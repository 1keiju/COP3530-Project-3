#include <iostream>
#include "Movies.h"
#include <vector>
#pragma once
using namespace std;

//sourced from Prof. Aman's presentation "6 - Sorting.pdf" slides 121-122
int partitionPopularity(Movie* &movie_list, int low, int high, bool descending);
void quickSortPopularity(Movie* &movie_list, int low, int high, bool descending);
int partitionRevenue(Movie* &movie_list, int low, int high, bool descending);
void quickSortRevenue(Movie* &movie_list, int low, int high, bool descending);
int partitionBudget(Movie* &movie_list, int low, int high, bool descending);
void quickSortBudget(Movie* &movie_list, int low, int high, bool descending);
int partitionRuntime(Movie* &movie_list, int low, int high, bool descending);
void quickSortRuntime(Movie* &movie_list, int low, int high, bool descending);
int partitionAvg(Movie* &movie_list, int low, int high, bool descending);
void quickSortAvg(Movie* &movie_list, int low, int high, bool descending);

int partitionPopularity(Movie* &movie_list, int low, int high, bool descending) {

    double pivot;

    //setting pivot point
    pivot = movie_list[low].popularityScore;

    int up = low;
    int down = high;

    //while up is still left of down
    while (up < down) {

        //increment until up greater than pivot
        for (int i = up; i < high; i++) {

            //sort by descending order or ascending order
            if ((descending && movie_list[up].popularityScore < pivot) || (!descending && movie_list[up].popularityScore > pivot)) {
                break;
            }

            up++;
        }

        //decrement until down less than pivot
        for (int i = high; i > low; i--) {

            if ((descending && movie_list[down].popularityScore > pivot) || (!descending && movie_list[down].popularityScore < pivot)) {
                break;
            }

            down--;
        }

        //swap up and down
        if (up < down) {
            Movie temp = movie_list[up];
            movie_list[up] = movie_list[down];
            movie_list[down] = temp;
        }
    }

    //swap pivot and down
    Movie temp = movie_list[low];
    movie_list[low] = movie_list[down];
    movie_list[down] = temp;
    return down;
}

int partitionRevenue(Movie* &movie_list, int low, int high, bool descending) {

    double pivot;

    //setting pivot point
    pivot = movie_list[low].movieRevenue;

    int up = low;
    int down = high;

    //while up is still left of down
    while (up < down) {

        //increment until up greater than pivot
        for (int i = up; i < high; i++) {

            //sort by descending order or ascending order
            if ((descending && movie_list[up].movieRevenue < pivot) || (!descending && movie_list[up].movieRevenue > pivot)) {
                break;
            }

            up++;
        }

        //decrement until down less than pivot
        for (int i = high; i > low; i--) {

            if ((descending && movie_list[down].movieRevenue > pivot) || (!descending && movie_list[down].movieRevenue < pivot)) {
                break;
            }

            down--;
        }

        //swap up and down
        if (up < down) {
            Movie temp = movie_list[up];
            movie_list[up] = movie_list[down];
            movie_list[down] = temp;
        }
    }

    //swap pivot and down
    Movie temp = movie_list[low];
    movie_list[low] = movie_list[down];
    movie_list[down] = temp;
    return down;
}

int partitionBudget(Movie* &movie_list, int low, int high, bool descending) {

	double pivot;

	//setting pivot point
    pivot = movie_list[low].movieBudget;

	int up = low;
	int down = high;

	//while up is still left of down
	while (up < down) {

		//increment until up greater than pivot
		for (int i = up; i < high; i++) {

            //sort by descending order or ascending order
            if ((descending && movie_list[up].movieBudget < pivot) || (!descending && movie_list[up].movieBudget > pivot)) {
                break;
            }
			
			up++;
		}

		//decrement until down less than pivot
		for (int i = high; i > low; i--) {

            if ((descending && movie_list[down].movieBudget > pivot) || (!descending && movie_list[down].movieBudget < pivot)) {
                break;
            }

			down--;
		}

		//swap up and down
		if (up < down) {
			Movie temp = movie_list[up];
			movie_list[up] = movie_list[down];
			movie_list[down] = temp;
		}
	}

	//swap pivot and down
	Movie temp = movie_list[low];
	movie_list[low] = movie_list[down];
	movie_list[down] = temp;
	return down;
}

int partitionRuntime(Movie* &movie_list, int low, int high, bool descending) {

    double pivot;

    //setting pivot point
    pivot = movie_list[low].movieRuntime;

    int up = low;
    int down = high;

    //while up is still left of down
    while (up < down) {

        //increment until up greater than pivot
        for (int i = up; i < high; i++) {

            //sort by descending order or ascending order
            if ((descending && movie_list[up].movieRuntime < pivot) || (!descending && movie_list[up].movieRuntime > pivot)) {
                break;
            }

            up++;
        }

        //decrement until down less than pivot
        for (int i = high; i > low; i--) {

            if ((descending && movie_list[down].movieRuntime > pivot) || (!descending && movie_list[down].movieRuntime < pivot)) {
                break;
            }

            down--;
        }

        //swap up and down
        if (up < down) {
            Movie temp = movie_list[up];
            movie_list[up] = movie_list[down];
            movie_list[down] = temp;
        }
    }

    //swap pivot and down
    Movie temp = movie_list[low];
    movie_list[low] = movie_list[down];
    movie_list[down] = temp;
    return down;
}

int partitionAvg(Movie* &movie_list, int low, int high, bool descending) {

    double pivot;

    //setting pivot point
    pivot = movie_list[low].voteAverage;

    int up = low;
    int down = high;

    //while up is still left of down
    while (up < down) {

        //increment until up greater than pivot
        for (int i = up; i < high; i++) {

            //sort by descending order or ascending order
            if ((descending && movie_list[up].voteAverage < pivot) || (!descending && movie_list[up].voteAverage > pivot)) {
                break;
            }

            up++;
        }

        //decrement until down less than pivot
        for (int i = high; i > low; i--) {

            if ((descending && movie_list[down].voteAverage > pivot) || (!descending && movie_list[down].voteAverage < pivot)) {
                break;
            }

            down--;
        }

        //swap up and down
        if (up < down) {
            Movie temp = movie_list[up];
            movie_list[up] = movie_list[down];
            movie_list[down] = temp;
        }
    }

    //swap pivot and down
    Movie temp = movie_list[low];
    movie_list[low] = movie_list[down];
    movie_list[down] = temp;
    return down;
}

//partition and sort lower and upper sub arrays
void quickSortPopularity(Movie* &movie_list, int low, int high, bool descending) {
    if (low < high) {
        int pivot = partitionPopularity(movie_list, low, high, descending);
        quickSortPopularity(movie_list, low, pivot-1, descending);
        quickSortPopularity(movie_list, pivot+1, high, descending);
    }
}

//partition and sort lower and upper sub arrays
void quickSortRevenue(Movie* &movie_list, int low, int high, bool descending) {
	if (low < high) {
		int pivot = partitionRevenue(movie_list, low, high, descending);
		quickSortRevenue(movie_list, low, pivot-1, descending);
		quickSortRevenue(movie_list, pivot+1, high, descending);
	}
}

//partition and sort lower and upper sub arrays
void quickSortBudget(Movie* &movie_list, int low, int high, bool descending) {
    if (low < high) {
        int pivot = partitionBudget(movie_list, low, high, descending);
        quickSortBudget(movie_list, low, pivot-1, descending);
        quickSortBudget(movie_list, pivot+1, high, descending);
    }
}

//partition and sort lower and upper sub arrays
void quickSortRuntime(Movie* &movie_list, int low, int high, bool descending) {
    if (low < high) {
        int pivot = partitionRuntime(movie_list, low, high, descending);
        quickSortRuntime(movie_list, low, pivot-1, descending);
        quickSortRuntime(movie_list, pivot+1, high, descending);
    }
}

//partition and sort lower and upper sub arrays
void quickSortAvg(Movie* &movie_list, int low, int high, bool descending) {
    if (low < high) {
        int pivot = partitionAvg(movie_list, low, high, descending);
        quickSortAvg(movie_list, low, pivot-1, descending);
        quickSortAvg(movie_list, pivot+1, high, descending);
    }
}
