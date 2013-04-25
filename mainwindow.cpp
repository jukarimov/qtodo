#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int day;
    int row;

    colTime = 0;
    colNote = 1;

    QString timestr;
    QString notestr;

    ui->setupUi(this);

    ui->table->setColumnWidth(colNote, 600);

    QFile file("todo.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "todo.xml read error";
        return;
    }

    QXmlStreamReader xs(&file);

    while (!xs.atEnd())
    {
        if (xs.readNextStartElement()) {

            //qDebug() << xs.name().toString();

            QXmlStreamAttributes attr = xs.attributes();

            if (xs.isStartElement() && xs.name().toString() == "time") {

                /*
                row = ui->table->rowCount();
                ui->table->insertRow(row);


                qDebug() << "d= " << attr.value("d");
                qDebug() << "h= " << attr.value("h");
                qDebug() << "m= " << attr.value("m");
                */
                day = attr.value("d").toString().toInt();

                timestr = attr.value("h").toString();
                timestr += attr.value("m").toString().toInt() <= 9 ? ":0" : ":";
                timestr += attr.value("m").toString();

                /*
                QLineEdit *cell = new QLineEdit();
                cell->setText(timestr);
                ui->table->setCellWidget(row, colTime, cell);
                */
            }

            if (xs.name().toString() == "note") {

                notestr = xs.readElementText();

                dayTimeNote(day, timestr, notestr);

                /*
                QLineEdit *cell = new QLineEdit();
                cell->setText(noteText);

                ui->table->setCellWidget(row, colNote, cell);
                */
            }
        }
    }
    for (int i = 0; i < 7; ++i) {

        if (Daylist[i].time.size()) {

            qDebug() << "day: " << i;

            for (int j = 0; j < Daylist[i].time.size(); ++j)
            {
                row = ui->table->rowCount();
                ui->table->insertRow(row);

                qDebug() << "time: " << Daylist[i].time[j];
                QLineEdit *cell = new QLineEdit();
                cell->setText(Daylist[i].time[j]);
                ui->table->setCellWidget(row, colTime, cell);

                qDebug() << "note: " << Daylist[i].note.at(j);
                QLineEdit *cell2 = new QLineEdit();
                cell2->setText(Daylist[i].note[j]);
                ui->table->setCellWidget(row, colNote, cell2);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_comboDay_currentIndexChanged(int index)
{
    qDebug() << "getting index: " << index;
    int row;

    ui->table->setRowCount(0);

    for (int j = 0; j < Daylist[index].time.size(); ++j)
    {
        row = ui->table->rowCount();
        ui->table->insertRow(row);

        qDebug() << "time: " << Daylist[index].time[j];
        QLineEdit *cell = new QLineEdit();
        cell->setText(Daylist[index].time[j]);
        ui->table->setCellWidget(row, colTime, cell);

        qDebug() << "note: " << Daylist[index].note.at(j);
        QLineEdit *cell2 = new QLineEdit();
        cell2->setText(Daylist[index].note[j]);
        ui->table->setCellWidget(row, colNote, cell2);
    }
}
