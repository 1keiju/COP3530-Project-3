#include <iostream>
#include "Movies.h"
#include <vector>

//sourced from Prof. Aman's presentation "6 - Sorting.pdf" slides 121-122
int partition(std::vector<Movie> &movie_list, int low, int high, std::string filter, bool descending);
void quickSort(std::vector<Movie> &movie_list, int low, int high, std::string filter, bool descending);

int partition(std::vector<Movie> &movie_list, int low, int high, std::string filter, bool descending) {
	//setting pivot point, can sort by id, popularity, budget, revenue, runtime, vote average, or vote count
	double pivot;
	if (filter == "id" || filter == "ID" || filter == "Id") {
		pivot = movie_list[low].movieID;
	}
	else if (filter == "budget" || filter == "Budget") {
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
	else if (filter == "vote count" || filter == "Vote Count" || filter == "Vote count") {
		pivot = movie_list[low].voteCount;
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
			//for each search filter: id, popularity, budget, revenue, runtime, vote average, and vote count
			if (filter == "id" || filter == "ID" || filter == "Id") {
				//sort by descending order or ascending order
				if ((descending && movie_list[up].movieID < pivot) || (!descending && movie_list[up].movieID > pivot)) {
					break;
				}
				up++;
			}

			else if (filter == "budget" || filter == "Budget") {
				if ((descending && movie_list[up].movieBudget < pivot) || (!descending && movie_list[up].movieBudget > pivot)) {
					break;
				}
				up++;
			}

			else if (filter == "revenue" || filter == "Revenue") {
				if ((descending && movie_list[up].movieRevenue < pivot) || (!descending && movie_list[up].movieRevenue > pivot)) {
					break;
				}
				up++;
			}

			else if (filter == "runtime" || filter == "Runtime") {
				if ((descending && movie_list[up].movieRuntime < pivot) || (!descending && movie_list[up].movieRuntime > pivot)) {
					break;
				}
				up++;
			}

			else if (filter == "vote average" || filter == "Vote Average" || filter == "Vote average") {
				if ((descending && movie_list[up].voteAverage < pivot) || (!descending && movie_list[up].voteAverage > pivot)) {
					break;
				}
				up++;
			}

			else if (filter == "vote count" || filter == "Vote Count" || filter == "Vote count") {
				if ((descending && movie_list[up].voteCount < pivot) || (!descending && movie_list[up].voteCount > pivot)) {
					break;
				}
				up++;
			}

			else {
				if ((descending && movie_list[up].popularityScore < pivot) || (!descending && movie_list[up].popularityScore > pivot)) {
					break;
				}
				up++;
			}
		}

		//decrement until down less than pivot
		for (int i = high; i > low; i--) {
			if (filter == "id" || filter == "ID" || filter == "Id") {
				if ((descending && movie_list[down].movieID > pivot) || (!descending && movie_list[down].movieID < pivot)) {
					break;
				}
				down--;
			}

			else if (filter == "budget" || filter == "Budget") {
				if ((descending && movie_list[down].movieBudget > pivot) || (!descending && movie_list[down].movieBudget < pivot)) {
					break;
				}
				down--;
			}

			else if (filter == "revenue" || filter == "Revenue") {
				if ((descending && movie_list[down].movieRevenue > pivot) || (!descending && movie_list[down].movieRevenue < pivot)) {
					break;
				}
				down--;
			}

			else if (filter == "runtime" || filter == "Runtime") {
				if ((descending && movie_list[down].movieRuntime > pivot) || (!descending && movie_list[down].movieRuntime < pivot)) {
					break;
				}
				down--;
			}

			else if (filter == "vote average" || filter == "Vote Average" || filter == "Vote average") {
				if ((descending && movie_list[down].voteAverage > pivot) || (!descending && movie_list[down].voteAverage < pivot)) {
					break;
				}
				down--;
			}

			else if (filter == "vote count" || filter == "Vote Count" || filter == "Vote count") {
				if ((descending && movie_list[down].voteCount > pivot) || (!descending && movie_list[down].voteCount < pivot)) {
					break;
				}
				down--;
			}

			else {
				if ((descending && movie_list[down].popularityScore > pivot) || (!descending && movie_list[down].popularityScore < pivot)) {
					break;
				}
				down--;
			}
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
