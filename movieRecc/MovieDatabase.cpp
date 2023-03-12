#include "MovieDatabase.h"
#include "Movie.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

bool MovieDatabase::load(const std::string& filename) {
    bool loadedMovies = loadMovies(filename);
    bool loadedIDMap = loadIdMap(filename);
    bool loadedDirMap = loadDirMap(filename);
    bool loadedActMap = loadActMap(filename);
    bool loadedGenMap = loadGenMap(filename);
    return (loadedIDMap && loadedMovies &&loadedDirMap && loadedActMap && loadedGenMap);
}
Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string lowercase_id = id;
    std::transform(lowercase_id.begin(), lowercase_id.end(), lowercase_id.begin(), ::tolower);
    TreeMultimap<std::string, Movie*>::Iterator it = m_idMap.find(lowercase_id);
    if(it.is_valid()){
        return it.get_value();
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string lowercase_director = director;
    std::transform(lowercase_director.begin(), lowercase_director.end(), lowercase_director.begin(), ::tolower);
    vector<Movie*> movies;
        TreeMultimap<std::string, Movie*>::Iterator it = m_dirMap.find(lowercase_director);
        while (it.is_valid()) {
            movies.push_back(it.get_value());
            it.advance();
        }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string lowercase_actor = actor;
    std::transform(lowercase_actor.begin(), lowercase_actor.end(), lowercase_actor.begin(), ::tolower);
    vector<Movie*> movies;
        TreeMultimap<std::string, Movie*>::Iterator it = m_dirMap.find(lowercase_actor);
        while (it.is_valid()) {
            movies.push_back(it.get_value());
            it.advance();
        }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string lowercase_genre = genre;
    std::transform(lowercase_genre.begin(), lowercase_genre.end(), lowercase_genre.begin(), ::tolower);
    vector<Movie*> movies;
    TreeMultimap<std::string, Movie*>::Iterator it = m_dirMap.find(lowercase_genre);
    while (it.is_valid()) {
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}
