#include "Movies.h"
using namespace std;

Movies::Movies() {
    movies = new Movie[110001];
	numMovies = 0;
	populateMovieList();
}

void Movies::populateMovieList() {

	fstream file("./movies.csv");

	string row;
    int index = 0;

	while (getline(file, row)) {

        // check if out of index
        if(index > 110000) {
            break;
        }

		// movie variables
		string name;
		double score;
		double budget;
		double revenue;
		double runtime;
		double average;

		getline(file, row);

		// .csv string variables
		istringstream stream(row);
		string token;

		/* FYI, things need to be read sequentially to properly assign variables
		   The getline below moves the counter forward so movie name can be read*/

		getline(stream, token, ','); // reads ID

		getline(stream, token, ','); // reads name

		name = token;

		getline(stream, token, ','); // reads genres

		getline(stream, token, ','); // reads language

		getline(stream, token, ','); // reads overview

		getline(stream, token, ','); // reads popularity score [DOUBLE]
		if (token == "") token = "0";

		score = stod(token);

		getline(stream, token, ','); // reads production studio

		getline(stream, token, ','); // reads release date

		getline(stream, token, ','); // reads budget [DOUBLE]
		if (token == "") token = "0";

		budget = stod(token);

		getline(stream, token, ','); // reads revenue [DOUBLE]
		if (token == "") token = "0";

		revenue = stod(token);

		getline(stream, token, ','); // reads runtime [INT]
		if (token == "") token = "0";

		runtime = stod(token);

		getline(stream, token, ','); // reads status [BOOL]

		getline(stream, token, ','); // reads tagline

		getline(stream, token, ','); // reads vote average [DOUBLE]
		if (token == "") token = "0";

		average = stod(token);

        // add new element to the array
		Movie newMovie = Movie(name, score, revenue, budget, runtime, average);
        movies[index] = newMovie;

        // add new element to vector
        moviesVector.push_back(Movie(name, score, revenue, budget, runtime, average));

		numMovies++;
        index++;

	}
}

Movie::Movie() {

}
