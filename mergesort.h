#include <iostream>
#include "Movies.h"
#include <vector>

//sourced from Prof. Aman's presentation "6 - Sorting.pdf" slides 88-90
void merge(std::vector<Movie> &movie_list, int left, int middle, int right, std::string filter, bool descending);
void mergeSort(std::vector<Movie> &movie_list, int left, int right, std::string filter, bool descending);

void merge(std::vector<Movie> &movie_list, int left, int middle, int right, std::string filter, bool descending) {
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
	int i = 0; //left subarray index
	int j = 0; //right subarray index
	int k = left; //merged subarray index

	while (i < left_subarray_size && j < right_subarray_size) {
		//for each search filter: budget, revenue, runtime, vote average, and popularity
		if (filter == "budget" || filter == "Budget") {
			//sort by descending order or ascending order
			if ((descending && left_subarray[i].movieBudget >= right_subarray[j].movieBudget) || (!descending && left_subarray[i].movieBudget <= right_subarray[j].movieBudget)) {
				movie_list[k] = left_subarray[i];
				i++;
			}
			else {
				movie_list[k] = right_subarray[j];
				j++;
			}
		}

		else if (filter == "revenue" || filter == "Revenue") {
			if ((descending && left_subarray[i].movieRevenue >= right_subarray[j].movieRevenue) || (!descending && left_subarray[i].movieRevenue <= right_subarray[j].movieRevenue)) {
				movie_list[k] = left_subarray[i];
				i++;
			}
			else {
				movie_list[k] = right_subarray[j];
				j++;
			}
		}

		else if (filter == "runtime" || filter == "Runtime") {
			if ((descending && left_subarray[i].movieRuntime >= right_subarray[j].movieRuntime) || (!descending && left_subarray[i].movieRuntime <= right_subarray[j].movieRuntime)) {
				movie_list[k] = left_subarray[i];
				i++;
			}
			else {
				movie_list[k] = right_subarray[j];
				j++;
			}
		}

		else if (filter == "vote average" || filter == "Vote Average" || filter == "Vote average") {
			if ((descending && left_subarray[i].voteAverage >= right_subarray[j].voteAverage) || (!descending && left_subarray[i].voteAverage <= right_subarray[j].voteAverage)) {
				movie_list[k] = left_subarray[i];
				i++;
			}
			else {
				movie_list[k] = right_subarray[j];
				j++;
			}
		}

		else {
			if ((descending && left_subarray[i].popularityScore >= right_subarray[j].popularityScore) || (!descending && left_subarray[i].popularityScore <= right_subarray[j].popularityScore)) {
				movie_list[k] = left_subarray[i];
				i++;
			}
			else {
				movie_list[k] = right_subarray[j];
				j++;
			}
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
void mergeSort(std::vector<Movie> &movie_list, int left, int right, std::string filter, bool descending) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		mergeSort(movie_list, left, middle, filter, descending);
		mergeSort(movie_list, middle+1, right, filter, descending);

		merge(movie_list, left, middle, right, filter, descending);
	}
}
