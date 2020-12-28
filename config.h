#ifndef CONFIG_H
#define CONFIG_H

#include <QStringList>

namespace Config
{
    const QString reservAdminLogin = "U4Oxn9uJ";
    const QString reservAdminPassword = "U4Oxn9uJ";

    const QStringList roles = {"Студент", "Диспетчер деканата", "Администратор"};
    const QStringList adminComboBoxItems = {"Пользователи", "Группы", "Дисциплины"};
    const QStringList supervisorComboBoxItems = {"Студенты", "Группы", "Дисциплины"};
    const QStringList studentComboBoxItems = {"Оценки", "Стипендия"};
    const QStringList disciplineFormOfControl = {"Зачёт", "Экзамен"};
}
#endif // CONFIG_H
