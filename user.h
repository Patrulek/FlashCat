#ifndef USER_H
#define USER_H

#include <QString>
#include "tallies.h"

class User
{
public:
    User();

    int id;
    QString token;
    Tallies tallies;
};

#endif // USER_H
