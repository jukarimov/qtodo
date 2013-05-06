#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void dayTimeNote(int day, QString time, QString note) {
        qDebug() << "PUSHED:: " << day << time << note;
        this->Daylist[day].time.push_back(time);
        this->Daylist[day].note.push_back(note);
    };

    void dbFetchTable(int day);

    int inMemory[];

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

    struct daylist {
        QVector<QString> time;
        QVector<QString> note;
    } Daylist[7];

    int colTime;
    int colNote;

    QString timestr;
    QString notestr;

private slots:
    void on_comboDay_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
