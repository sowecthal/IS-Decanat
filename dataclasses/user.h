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

    void setRole(int sRole);
    int getRole();
    QString getLogin();
    QString getPassword();
};

#endif // USER_H
