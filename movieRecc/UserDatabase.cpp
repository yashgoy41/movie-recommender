#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Failed to load user data file " << filename << "!" << endl;
        return false;
    }

    string line;
    string name, email, movie_id;
    vector<string> watch_history;
    int count = 0;

    while (getline(infile, line)) {
        switch(count) {
            case 0:
                name = line;
                break;
            case 1:
                email = line;
                break;
            case 2:
                break;
            default:
                watch_history.push_back(line);
                break;
        }

        if (line.empty()) {
            m_users.insert(email, User(name, email, watch_history));
            watch_history.clear();
            count = 0;
        } else {
            count++;
        }
    }
    if (!watch_history.empty()) {
        m_users.insert(email, User(name, email, watch_history));
    }
    infile.close();
    return true;
}


User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User>::Iterator it = m_users.find(email);
    if(it.is_valid()){
        return &(it.get_value());
    }
    return nullptr;
}

