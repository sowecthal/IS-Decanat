#ifndef DATABASES_H
#define DATABASES_H

#include "dataclasses/user.h"
#include "dataclasses/discipline.h"
#include "dataclasses/group.h"
#include "dataclasses/grade.h"

#include <QString>
#include <QList>

class DataBases
{
public:
    //! Конструктор по умолчанию
    DataBases();

    //! Поиск пользователя для авторизации
    User* findAuthUser(QString fLogin, QString fPassword);
    /* Возвращает значение поля mRole, найденного пользователя;
     * В противном случае, возвращает -1
     */

    //! Поиск по id
    User *findStudent(int fID);
    Group *findGroup(int fID);
    //! Поиск по имени
    Group *findGroupName(QString fName);

    //! Создание оценки
    void createGrade(int cStudentID, int cDisciplineID, Grade::grades cGrade);
    //! Поиск оценки
    Grade::grades findGrade(int fStudentID, int fDisciplineID);
    //! Перезапись оценки
    void resetGrade(int rStudentID, int rDisciplineID, Grade::grades rGrade);
    //! Удаление оценки
    void deleteGrade(int dStudentID, int dDisciplineID);
    //! Удаление всех оценок по дисциплине
    void deleteGradesByDiscipine(int dDisciplineID);
    //! Удаление всех оценок студента
    void deleteGradesByStudent(int dStudentID);

    //! Перезапись файлов
    void overwriteAll();
    void overwriteUsers();
    void overwriteDisciplines();
    void overwriteGrades();
    void overwriteGroups();
    //! Перезагрузка
    void reloadGroups();
    void reloadGrades();
    void reloadAll();
    //! Получение доступного id
    int getNextDisciplineID();
    int getNextGroupID();
    //! Инкремент id
    void incrementNextDisciplineID();
    void incrementNextGroupID();
    //! Сопоставление групп со студентами и дисциплинами
    void coinsideGroups();

    //! Списки объектов
    QList<User> usersList;
    QList<Discipline> disciplinesList;
    QList<Grade> gradesList;
    QList<Group> groupsList;

private:
    //! Загрузка файлов
    void loadUsers();
    void loadGroups();
    void loadDisciplines();
    void loadGrades();

    //! Поля следующих id
    int nextDisciplineID = 0;
    int nextGroupID = 0;
};
#endif // DATABASES_H
