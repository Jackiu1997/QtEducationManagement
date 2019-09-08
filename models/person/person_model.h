#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using std::string;

class Person {
public:
    string getName() { return name; }
    long getID() { return ID; }
    string getPassword() { return password; }

    bool setName(string na) {
        if (na.length() > 100 || na.length() < 1)
            return false;
        else
            this->name = na;
        return true;
    }
    bool setID(long id) {
        if (id < 0)
            return false;
        else
            this->ID = id;
        return true;
    }
    bool setPassword(string pwd) {
        if (pwd.length() > 16 || pwd.length() < 6)
            return false;
        else
            this->password = pwd;
        return true;
    }

protected:
    string name;
    long ID;
    string password;
};

#endif
