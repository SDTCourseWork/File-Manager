#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


};
public:
    int exist_resolution (QString filename, QStringList only_exist_list, QStringList delete_exist_list);
    void Obrabotka (QString full_filename, QStringList only_exist_list, QStringList delete_exist_list);
    void Obxod (QString path, QStringList only_exist_list, QStringList delete_exist_list);
    int copy_file_remover (QString full_address);
    QString hashSum(QString address_file);
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();


#endif // MAINWINDOWTQW_H
