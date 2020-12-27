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

void User::editUser(QString eLogin, QString ePassword, int eRole)
{
    mLogin = eLogin;
    mPassword = ePassword;
    if (mRole != eRole)
    {
        // Для удобства распознавания студентов, при изменении роли на "студент", логин помещается в строку с фамилией.
        mSurname = eLogin;
        mID = -1;
        mGroupID = -1;
        mName = "";
        mPatronymic = "";
        mGrant = 0;
        mGrades = {};
    }
    mRole = eRole;
}
