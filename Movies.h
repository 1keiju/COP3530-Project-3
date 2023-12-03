#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#pragma once

struct Movie {
	int movieID;
	std::string movieName;
	std::string genresSTR; //
	std::vector<std::string> genreList;
	std::string movieLanguage;
	std::string movieOverview;
	double popularityScore;
	std::string productionStudio;
	std::string releaseDate;
	double movieBudget;
	double movieRevenue;
	int movieRuntime;
	bool movieReleased;
	std::string movieTagline;
	double voteAverage;
	double voteCount;
	std::string creditsSTR;
	std::vector<std::string> movieCredits; //
	std::string movieKeywords;
	std::string posterImageURL;
	std::string bannerImageURL;
	std::string recommendationSTR; //
	std::vector<std::string> movieRecommendations;

	Movie();
	Movie(std::string name, double score, double revenue, double budget, int runtime, double average) {

		// full list of parameters
		/*int id, std::string name, std::string genres, std::string lang, std::string overview, double score, std::string studio, std::string date, double budget, double revenue, int runtime,
	bool released, std::string tagline, double average, double count, std::string keywords, std::string poster, std::string banner*/

		movieName = name;
		popularityScore = score;
        movieRevenue = revenue;
        movieBudget = budget;
        movieRuntime = runtime;
        voteAverage = average;
		
		/* 
		   The following variables were omitted for testing
		   Make a decision about what data points we want to display
		   The image URLs could work if we find a way to pull the image from the web to display
		*/
		// movieID = id;
		// movieLanguage = lang;
		// popularityScore = score;
		/*productionStudio = studio;
		releaseDate = date;
		movieBudget = budget;
		movieRevenue = revenue;
		movieRuntime = runtime;
		movieReleased = released;
		movieTagline = tagline;
		voteAverage = average;
		voteCount = count;
		movieKeywords = keywords;
		posterImageURL = "https://image.tmdb.org/t/p/w1280" + poster;
		bannerImageURL = "https://image.tmdb.org/t/p/w1280" + banner;*/
	}
};


class Movies {
private:
	std::vector<Movie> movies;
	int numMovies;
public:
	Movies(); // constructor, grabs data from opened file and uses populateMovieList()
	void populateMovieList(); // reads .csv file
	void printMovies();
};