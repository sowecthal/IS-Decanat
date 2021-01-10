#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <QString>
#include <QList>

class Discipline
{
public:
    enum forms {EXAM, PASS};
    //! Конструктор по умолчанию
    Discipline() {}
    //! Конструктор дисциплины
    Discipline(QString sName, int sDisciplinesID, forms sForm, QList<int> sGroups);

    int mDisciplineID;
    QString mName;
    forms mForm;
    QList<int> mGroups;
};

#endif // DISCIPLINE_H
