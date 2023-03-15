#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;


Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database) : m_udb(user_database), m_mdb(movie_database){
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if(movie_count <= 0){
        return {};
    }
    User* u = m_udb.get_user_from_email(user_email);
    // user not found, return empty vector
    if (u == nullptr){
        return {};
    }
    std::unordered_map<std::string, int> directorHistMap;
    std::unordered_map<std::string, int> actorHistMap;
    std::unordered_map<std::string, int> genreHistMap;
    std::unordered_map<std::string, bool> movieHistMap;
    std::unordered_map<std::string,int> compatibility_scores;
    
    const vector<string>& watchHistory = u->get_watch_history();
    for(const string& movie_id : watchHistory){
        Movie* m = m_mdb.get_movie_from_id(movie_id);
        if (m) {
            movieHistMap[m->get_id()] = true; // Add to movie history map
            // add 20 points for each director of the movie
            for (const std::string& director : m->get_directors()) {
                directorHistMap[director] += 1; // Add director to director history map
            }
            // add 30 points for each actor of the movie
            for (const std::string& actor : m->get_actors()) {
                actorHistMap[actor] += 1; // Add director to actor history map
            }
            // add 1 point for each genre of the movie
            for (const std::string& genre : m->get_genres()){
                genreHistMap[genre] += 1; // Add director to actor history map
            }
        }
    }
    for (const auto& kv : directorHistMap) {
        for (const Movie* candidate : m_mdb.get_movies_with_director(kv.first)) {
            if (movieHistMap.find(candidate->get_id()) != movieHistMap.end()){
                continue; // Movie exists in watch history
            }
            else{
                compatibility_scores[candidate->get_id()] += directorHistMap[kv.first]*20;
            }
        }
    }
    for (const auto& kv : actorHistMap) {
        for (const Movie* candidate : m_mdb.get_movies_with_actor(kv.first)) {
            if (movieHistMap.find(candidate->get_id()) != movieHistMap.end()){
                continue; // Movie exists in watch history
            }
            else{
                compatibility_scores[candidate->get_id()] += actorHistMap[kv.first]*30;
            }
        }
    }
    for (const auto& kv : genreHistMap) {
        for (const Movie* candidate : m_mdb.get_movies_with_genre(kv.first)) {
            if (movieHistMap.find(candidate->get_id()) != movieHistMap.end()){
                continue; // Movie exists in watch history
            }
            else{
                compatibility_scores[candidate->get_id()] += genreHistMap[kv.first]*1;
            }
        }
    }
    std::vector<std::pair<std::string,int>> compatible_movies;
    for (const auto& p : compatibility_scores) {
        if (std::find(watchHistory.begin(), watchHistory.end(), p.first) == watchHistory.end()) {
          compatible_movies.emplace_back(p);
        }
    }

    std::unordered_map<std::string, const Movie*> cached_movies;
    for (const auto& p : compatibility_scores) {
        const Movie* m = m_mdb.get_movie_from_id(p.first);
        if (m) {
            cached_movies.emplace(p.first, m);
        }
    }

    std::sort(compatible_movies.begin(), compatible_movies.end(), [&cached_movies](const auto& a, const auto& b) {
        const Movie* m1 = cached_movies.at(a.first);
        const Movie* m2 = cached_movies.at(b.first);

        return (a.second > b.second) ||
               ((a.second == b.second) &&
                ((m1->get_rating() > m2->get_rating()) ||
                 ((m1->get_rating() == m2->get_rating()) && (m1->get_title() < m2->get_title()))));
    });

    std::vector<MovieAndRank> ranked_movies;
    for (const auto& p : compatible_movies) {
        const Movie* m = m_mdb.get_movie_from_id(p.first);
        if (m) {
          MovieAndRank movie_rank(m->get_id(), p.second);
          ranked_movies.push_back(movie_rank);
        }
    }
 
    std::vector<MovieAndRank> topNMovies;
    std::vector<MovieAndRank>::iterator it = ranked_movies.begin();
    while (movie_count > 0 && it != ranked_movies.end()) {
        topNMovies.emplace_back(*it);
        it++;
        movie_count--;
    }
    return topNMovies;
}
