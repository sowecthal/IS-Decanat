#ifndef USER_H
#define USER_H

#include <QString>

class User
{
private:
    QString mLogin;
    QString mPassword;
    int mRole;

public:
    User(QString uLogin, QString uPassword, int uRole);
};

#endif // USER_H
