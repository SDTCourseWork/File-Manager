#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QListView>
#include <QString>

#include <QHash>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QTextCodec>

#include <qDebug>
#include <QSet>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->add_input_folder, SIGNAL(clicked()), this, SLOT(add_input_directory()));
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Processing()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_input_directory()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);

    if (fileName != "") {
        ui->list_input_folder->append(fileName);
    }
}



int MainWindow::exist_resolution (QString filename, QStringList only_exist_list, QStringList delete_exist_list)
{
    QStringList strList = filename.split('.');
    QString exist = strList.at(strList.size() - 1);

     int flag_only = 0;
    if (only_exist_list.at(0) != "")
    {
        for (int i = 0; i < only_exist_list.size(); i++)
        {
            if (QString::compare(exist, only_exist_list.at(i)) == 0)
            {
                flag_only = 1;
                break;
            }

        }
    }
    else
        flag_only = 1;

    return (flag_delete || !flag_only); //если функция запрещенная или ее нет в списке разрешенных
}
