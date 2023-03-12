#ifndef MOVIE_INCLUDED
#define MOVIE_INCLUDED

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class Movie
{
  public:
    Movie(const std::string& id, const std::string& title,
          const std::string& release_year, const std::string& directors,
          const std::string& actors, const std::string& genres, float rating);
    std::string get_id() const;
    std::string get_title() const;
    std::string get_release_year() const;
    float get_rating() const;
    std::vector<std::string> get_directors() const;
    std::vector<std::string> get_actors() const;
    std::vector<std::string> get_genres() const;

  private:
    std::string m_id;
    std::string m_name;
    std::string m_year;
    std::vector<std::string> m_dirs;
    std::vector<std::string> m_actors;
    std::vector<std::string> m_genres;
    void getNames(std::vector<std::string> &vec, std::string names){
        std::string name;
        std::stringstream ss(names);
        while (getline(ss, name, ',')) {
            vec.push_back(name);
        }
    }
    float m_rating;

    
};

#endif // MOVIE_INCLUDED
