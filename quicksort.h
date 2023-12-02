#include <iostream>
#include "Movies.h"
#include <vector>

//sourced from Prof. Aman's presentation "6 - Sorting.pdf" slides 121-122
int partition(std::vector<Movie> &movie_list, int low, int high, std::string filter, bool descending);
void quickSort(std::vector<Movie> &movie_list, int low, int high, std::string filter, bool descending);

int partition(std::vector<Movie> &movie_list, int low, int high, std::string filter, bool descending) {
	double pivot;
	//setting pivot point, can sort by budget, revenue, runtime, vote average, or popularity 
	if (filter == "budget" || filter == "Budget") {
		pivot = movie_list[low].movieBudget;
	}

	else if (filter == "revenue" || filter == "Revenue") {
		pivot = movie_list[low].movieRevenue;
	}

	else if (filter == "runtime" || filter == "Runtime") {
		pivot = movie_list[low].movieRuntime;
	}

	else if (filter == "vote average" || filter == "Vote Average" || filter == "Vote average") {
		pivot = movie_list[low].voteAverage;
	}
	//popularity as default
	else {
		pivot = movie_list[low].popularityScore;
	}

	int up = low;
	int down = high;

	//while up is still left of down
	while (up < down) {
		//increment until up greater than pivot
		for (int i = up; i < high; i++) {
			//for each search filter: budget, revenue, runtime, vote average, and popularity
			if (filter == "budget" || filter == "Budget") {
				//sort by descending order or ascending order
				if ((descending && movie_list[up].movieBudget < pivot) || (!descending && movie_list[up].movieBudget > pivot)) {
					break;
				}
			}

			else if (filter == "revenue" || filter == "Revenue") {
				if ((descending && movie_list[up].movieRevenue < pivot) || (!descending && movie_list[up].movieRevenue > pivot)) {
					break;
				}
			}

			else if (filter == "runtime" || filter == "Runtime") {
				if ((descending && movie_list[up].movieRuntime < pivot) || (!descending && movie_list[up].movieRuntime > pivot)) {
					break;
				}
			}

			else if (filter == "vote average" || filter == "Vote Average" || filter == "Vote average") {
				if ((descending && movie_list[up].voteAverage < pivot) || (!descending && movie_list[up].voteAverage > pivot)) {
					break;
				}
			}

			else {
				if ((descending && movie_list[up].popularityScore < pivot) || (!descending && movie_list[up].popularityScore > pivot)) {
					break;
				}	
			}
			
			up++;
		}

		//decrement until down less than pivot
		for (int i = high; i > low; i--) {
			if (filter == "budget" || filter == "Budget") {
				if ((descending && movie_list[down].movieBudget > pivot) || (!descending && movie_list[down].movieBudget < pivot)) {
					break;
				}
			}

			else if (filter == "revenue" || filter == "Revenue") {
				if ((descending && movie_list[down].movieRevenue > pivot) || (!descending && movie_list[down].movieRevenue < pivot)) {
					break;
				}
			}

			else if (filter == "runtime" || filter == "Runtime") {
				if ((descending && movie_list[down].movieRuntime > pivot) || (!descending && movie_list[down].movieRuntime < pivot)) {
					break;
				}
			}

			else if (filter == "vote average" || filter == "Vote Average" || filter == "Vote average") {
				if ((descending && movie_list[down].voteAverage > pivot) || (!descending && movie_list[down].voteAverage < pivot)) {
					break;
				}
			}

			else {
				if ((descending && movie_list[down].popularityScore > pivot) || (!descending && movie_list[down].popularityScore < pivot)) {
					break;
				}
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
void quickSort(std::vector<Movie> &movie_list, int low, int high, std::string filter, bool descending) {
	if (low < high) {
		int pivot = partition(movie_list, low, high, filter, descending);
		quickSort(movie_list, low, pivot-1, filter, descending);
		quickSort(movie_list, pivot+1, high, filter, descending);
	}
}
