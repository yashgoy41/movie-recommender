#include "Movie.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

Movie::Movie(const string& id, const string& title,
             const string& release_year, const string& directors,
             const string& actors, const string& genres, float rating)
{
    m_id = id;
    m_name = title;
    m_year = release_year;
    m_rating = rating;
    getNames(m_dirs, directors);
    getNames(m_actors, actors);
    getNames(m_genres, genres);
    
}

string Movie::get_id() const
{
    return m_id;
}

string Movie::get_title() const
{
    return m_name;
}

string Movie::get_release_year() const
{
    return m_year;
}

float Movie::get_rating() const
{
    return m_rating;
}

vector<string> Movie::get_directors() const
{
    return m_dirs;
}

vector<string> Movie::get_actors() const
{
    return m_actors;
}

vector<string> Movie::get_genres() const
{
    return m_genres;
}

void Movie::getNames(std::vector<std::string> &vec, std::string names){
    std::string name;
    std::stringstream ss(names);
    while (getline(ss, name, ',')) {
        vec.push_back(name);
    }
}
