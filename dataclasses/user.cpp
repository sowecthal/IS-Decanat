#include "user.h"

User::User(QString uLogin, QString uPassword, int uRole)
{
    mLogin = uLogin;
    mPassword = uPassword;
    mRole = uRole;
}

void User::setRole(int sRole)
{
    mRole = sRole;
}


QString User::getLogin()
{
    return(mLogin);
}

QString User::getPassword()
{
    return(mPassword);
}

int User::getRole()
{
    return(mRole);
}
