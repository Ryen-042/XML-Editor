#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
using namespace std;

class User
{
public:
    //  attributes
    string name;
    int id;
    vector<int> followers;

    // methods
    User()
        : name("NULL"), id(0)
    {
    }
    void addFollower(int follower)
    {
        followers.push_back(follower);
    }
    ~User()
    {
    }
};

#endif // USER_HPP
