#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>

class User
{
private:
    QString mLogin;
    QString mPassword;
    int mRole;

public:
    //! Конструктор пользователя
    User(QString uLogin, QString uPassword, int uRole);
    /* uLogin - логин;
     * uPassword - пароль;
     * uRole - роль:
     *      0 - студент;
     *      1 - диспетчер деканата;
     *      2 - администратор ИС.
     */

    //! Конструктор пользователя-студента
    User(QString uLogin, QString uPassword, int uRole, int sID, int sGroupID, QString sSurname,
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
    void editUser(QString eLogin, QString ePassword, int eRole);

    //! Поля пользователя-студетна
    int mID;
    int mGroupID;
    QString mSurname;
    QString mName;
    QString mPatronymic;
    int mGrant;
    QList<int> mGrades;
};

#endif // USER_H
