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
    //! Тестирование User:
    void checkGetLogin();
    void checkGetPassword();
    void checkGetRole();
    void checkEditUser();
    //! Тестирование Grade
    void checkGetStudentID();
    void checkGetDisciplineID();
    void checkGetValue();
    void checkBelongsDiscipline();
    void checkBelongsStudent();
    void checkItsMe();
    void checkFind();
    void checkReset();
    //! Тестирование DateBases
    void checkFindAuthUser();
    void checkFindStudent();
    void checkFindGroup();
    void checkFindGroupName();
    void checkNextId();
    void checkGradeWork();
    void checkReadAndWrite();
};

void tst::checkGetLogin()
{
    QString tstLogin = "login";
    User tstUser(tstLogin, "Password", User::roles::ADMIN);

    QVERIFY(tstUser.getLogin() == tstLogin);
}

void tst::checkGetPassword()
{
    QString tstPassword = "Password";
    User tstUser("login", tstPassword, User::roles::ADMIN);

    QVERIFY(tstUser.getPassword() == tstPassword);
}

void tst::checkGetRole()
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

void tst::checkGetStudentID()
{
    int tmpStudentID = 31945210;
    User *tstStudent = new User("Login", "Password", User::STUDENT, tmpStudentID, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", 1, Discipline::EXAM, {1906});
    Grade tmpGrade(*tstStudent, *tstDiscipline, Grade::EXCELLENT);

    QVERIFY(tmpGrade.getStudentID() == tmpStudentID);
}

void tst::checkGetDisciplineID()
{
    int tmpDisciplineID = 1;
    User *tstStudent = new User("Login", "Password", User::STUDENT, 31945210, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", tmpDisciplineID, Discipline::EXAM, {1906});
    Grade tmpGrade(*tstStudent, *tstDiscipline, Grade::EXCELLENT);

    QVERIFY(tmpGrade.getDisciplineID() == tmpDisciplineID);
}

void tst::checkGetValue()
{
    Grade::grades tmpValue = Grade::EXCELLENT;
    User *tstStudent = new User("Login", "Password", User::STUDENT, 31945210, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", 1, Discipline::EXAM, {1906});
    Grade tmpGrade(*tstStudent, *tstDiscipline, tmpValue);

    QVERIFY(tmpGrade.getValue() == tmpValue);
}

void tst::checkBelongsDiscipline()
{
    int tmpDisciplineID = 1;
    User *tstStudent = new User("Login", "Password", User::STUDENT, 31945210, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", tmpDisciplineID, Discipline::EXAM, {1906});
    Grade tmpGrade(*tstStudent, *tstDiscipline, Grade::EXCELLENT);

    QVERIFY(tmpGrade.belongsDiscipline(tmpDisciplineID));
}

void tst::checkBelongsStudent()
{
    int tmpStudentID = 31945210;
    User *tstStudent = new User("Login", "Password", User::STUDENT, tmpStudentID, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", 1, Discipline::EXAM, {1906});
    Grade tmpGrade(*tstStudent, *tstDiscipline, Grade::EXCELLENT);

    QVERIFY(tmpGrade.belongsStudent(tmpStudentID));
}

void tst::checkItsMe()
{
    int tmpStudentID = 31945210;
    int tmpDisciplineID = 1;

    User *tstStudent = new User("Login", "Password", User::STUDENT, tmpStudentID, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", tmpDisciplineID, Discipline::EXAM, {1906});
    Grade tmpGrade(*tstStudent, *tstDiscipline, Grade::EXCELLENT);

    QVERIFY(tmpGrade.itsMe(tmpStudentID, tmpDisciplineID));
    QVERIFY(!tmpGrade.itsMe(tmpDisciplineID, tmpStudentID));
}

void tst::checkFind()
{
    int tmpStudentID = 31945210;
    int tmpDisciplineID = 1;
    Grade::grades tmpValue = Grade::EXCELLENT;

    User *tstStudent = new User("Login", "Password", User::STUDENT, tmpStudentID, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", tmpDisciplineID, Discipline::EXAM, {1906});
    Grade tmpGrade(*tstStudent, *tstDiscipline, tmpValue);

    QVERIFY(tmpGrade.find(tmpStudentID, tmpDisciplineID) == tmpValue);
    QVERIFY(tmpGrade.find(tmpStudentID, tmpDisciplineID) != Grade::NONE);
    QVERIFY(tmpGrade.find(tmpStudentID, tmpDisciplineID) != Grade::BAD);
    QVERIFY(tmpGrade.find(tmpStudentID, tmpDisciplineID) != Grade::OKAY);
    QVERIFY(tmpGrade.find(tmpStudentID, tmpDisciplineID) != Grade::GOOD);
    QVERIFY(tmpGrade.find(tmpDisciplineID, tmpStudentID) == Grade::NONE);
}

void tst::checkReset()
{
    Grade::grades tmpValue_1 = Grade::GOOD;
    Grade::grades tmpValue_2 = Grade::EXCELLENT;
    Grade::grades tmpValue_3 = Grade::NOPASSED;

    User *tstStudent = new User("Login", "Password", User::STUDENT, 31945210, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline *tstDiscipline = new Discipline("ОППО", 1, Discipline::EXAM, {1906});
    Grade tstGrade(*tstStudent, *tstDiscipline, tmpValue_1);

    QVERIFY(tstGrade.getValue() == tmpValue_1);

    tstGrade.reset(tmpValue_2);
    QVERIFY(tstGrade.getValue() == tmpValue_2);

    tstGrade.reset(tmpValue_3);
    QVERIFY(tstGrade.getValue() == Grade::BAD);
    /* Была произведена попытка установка несоответствующего форме контроля оценки,
     * замена на подхлдящую.
     * Результат работы приватного для Grade метода getSuitable(Grade::grades)
     */
}

void tst::checkEditUser()
{
    User tstUser("admin", "admin", User::roles::ADMIN);
    QString tstLogin = "student";
    QString tstPassword = "student";
    User::roles tstRole = User::roles::STUDENT;

    tstUser.editUser(tstLogin, tstPassword, tstRole);

    QVERIFY(tstUser.mSurname == tstLogin);
    // Подробнее об этом dataclasses/user.cpp line: 49
}

void tst::checkFindAuthUser()
{
    DataBases tstDataBases;

    QString tstLogin = "admin";
    QString tstPassword = "admin";
    User::roles tstRole = User::roles::ADMIN;

    User tstUser(tstLogin, tstPassword, tstRole);

    User *received = tstDataBases.findAuthUser(tstLogin, tstPassword);
    QVERIFY(received == nullptr);

    tstDataBases.usersList.append(tstUser);
    received = tstDataBases.findAuthUser(tstLogin, tstPassword);
    QVERIFY(received->getRole() == tstRole);
}

void tst::checkFindStudent()
{
    DataBases tstDataBases;

    int tstSID = 1234;

    User tstStudent("student", "student", User::roles::STUDENT, tstSID, 0, "", "", "", User::grants::REGULAR);

    User *received = tstDataBases.findStudent(tstSID);
    QVERIFY(received == nullptr);

    tstDataBases.usersList.append(tstStudent);
    received = tstDataBases.findStudent(tstSID);
    QVERIFY(received->mID == tstSID);
}

void tst::checkFindGroup()
{
    DataBases tstDataBases;

    int tstGID = 1234;

    Group tstGroup(tstGID, "", {}, {});

    Group *received = tstDataBases.findGroup(tstGID);
    QVERIFY(received == nullptr);

    tstDataBases.groupsList.append(tstGroup);
    received = tstDataBases.findGroup(tstGID);
    QVERIFY(received->mGroupID == tstGID);
}

void tst::checkFindGroupName()
{
    DataBases tstDataBases;

    QString tstName = "ОППО";

    Group tstGroup(1234, tstName, {}, {});

    Group *received = tstDataBases.findGroupName(tstName);
    QVERIFY(received == nullptr);

    tstDataBases.groupsList.append(tstGroup);
    received = tstDataBases.findGroupName(tstName);
    QVERIFY(received->mNumber == tstName);
}

void tst::checkNextId()
{
     DataBases tstDataBases;
     int nextGroupID = tstDataBases.getNextGroupID();
     int nextDisciplineID = tstDataBases.getNextDisciplineID();

     tstDataBases.incrementNextGroupID();
     tstDataBases.incrementNextDisciplineID();

     QCOMPARE(tstDataBases.getNextGroupID(), nextGroupID + 1);
     QCOMPARE(tstDataBases.getNextDisciplineID(), nextDisciplineID + 1);
}

void tst::checkGradeWork()
{
    DataBases tstDataBases;

    int tmpStudentID = 31945210;
    int tmpDisciplineID = 1;

    User tstStudent_1("Login", "Password", User::STUDENT, tmpStudentID, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    User tstStudent_2("Login2", "Password2", User::STUDENT, 31945211, 1906,
                    "", "", "", User::HIGHT);
    Discipline tstDiscipline_1("ОППО", tmpDisciplineID, Discipline::EXAM, {1906});
    Discipline tstDiscipline_2("МДКП", 2, Discipline::PASS, {1906});

    Group tstGroup(1906, "КИ19-06б", {&tstStudent_1, &tstStudent_2}, {&tstDiscipline_1, &tstDiscipline_2});

    tstDataBases.usersList.push_back(tstStudent_1);
    tstDataBases.usersList.push_back(tstStudent_2);
    tstDataBases.disciplinesList.push_back(tstDiscipline_1);
    tstDataBases.disciplinesList.push_back(tstDiscipline_2);
    tstDataBases.groupsList.push_back(tstGroup);

    tstDataBases.createGrade(tmpStudentID, tmpDisciplineID, Grade::EXCELLENT);
    tstDataBases.createGrade(tmpStudentID, 2, Grade::PASSED);
    tstDataBases.createGrade(31945211, tmpDisciplineID, Grade::EXCELLENT);
    tstDataBases.createGrade(31945211, 2, Grade::PASSED);

    QCOMPARE(tstDataBases.findGrade(tmpStudentID, tmpDisciplineID), Grade::EXCELLENT);
    QCOMPARE(tstDataBases.findGrade(tmpStudentID, 2), Grade::PASSED);
    QCOMPARE(tstDataBases.findGrade(31945211, tmpDisciplineID), Grade::EXCELLENT);
    QCOMPARE(tstDataBases.findGrade(31945211, 2), Grade::PASSED);

    tstDataBases.deleteGradesByDiscipine(tmpDisciplineID);
    QCOMPARE(tstDataBases.findGrade(tmpStudentID, tmpDisciplineID), Grade::NONE);
    QCOMPARE(tstDataBases.findGrade(31945211, tmpDisciplineID), Grade::NONE);

    tstDataBases.deleteGradesByStudent(tmpStudentID);
    QCOMPARE(tstDataBases.findGrade(tmpStudentID, tmpDisciplineID), Grade::NONE);
    QCOMPARE(tstDataBases.findGrade(tmpStudentID, 2), Grade::NONE);

    QCOMPARE(tstDataBases.findGrade(31945211, 2), Grade::PASSED);

    tstDataBases.deleteGrade(31945211, 2);
    QCOMPARE(tstDataBases.findGrade(31945211, 2), Grade::NONE);
}

void tst::checkReadAndWrite()
{
    QDir().mkdir("data");

    DataBases tstDataBases;

    int tmpLength_1 = tstDataBases.usersList.length();
    int tmpLength_2 = tstDataBases.disciplinesList.length();
    int tmpLength_3 = tstDataBases.gradesList.length();
    int tmpLength_4 = tstDataBases.groupsList.length();


    User tstStudent("Login", "Password", User::STUDENT, 31945210, 1906,
                    "Малаева", "Полина", "Маратовна", User::HIGHT);
    Discipline tstDiscipline("ОППО", 1, Discipline::EXAM, {1906});
    Grade tstGrade(tstStudent, tstDiscipline, Grade::EXCELLENT);
    Group tstGroup(1906, "КИ19-06б", {&tstStudent}, {&tstDiscipline});

    tstDataBases.usersList.push_back(tstStudent);
    tstDataBases.disciplinesList.push_back(tstDiscipline);
    tstDataBases.gradesList.push_back(tstGrade);
    tstDataBases.groupsList.push_back(tstGroup);

    tstDataBases.overwriteAll();
    tstDataBases.reloadAll();

    QCOMPARE( tstDataBases.usersList.length(), tmpLength_1 + 1);
    QCOMPARE( tstDataBases.disciplinesList.length(), tmpLength_2 + 1);
    QCOMPARE( tstDataBases.gradesList.length(), tmpLength_3 + 1);
    QCOMPARE( tstDataBases.groupsList.length(), tmpLength_4 + 1);

    QDir().rmdir("data");
}

QTEST_MAIN(tst)
#include "tst_1.moc"
