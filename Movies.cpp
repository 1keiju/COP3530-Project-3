#include "Movies.h"

Movies::Movies() {
	numMovies = 0;
	populateMovieList();
}

void Movies::populateMovieList() {

	std::fstream file("movies.csv");

	std::string row;
	
	while (std::getline(file, row)) {
		// movie variables
		std::string name;
		std::string genres;
		std::string overview;

		std::getline(file, row);

		// .csv string variables
		std::istringstream stream(row);
		std::string token;

		/* FYI, things need to be read sequentially to properly assign variables
		   The getline below moves the counter forward so movie name can be read*/

		std::getline(stream, token, ','); // reads ID

		std::getline(stream, token, ','); // reads name
		name = token;

		std::getline(stream, token, ','); // reads genres
		genres = token;

		std::getline(stream, token, ','); // reads language

		std::getline(stream, token, ','); // reads overview
		overview = token;
		
		// std::getline(stream, token, ','); // reads popularity score [DOUBLE]
		// std::getline(stream, token, ','); // reads production studio
		// std::getline(stream, token, ','); // reads release date
		// std::getline(stream, token, ','); // reads budget [DOUBLE]
		// std::getline(stream, token, ','); // reads revenue [DOUBLE]
		// std::getline(stream, token, ','); // reads runtime [INT]
		// std::getline(stream, token, ','); // reads status [BOOL]
		// std::getline(stream, token, ','); // reads tagline
		// std::getline(stream, token, ','); // reads vote average [DOUBLE]
		// std::getline(stream, token, ','); // reads vote count [DOUBLE]
		// std::getline(stream, token, ','); // reads credits
		// std::getline(stream, token, ','); // reads keywords
		// std::getline(stream, token, ','); // reads poster
		// std::getline(stream, token, ','); // reads background
		// std::getline(stream, token, ','); // reads recommendations

		movies.push_back(Movie(name, genres, overview));
		numMovies++;
	}
}

void Movies::printMovies() {
	for (int i = 0; i < 100; i++) { // currently set at 100 for hard-coded testing
		std::cout << movies[i].movieName << " | " << movies[i].genresSTR << " | " << movies[i].movieOverview << "\n\n";
	}
}