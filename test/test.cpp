#include <QtTest/QtTest>

#include "../spielbrett.h"
#include "../brettwidget.h"
#include "../spielwindow.h"
#include "../mainwindow.h"
#include "../settings.h"

class test : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
      this->brett = new Spielbrett();
      brett->erzeugeBrett(8, 1, 0, Spielbrett::WEISS);

      this->brettwidget = new BrettWidget();
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

    void testKI()
    {


        this->brettwidget->brett.erzeugeBrett(8, 1, 1, Spielbrett::WEISS);
        this->brettwidget->brett.calculateBestMove(Spielbrett::WEISS, 1);
        QVERIFY(this->brettwidget->brett.Zug(this->brettwidget->brett.getBestMove(), Spielbrett::WEISS, 1));
        QVERIFY(this->brettwidget->brett.istZelleBelegt({5,4}));

    }



private:
Spielbrett * brett;
BrettWidget *brettwidget;
SpielWindow *spielwindow;



};

QTEST_MAIN(test)
#include "test.moc"
