#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "Movie.h"
#include "treemm.h"
#include <fstream>
#include <iostream>
#include <sstream>

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    std::vector<Movie> m_movies;
    TreeMultimap<std::string, Movie*> m_idMap;
    TreeMultimap<std::string, Movie*> m_dirMap;
    TreeMultimap<std::string, Movie*> m_actMap;
    TreeMultimap<std::string, Movie*> m_genMap;
    bool loadMovies(const std::string& filename){
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
            
            // Populate movie array
            m_movies.push_back(Movie(movie_id, name, year, directors, actors, genres, rating));
            
            // Skip the blank line between movie records
            std::getline(file, line);
        }
        return true;
    }
    bool loadIdMap(const std::string& filename) {
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

    bool loadDirMap(const std::string& filename){
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
    bool loadActMap(const std::string& filename){
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
    bool loadGenMap(const std::string& filename){
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
};

#endif // MOVIEDATABASE_INCLUDED
