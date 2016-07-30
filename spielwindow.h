#ifndef SPIELWINDOW_H
#define SPIELWINDOW_H

#include "brettwidget.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QMediaPlayer>
#include <QSound>
#include <QCoreApplication>

class QLabel;

class SpielWindow : public QWidget
{
    Q_OBJECT
public:
    SpielWindow();
    BrettWidget *brettwidget;

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


};

#endif // SPIELWINDOW_H
