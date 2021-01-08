#include "user.h"
#include <QDebug>

User::User(QString uLogin, QString uPassword, roles uRole)
{
    mLogin = uLogin;
    mPassword = uPassword;
    mRole = uRole;
}

User::User(QString uLogin, QString uPassword, roles uRole, int sID, int sGroupID, QString sSurname, QString sName, QString sPatronymic, int sGrant, QList<int> sGrades)
{
    mLogin = uLogin;
    mPassword = uPassword;
    mRole = uRole;
    if (uRole == roles::STUDENT) {
        mID = sID;
        mGroupID = sGroupID;
        mSurname = sSurname;
        mName = sName;
        mPatronymic = sPatronymic;
        mGrant = sGrant;
        mGrades = sGrades;
    }
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

void User::editUser(QString eLogin, QString ePassword, roles eRole)
{
    mLogin = eLogin;
    mPassword = ePassword;

    if (mRole != eRole) {
        /* При изменении роли на "Студент"(равно создании пользователя с этой ролью) - Логин помещается в поле с фамилией,
         * предполагается, для того, чтобы сотрудник деканата смог определить(вероятно по каким-то своим таблицам),
         * что администратором был создан пользователь, являющийся студентом, к примеру, Ивановым (Ivanov1234).
         */
        mSurname = eLogin;
        mID = 0;
        mGroupID = -1;
        mName = "";
        mPatronymic = "";
        mGrant = 0;
        mGrades = {};
    }

    mRole = eRole;
}
