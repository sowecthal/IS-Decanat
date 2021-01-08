#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>

class User
{
public:
    //! Конструктор по умолчанию
    User() {}

    //! Возможные роли.
    enum roles {UNKNOWN, ADMIN, SUPERVISOR, STUDENT};

    //! Конструктор пользователя
    User(QString uLogin, QString uPassword, roles uRole);
    /* uLogin - логин;
     * uPassword - пароль;
     * uRole - роль.
     */

    //! Конструктор пользователя-студента
    User(QString uLogin, QString uPassword, roles uRole, int sID, int sGroupID, QString sSurname,
         QString sName, QString sPatronymic, int sGrant, QList<int> sGrades);
    /* sID - внутренний номер студента;
     * sGroupID - внутренний номер группы студента;
     * sName, sSurname, sPatronymic - ФИО;
     * sGrant - получаемая стипендия:
     *      0 - лишён;
     *      1 - обычная;
     *      2 - повышенная;
     * sGrades - список оценок.
     */

    //! Методы получения значений полей
    QString getLogin();
    QString getPassword();
    int getRole();

    //! Метод редактирования пользователя
    void editUser(QString eLogin, QString ePassword, roles eRole);

    //! Поля пользователя-студетна
    int mID;
    int mGroupID;
    QString mSurname;
    QString mName;
    QString mPatronymic;
    int mGrant;
    QList<int> mGrades;

private:
    QString mLogin;
    QString mPassword;
    roles mRole;

};

#endif // USER_H
