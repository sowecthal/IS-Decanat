#ifndef CONFIG_H
#define CONFIG_H

#include <QStringList>

namespace Config
{
    const QString reservAdminLogin = "U4Oxn9uJ";
    const QString reservAdminPassword = "U4Oxn9uJ";
    const QStringList adminComboBoxItems = {"Пользователи", "Группы", "Дисциплины"};
    const QStringList supervisorComboBoxItems = {"Студенты", "Группы", "Дисциплины"};
    const QStringList studentComboBoxItems = {"Оценки", "Стипендия"};
    const QStringList grant = {"Нет", "Обычная", "Повышенная"};
    const QStringList disciplineFormOfControl = {"Зачёт", "Экзамен"};
    const QStringList gradesExam = {"Нет", "Неудовлетворительно", "Удовлетворительно", "Хорошо", "Отлично"};
    const QStringList gradesPass = {"Нет","Не зачтено", "Зачтено"};
}
#endif // CONFIG_H
