#ifndef GRADE_H
#define GRADE_H

#include "user.h"
#include "discipline.h"

class Grade
{
public:
    enum grades {NOPASSED, PASSED, BAD, OKAY, GOOD, EXCELLENT};
    //! Конструктор по умолчанию
    Grade() {}
    //! Конструктор оценки
    Grade(User *sUser, Discipline *sDiscipline, grades sGrade);
    //! Устанавливает новое значение
    void reset(grades newGrade);
    //! Возвращает значение
    Grade::grades value() const;
private:
    User *mStudent;
    Discipline *mDiscipline;
    Grade::grades mValue;

    //! Проверяет соответсвие дисциплыны и оценки, возвращает валидное  значение
    grades getSuitable(grades cValue);
};

#endif // GRADE_H
