#ifndef MOTLEPLUSLONG_H
#define MOTLEPLUSLONG_H

#include <string>
#include <list>


using namespace std;




class Article {
public:
    Article(const string& mot) : mot(mot), pmot(mot) {
        sort(pmot.begin(), pmot.end());
    }

    string mot;
    string pmot;
};

#endif // MOTLEPLUSLONG_H




