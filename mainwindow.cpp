#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("todo.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "todo.xml read error";
        return;
    }

    QXmlStreamReader xs(&file);

    while (!xs.atEnd()) {
        if (xs.readNextStartElement()) {

            //qDebug() << xs.name().toString();

            QXmlStreamAttributes attr = xs.attributes();


            int row;
            int colTime = 0;
            int colNote = 1;
            ui->table->setColumnWidth(colNote, 600);

            if (xs.isStartElement() && xs.name().toString() == "time") {

                row = ui->table->rowCount();
                ui->table->insertRow(row);

                qDebug() << "d= " << attr.value("d");
                qDebug() << "h= " << attr.value("h");
                qDebug() << "m= " << attr.value("m");

                QString timestr = attr.value("h").toString();
                timestr += attr.value("m").toString().toInt() <= 9 ? ":0" : ":";
                timestr += attr.value("m").toString();

                QLineEdit *cell = new QLineEdit();
                cell->setText(timestr);
                ui->table->setCellWidget(row, colTime, cell);
            }

            if (xs.name().toString() == "note") {
                QString noteText = xs.readElementText();
                qDebug() << "note: " << noteText;

                QLineEdit *cell = new QLineEdit();
                cell->setText(noteText);

                ui->table->setCellWidget(row, colNote, cell);

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

void MainWindow::on_pushNew_clicked()
{
    qDebug() << "new";
}

void MainWindow::on_pushDelete_clicked()
{
    qDebug() << "delete";
}

void MainWindow::on_comboDay_currentIndexChanged(int index)
{
    qDebug() << index;
}
