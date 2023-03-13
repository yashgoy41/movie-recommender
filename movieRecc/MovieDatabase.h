#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include "Movie.h"
#include "treemm.h"
#include <string>
#include <vector>


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
    bool loadMovies(const std::string& filename);
    bool loadIdMap();
    bool loadDirMap();
    bool loadActMap();
    bool loadGenMap();
    void getNames(std::vector<std::string> &vec, std::string names);
};

#endif // MOVIEDATABASE_INCLUDED
