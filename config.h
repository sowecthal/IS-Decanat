#ifndef CONFIG_H
#define CONFIG_H

#include <QStringList>

namespace Config
{
    const QStringList adminComboBoxItems = {"Пользователи", "Группы", "Дисциплины"};
    const QStringList supervisorComboBoxItems = {"Студенты", "Группы", "Дисциплины"};
    const QStringList studentComboBoxItems = {"Оценки", "Стипендия"};
}
#endif // CONFIG_H
