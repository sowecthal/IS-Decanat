#include "user.h"
#include <QDebug>

User::User(QString uLogin, QString uPassword, int uRole)
{
    mLogin = uLogin;
    mPassword = uPassword;
    mRole = uRole;
}

User::User(QString uLogin, QString uPassword, int uRole, int sID, int sGroupID, QString sSurname, QString sName, QString sPatronymic, int sGrant, QList<int> sGrades)
{
    qDebug() << "[User::User] Сreate";
    mLogin = uLogin;
    mPassword = uPassword;
    mRole = uRole;
    mID = sID;
    mGroupID = sGroupID;
    mSurname = sSurname;
    mName = sName;
    mPatronymic = sPatronymic;
    mGrant = sGrant;
    mGrades = sGrades;
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
