#include <iostream>
#include "Movies.h"
#include <vector>

//sourced from Prof. Aman's presentation "6 - Sorting.pdf" slides 121-122
int partition(std::vector<Movie> &movie_list, int low, int high);
void quickSort(std::vector<Movie> &movie_list, int low, int high);

//sorted by movie popularity score in descending order (highest to lowest popularity score)
int partition(std::vector<Movie> &movie_list, int low, int high) {
	//setting pivot point
	int pivot = movie_list[low].popularityScore;
	int up = low;
	int down = high;

	//while up is still left of down
	while (up < down) {
		//increment until up greater than pivot
		for (int i = up; i < high; i++) {
			if (movie_list[up].popularityScore < pivot) {
				break;
			}
			up++;
		}

		//decrement until down less than pivot
		for (int i = high; i > low; i--) {
			if (movie_list[down].popularityScore > pivot) {
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

//partition and sort lower and upper subarrays
void quickSort(std::vector<Movie> &movie_list, int low, int high) {
	if (low < high) {
		int pivot = partition(movie_list, low, high);
		quickSort(movie_list, low, pivot-1);
		quickSort(movie_list, pivot+1, high);
	}
}
