#include <QtTest/QtTest>
#include <QString>
#include "../IS-Decanat/databases.h"
#include "../IS-Decanat/dataclasses/user.h"
#include "../IS-Decanat/dataclasses/group.h"
#include "../IS-Decanat/dataclasses/grade.h"
#include "../IS-Decanat/dataclasses/discipline.h"

Q_DECLARE_METATYPE(DataBases);
Q_DECLARE_METATYPE(User);
Q_DECLARE_METATYPE(Group);
Q_DECLARE_METATYPE(Discipline);
Q_DECLARE_METATYPE(Grade);

class tst : public QObject
{
    Q_OBJECT
private slots:
    // Тестирование User:
    void getLogin();
    void getPassword();
    void getRole();
    void editUser();
    // Тестирование DateBases
    void findAuthUser();
    void findStudent();
    void findGroup();
    void findGroupName();
};

void tst::getLogin()
{
    QString tstLogin = "login";
    User tstUser(tstLogin, "Password", User::roles::ADMIN);
    QVERIFY(tstUser.getLogin() == tstLogin);
}

void tst::getPassword()
{
    QString tstPassword = "Password";
    User tstUser("login", tstPassword, User::roles::ADMIN);
    QVERIFY(tstUser.getPassword() == tstPassword);
}

void tst::getRole()
{
    User::roles tstRole = User::roles::ADMIN;
    User tstUserAdmin("admin", "admin", tstRole);
    QCOMPARE(tstUserAdmin.getRole(), tstRole);

    tstRole = User::roles::SUPERVISOR;
    User tstUserSupervisor("supervisor", "supervisor", tstRole);
    QCOMPARE(tstUserSupervisor.getRole(), tstRole);

    tstRole = User::roles::STUDENT;
    User tstUserStudent("student", "student", tstRole);
    QCOMPARE(tstUserStudent.getRole(), tstRole);

    tstRole = User::roles::UNKNOWN;
    User tstUserWho("student", "student", tstRole);
    QCOMPARE(tstUserWho.getRole(), tstRole);

    QVERIFY(tstUserAdmin.getRole() != tstRole);
    QVERIFY(tstUserSupervisor.getRole() != tstRole);
    QVERIFY(tstUserStudent.getRole() != tstRole);
}

void tst::editUser()
{
    User tstUser("admin", "admin", User::roles::ADMIN);
    QString tstLogin = "student";
    QString tstPassword = "student";
    User::roles tstRole = User::roles::STUDENT;

    tstUser.editUser(tstLogin, tstPassword, tstRole);

    QVERIFY(tstUser.mSurname == tstLogin);
    // Подробнее об этом dataclasses/user.cpp line: 49
}

void tst::findAuthUser()
{
    DataBases tstDataBases;

    QString tstLogin = "admin";
    QString tstPassword = "admin";
    User::roles tstRole = User::roles::ADMIN;

    User tstUser(tstLogin, tstPassword, tstRole);

    User *received = tstDataBases.findAuthUser(tstLogin, tstPassword);
    QVERIFY(received->getRole() == User::roles::UNKNOWN);

    tstDataBases.usersList.append(tstUser);
    received = tstDataBases.findAuthUser(tstLogin, tstPassword);
    QVERIFY(received->getRole() == tstRole);
}

void tst::findStudent()
{
    DataBases tstDataBases;

    int tstSID = 1234;

    User tstStudent("student", "student", User::roles::STUDENT, tstSID, 0, "", "", "", User::grants::REGULAR);

    User *received = tstDataBases.findStudent(tstSID);
    QVERIFY(received->getRole() == User::roles::UNKNOWN);

    tstDataBases.usersList.append(tstStudent);
    received = tstDataBases.findStudent(tstSID);
    QVERIFY(received->mID == tstSID);
}

void tst::findGroup()
{
    DataBases tstDataBases;

    int tstGID = 1234;

    Group tstGroup(tstGID, "", {}, {});

    Group *received = tstDataBases.findGroup(tstGID);
    QVERIFY(received->mGroupID == 0);

    tstDataBases.groupsList.append(tstGroup);
    received = tstDataBases.findGroup(tstGID);
    QVERIFY(received->mGroupID == tstGID);
}

void tst::findGroupName()
{
    DataBases tstDataBases;

    QString tstName = "ОППО";

    Group tstGroup(1234, tstName, {}, {});

    Group *received = tstDataBases.findGroupName(tstName);
    QVERIFY(received->mGroupID == 0);

    tstDataBases.groupsList.append(tstGroup);
    received = tstDataBases.findGroupName(tstName);
    QVERIFY(received->mNumber == tstName);
}

QTEST_MAIN(tst)
#include "tst_1.moc"
