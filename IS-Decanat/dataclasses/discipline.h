#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <QString>
#include <QList>

class Discipline
{
public:
    //! Конструктор по умолчанию
    Discipline() {}
    //! Конструктор дисциплины
    Discipline(QString sName, int sDisciplinesID, int sForm, QList<int> sGroups);

    int mDisciplineID;
    QString mName;
    int mForm;
    QList<int> mGroups;
};

#endif // DISCIPLINE_H
