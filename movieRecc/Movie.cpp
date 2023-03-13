#include "Movie.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Movie::Movie(const std::string& id, const std::string& title,
             const std::string& release_year,
             const std::vector<std::string>& directors,
             const std::vector<std::string>& actors,
             const std::vector<std::string>& genres, float rating)
{
    m_id = id;
    m_name = title;
    m_year = release_year;
    m_rating = rating;
    m_dirs = directors;
    m_actors = actors;
    m_genres = genres;
    
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

