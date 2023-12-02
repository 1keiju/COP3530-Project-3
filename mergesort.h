#include <iostream>
#include "Movies.h"
#include <vector>

//sourced from Prof. Aman's presentation "6 - Sorting.pdf" slides 88-90
void merge(std::vector<Movie> &movie_list, int left, int middle, int right);
void mergeSort(std::vector<Movie> &movie_list, int left, int right);

//sorted by movie popularity score in descending order (highest to lowest popularity score)
void merge(std::vector<Movie> &movie_list, int left, int middle, int right) {
	//split array in half
	int left_subarray_size = middle - left + 1;
	int right_subarray_size = right - middle;
	std::vector<Movie> left_subarray;
	std::vector<Movie> right_subarray;

	//creating left subarray
	for (int i = 0; i < left_subarray_size; i++) {
		left_subarray.push_back(movie_list[left+i]);
	}

	//creating right subarray
	for (int i = 0; i < right_subarray_size; i++) {
		right_subarray.push_back(movie_list[middle+1+i]);
	}

	//comparing and combining both subarrays
	int i = 0;
	int j = 0;
	int k = left;

	while (i < left_subarray_size && j < right_subarray_size) {
		//comparing and ordering movie with higher popularity score
		if (left_subarray[i].popularityScore >= right_subarray[j].popularityScore) {
			movie_list[k] = left_subarray[i];
			i++;
		}

		else {
			movie_list[k] = right_subarray[j];
			j++;
		}

		k++;
	}

	//case where no more movies in one of the subarrays, add rest
	while (i < left_subarray_size) {
		movie_list[k] = left_subarray[i];
		i++;
		k++;
	}

	while (j < right_subarray_size) {
		movie_list[k] = right_subarray[j];
		j++;
		k++;
	}
}

//partition and merge the subarrays
void mergeSort(std::vector<Movie> &movie_list, int left, int right) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		mergeSort(movie_list, left, middle);
		mergeSort(movie_list, middle+1, right);

		merge(movie_list, left, middle, right);
	}
}
