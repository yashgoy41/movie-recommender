#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "treemm.h"
#include <iostream>
#include <string>
#include <cassert>
#include "Recommender.h"
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/yash/Desktop/CS32/movieRecc/movieRecc/users.txt";
const string MOVIE_DATAFILE = "/Users/yash/Desktop/CS32/movieRecc/movieRecc/movies.txt";

//int main()
//{
//	UserDatabase udb;
//	if (0&&!udb.load(USER_DATAFILE))  // In skeleton, load always return false
//	{
//		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
//		return 1;
//	}
//	for (;;)
//	{
//		cout << "Enter user email address (or quit): ";
//		string email;
//		getline(cin, email);
//		if (email == "quit")
//			return 0;
//		User* u = udb.get_user_from_email(email);
//		if (u == nullptr)
//			cout << "No user in the database has that email address." << endl;
//		else
//			cout << "Found " << u->get_full_name() << endl;
//	}
void findMatches(const Recommender& r,const MovieDatabase& md, const string& user_email, int num_recommendations) {
 // get up to ten movie recommendations for the user
    vector<MovieAndRank> recommendations =
    r.recommend_movies(user_email, num_recommendations);
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i+1 << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n";
        }
    }
}

int main()
{
//    TreeMultimap<std::string, std::string> myMap;
//    myMap.insert("Inception", "Christoper Nolan");
//    myMap.insert("Inception", "Leonardo DiCaprio");
//    myMap.insert("Inception", "Ellen Page");
//    myMap.insert("Irreversible", "Monica Bellucci");
//    TreeMultimap<std::string, std::string>::Iterator it =  myMap.find("Inception");
//
//    assert(it.get_value() == "Christoper Nolan");
//    it.advance();
//    assert(it.get_value() == "Leonardo DiCaprio");
//    it.advance();
//    assert(it.get_value() == "Ellen Page");
    
    UserDatabase udb;
    udb.load(USER_DATAFILE);
//    cerr << "Passed all tests" << endl;
//    for (;;)
//    {
//        cout << "Enter user email address (or quit): ";
//        string email;
//        getline(cin, email);
//        if (email == "quit")
//            return 0;
//        User* u = udb.get_user_from_email(email);
//        if (u == nullptr)
//            cout << "No user in the database has that email address." << endl;
//        else{
//            cout << "Found " << u->get_full_name() << endl;
//            vector<string> watchhist = u->get_watch_history();
//            vector<string>::iterator it = watchhist.begin();
//            while(it != watchhist.end()){
//                cout << *it << " ";
//                it++;
//            }
//        }
//    }
//
    MovieDatabase mdb;
    mdb.load(MOVIE_DATAFILE);
    Recommender r(udb, mdb);
    for (;;)
    {
        cout << "Enter email (or quit): ";
        string id;
        getline(cin, id);
        if (id == "quit")
            return 0;
        findMatches(r, mdb, id, 20);
//        cout << "Enter movie id (or quit): ";
//        string id;
//        getline(cin, id);
//        if (id == "quit")
//            return 0;
//        Movie* m = mdb.get_movie_from_id(id);
//        if (m == nullptr)
//            cout << "No movie in the database has that id." << endl;
//        else{
//            cout << "Found " << m->get_title() << endl;
//            cout << m->get_id() << endl;
//            cout << m->get_rating() << endl;
//            cout << m->get_release_year() << endl;
//
//            vector<string> directorList = m->get_directors();
//            vector<string>::iterator it2 = directorList.begin();
//            while(it2 != directorList.end()){
//                cout << *it2 << ", ";
//                it2++;
//            }
//            cout << endl;
//
//            vector<string> actorList = m->get_actors();
//            vector<string>::iterator it = actorList.begin();
//            while(it != actorList.end()){
//                cout << *it << ", ";
//                it++;
//            }
//            cout << endl;
//
//            vector<string> genList = m->get_genres();
//            vector<string>::iterator it3 = genList.begin();
//            while(it3 != genList.end()){
//                cout << *it3 << ", ";
//                it3++;
//            }
//            cout << endl;
//        }
//        cout << "Enter email (or quit): ";
//        string id;
//        getline(cin, id);
//        if (id == "quit")
//            return 0;
//        vector<Movie*> movies = mdb.get_movies_with_genre(id);
//        if (movies.empty())
//            cout << "No movie in the database has that id." << endl;
//        else{
//
//            cout << "Found movies with the genre " << id << endl;
//            vector<Movie*>::iterator it = movies.begin();
//            while(it != movies.end()){
//                cout << (*it)->get_title() << endl;
//                it++;
//            }
//        }
    
    }
}
    
    
    

    
