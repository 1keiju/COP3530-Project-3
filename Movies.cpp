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
		double score;
		double budget;
		double revenue;
		double runtime;
		double average;

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

		std::getline(stream, token, ','); // reads language

		std::getline(stream, token, ','); // reads overview

		std::getline(stream, token, ','); // reads popularity score [DOUBLE]
		if (token == "") token = "0";

		score = std::stod(token);

		std::getline(stream, token, ','); // reads production studio

		std::getline(stream, token, ','); // reads release date

		std::getline(stream, token, ','); // reads budget [DOUBLE]
		if (token == "") token = "0";

		budget = std::stod(token);

		std::getline(stream, token, ','); // reads revenue [DOUBLE]
		if (token == "") token = "0";

		revenue = std::stod(token);

		std::getline(stream, token, ','); // reads runtime [INT]
		if (token == "") token = "0";

		runtime = std::stod(token);

		std::getline(stream, token, ','); // reads status [BOOL]

		std::getline(stream, token, ','); // reads tagline

		std::getline(stream, token, ','); // reads vote average [DOUBLE]
		if (token == "") token = "0";

		average = std::stod(token);

		// std::getline(stream, token, ','); // reads vote count [DOUBLE]
		// std::getline(stream, token, ','); // reads credits
		// std::getline(stream, token, ','); // reads keywords
		// std::getline(stream, token, ','); // reads poster
		// std::getline(stream, token, ','); // reads background
		// std::getline(stream, token, ','); // reads recommendations

		movies.push_back(Movie(name, score, revenue, budget, runtime, average));
		numMovies++;
	}
}

void Movies::printMovies() {
	for (int i = 0; i < 10; i++) { // currently set at 100 for hard-coded testing
		std::cout << movies[i].movieName << " | " << movies[i].genresSTR << " | " << movies[i].movieOverview << "\n\n";
	}
}

std::string Movies::createTopTenList() {
	std::string returnString = "";
	for (int i = 0; i < 10; i++) { // currently set at 10 for printing top 10 movies
		std::string num = std::to_string(i + 1) + ".";

		returnString += num + " " + movies[i].movieName + "\n\n";

		//std::cout << (i + 1) << ". " << movies[i].movieName << "\n\n";
	}
	return returnString;
}