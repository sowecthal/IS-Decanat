#include <QtTest>
#include "../IS-Decanat/dataclasses/user.h"

Q_DECLARE_METATYPE(User);

class tst_1 : public QObject
{
    Q_OBJECT
private slots:
    //Тесты пользователя
    void getLogin();
};

void tst_1::getLogin()
{
    QString n = "login";
    User u0(n, "Password", 2);
    QVERIFY(u0.getLogin() == n);
}

QTEST_MAIN(tst_1)
#include "tst_1.moc"
