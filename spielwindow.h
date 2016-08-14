#ifndef SPIELWINDOW_H
#define SPIELWINDOW_H

#include "brettwidget.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QMediaPlayer>
#include <QSound>
#include <QCoreApplication>
#include <string>

class QLabel;

class SpielWindow : public QWidget
{
    Q_OBJECT
public:
    SpielWindow();
    SpielWindow(QString name1, QString name2, Spielbrett::Zellen_Farbe spielerfarbe, int sprache);
    BrettWidget *brettwidget;
    ~SpielWindow();

private slots:
    /** Aktualisiert alle Label des Spielwindows.
     * @brief updateLabels
     */
    void updateLabels();


private:
    /** Erzeugt ein neues Label mit dem Text.
     * @brief createLabel
     * @param text Der Text des Labels.
     * @return Das Label.
     */
    QLabel *createLabel(const QString &text);
    QLabel *Spieler;
    QLabel *weissePunkte;
    QLabel *schwarzePunkte;
    QLabel *Sieger;
    QString weissname;
    QString schwarzname;
    int sprache;


};

#endif // SPIELWINDOW_H
