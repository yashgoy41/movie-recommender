#include "MovieDatabase.h"
#include "Movie.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

MovieDatabase::MovieDatabase(){}

bool MovieDatabase::load(const std::string& filename) {
    bool loadedMovies = loadMovies(filename);
    bool loadedIDMap = loadIdMap();
    bool loadedDirMap = loadDirMap();
    bool loadedActMap = loadActMap();
    bool loadedGenMap = loadGenMap();
    return (loadedIDMap && loadedMovies &&loadedDirMap && loadedActMap && loadedGenMap);
}
Movie* MovieDatabase::get_movie_from_id(const string& id) const {
    string lowercase_id = id;
    std::transform(lowercase_id.begin(), lowercase_id.end(), lowercase_id.begin(), ::tolower);
    TreeMultimap<std::string, Movie*>::Iterator it = m_idMap.find(lowercase_id);
    if(it.is_valid()){
        return it.get_value();
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const {
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

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const {
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

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const {
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

bool MovieDatabase::loadGenMap(){
    if(m_movies.empty()){
        return false;
    }
    std::vector<Movie>::iterator it = m_movies.begin();
    while(it != m_movies.end()){
        std::string genName;
        std::vector<std::string> genres = (*it).get_genres();
        for(auto gen : genres){
            std::string lowercase_genre= gen;
            std::transform(lowercase_genre.begin(), lowercase_genre.end(), lowercase_genre.begin(), ::tolower);
            m_dirMap.insert(lowercase_genre, &(*it));
        }
        it++;
    }
    return true;
}

bool MovieDatabase::loadActMap(){
    if(m_movies.empty()){
        return false;
    }
    std::vector<Movie>::iterator it = m_movies.begin();
    while(it != m_movies.end()){
        std::string actName;
        std::vector<std::string> actors = (*it).get_actors();
        for(auto act : actors){
            std::string lowercase_actor= act;
            std::transform(lowercase_actor.begin(), lowercase_actor.end(), lowercase_actor.begin(), ::tolower);
            m_dirMap.insert(lowercase_actor, &(*it));
        }
        it++;
    }
    return true;
}

bool MovieDatabase::loadDirMap(){
    if(m_movies.empty()){
        return false;
    }
    std::vector<Movie>::iterator it = m_movies.begin();
    while(it != m_movies.end()){
        std::string dirName;
        std::vector<std::string> directors = (*it).get_directors();
        for(auto dir : directors){
            std::string lowercase_director = dir;
            std::transform(lowercase_director.begin(), lowercase_director.end(), lowercase_director.begin(), ::tolower);
            m_dirMap.insert(lowercase_director, &(*it));
        }
        it++;
    }
    return true;
}

bool MovieDatabase::loadIdMap() {
    if(m_movies.empty()){
        return false;
    }
    std::vector<Movie>::iterator it = m_movies.begin();
    while(it != m_movies.end()){
        std::string lowercase_id = (*it).get_id();
        std::transform(lowercase_id.begin(), lowercase_id.end(), lowercase_id.begin(), ::tolower);
        m_idMap.insert(lowercase_id, &(*it));
        it++;
    }
    return true;
}

bool MovieDatabase::loadMovies(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::string movie_id = line;      // Line 1
        std::getline(file, line);
        std::string name = line;    // Line 2
        std::getline(file, line);
        std::string year = line;    // Line 3
        std::getline(file, line);
        std::string directors = line;  // Line 4
        std::getline(file, line);
        std::string actors = line; // Line 5
        std::getline(file, line);
        std::string genres = line; // Line 6
        std::getline(file, line);
        float rating = std::stof(line); // Line 7
        
        std::vector<std::string> directorList;
        std::vector<std::string> actorList;
        std::vector<std::string> genreList;
        
        getNames(directorList, directors);
        getNames(actorList, actors);
        getNames(genreList, genres);
        // Populate movie array
        m_movies.push_back(Movie(movie_id, name, year, directorList, actorList, genreList, rating));
        
        // Skip the blank line between movie records
        std::getline(file, line);
    }
    return true;
}

void MovieDatabase::getNames(std::vector<std::string> &vec, std::string names){
    std::string name;
    std::stringstream ss(names);
    while (getline(ss, name, ',')) {
        vec.push_back(name);
    }
}
