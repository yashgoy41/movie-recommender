#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database) : m_udb(user_database), m_mdb(movie_database){
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    User* u = m_udb.get_user_from_email(user_email);
    // user not found, return empty vector
    if (u == nullptr){
        return {};
    }
    const vector<string>& watchHistory = u->get_watch_history();
    std::map<std::string,int> compatibility_scores;
    for(const string& movie_id : watchHistory){
        Movie* m = m_mdb.get_movie_from_id(movie_id);
        if (m) {
            // add 20 points for each director of the movie
            for (const std::string& director : m->get_directors()) {
                for (const Movie* candidate : m_mdb.get_movies_with_director(director)) {
                    if (candidate->get_id() != m->get_id()) {
                        compatibility_scores[candidate->get_id()] += 20;
                    }
                }
            }
            // add 30 points for each actor of the movie
            for (const std::string& actor : m->get_actors()) {
                for (const Movie* candidate : m_mdb.get_movies_with_actor(actor)) {
                    if (candidate->get_id() != m->get_id()) {
                        compatibility_scores[candidate->get_id()] += 30;
                    }
                }
            }
            // add 1 point for each genre of the movie
            for (const std::string& genre : m->get_genres()){
                for (const Movie* candidate : m_mdb.get_movies_with_genre(genre)){
                    if (candidate->get_id() != m->get_id()) {
                        compatibility_scores[candidate->get_id()] += 1;
                    }
                }
            }
        }
    }
    std::vector<std::pair<std::string,int>> compatible_movies;
    for (const auto& p : compatibility_scores) {
        if (std::find(watchHistory.begin(), watchHistory.end(), p.first) == watchHistory.end()) {
          compatible_movies.emplace_back(p);
        }
    }
    std::sort(compatible_movies.begin(), compatible_movies.end(), [this](const auto& a, const auto& b) {
        return (a.second > b.second) ||
                            ((a.second == b.second) &&
                             ((m_mdb.get_movie_from_id(a.first)->get_rating() > m_mdb.get_movie_from_id(b.first)->get_rating()) ||
                              ((m_mdb.get_movie_from_id(a.first)->get_rating() == m_mdb.get_movie_from_id(b.first)->get_rating()) && (m_mdb.get_movie_from_id(a.first)->get_title() < m_mdb.get_movie_from_id(b.first)->get_title()))));
    });
    std::vector<MovieAndRank> ranked_movies;
    for (const auto& p : compatible_movies) {
        const Movie* m = m_mdb.get_movie_from_id(p.first);
        if (m) {
          MovieAndRank movie_rank(m->get_id(), p.second);
          ranked_movies.push_back(movie_rank);
        }
    }
    if(movie_count <= 0){
        return {};
    }
    // get the top N movies
    std::vector<MovieAndRank> topNMovies;
    std::vector<MovieAndRank>::iterator it = ranked_movies.begin();
    while (movie_count > 0 && it != ranked_movies.end()) {
        topNMovies.push_back(*it);
        it++;
        movie_count--;
    }
    return topNMovies;
}
