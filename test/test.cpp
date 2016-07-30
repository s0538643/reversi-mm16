#include <QtTest/QtTest>

#include "spielbrett.h"

class test : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
      this->brett = new Spielbrett();
      brett->erzeugeBrett(8, 1, 0);
	}

	void TestGetGroesse()
	{	
        QVERIFY(brett->getGroesse()==8);
    }

    void testZug()
    {
        Spielbrett::SpielPosition position;
        position.x = 4;
        position.y = 2;
        QVERIFY(this->brett->Zug(position, Spielbrett::SCHWARZ, 1));


        position.x = 4;
        position.y = 3;

        QVERIFY(this->brett->istZelleBelegt(position));
        QVERIFY(this->brett->Zug(position, Spielbrett::SCHWARZ, 1)==false);

    }


private:
Spielbrett * brett;
};

QTEST_MAIN(test)
#include "test.moc"
