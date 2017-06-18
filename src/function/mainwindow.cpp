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


QSet<QString> list_hash_of_files;
void MainWindow::Processing()
{

    QString delete_exist_all = ui->textEdit_delete_exist->toPlainText(); //считать входящие запрещенные расширения
    QStringList delete_exist_list = delete_exist_all.split('\n');
    QString only_exist_all = ui->textEdit_only_exist->toPlainText();
    QStringList only_exist_list = only_exist_all.split('\n');

    QString str = ui->list_input_folder->toPlainText(); //считать входящие каталоги
    QStringList strList = str.split('\n'); // разбиваем строку из текстедита на отдельные строки

    for (int i = 0; i < strList.size(); i++)
    { //пройтись циклом по разделителю
        //qDebug() << "TOT: " << strList.at(i);
        QString current_dir = strList.at(i);

        if(QFile::exists(current_dir))
        {
            Obxod(current_dir, only_exist_list, delete_exist_list); //пройти все вложенные файлы
            if (ui->checkbox_all_no_copy->checkState() == Qt::CheckState())
            {
                list_hash_of_files.clear(); //очищаем данные чтобы копии могли быть в разных каталогах
            }
        }
    }



    list_hash_of_files.clear(); //очищаем данные для повторного нажатия
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




    int flag_delete = 0;
    for (int i = 0; i < delete_exist_list.size(); i++)
    {
        if (QString::compare(exist, delete_exist_list.at(i)) == 0)
        {
            flag_delete = 1;
            break;
        }
    }

    return (flag_delete || !flag_only); //если функция запрещенная или ее нет в списке разрешенных
}

void MainWindow::Obrabotka (QString full_filename, QStringList only_exist_list, QStringList delete_exist_list)
{
    if (copy_file_remover(full_filename) ||
            exist_resolution(full_filename, only_exist_list, delete_exist_list))
    {

        QFile(full_filename).remove();
    }
}
int MainWindow::copy_file_remover (QString full_address)
{
    QString hash_str = hashSum(full_address);
    //проверить наличие в сенд
    if (list_hash_of_files.find( hash_str ) == list_hash_of_files.end())
    { //если нет - добавить в сенд и прервать обработку
        list_hash_of_files.insert(hash_str);
        return 0;
    }
    else
    { //если есть - удалить файл
        return 1;
    }
}

void MainWindow::Obxod (QString path, QStringList only_exist_list, QStringList delete_exist_list)
{
    QDir currentFolder(path);

    currentFolder.setFilter(QDir::Dirs | QDir::Files);
    currentFolder.setSorting(QDir::Name);

    QFileInfoList folderitems(currentFolder.entryInfoList());
    foreach (QFileInfo i_file, folderitems)
    {
        QString i_filename(i_file.fileName());


        if (i_filename == "." || i_filename == ".." || i_filename.isEmpty())
            continue;

        if (i_file.isDir())
        {
            Obxod(path + "\\" + i_filename, only_exist_list, delete_exist_list);
        }
        else
        {
            QString full_filename = path + "\\" + i_filename;

            //TagLib::FileRef ref([B]full_filename.toStdWString().c_str()[/B]); // только с таким преобразованием не игнорируются папки с нелатинскими буквами

                 // тут моя обработка, вам она не нужна
            Obrabotka(full_filename, only_exist_list, delete_exist_list);


        }
    }
}

QString MainWindow::hashSum(QString address_file)
{
    QFile file(address_file); // создаем объект класса QFile
    QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные
    if (!file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения
        return ""; // если это сделать невозможно, то завершаем функцию
    data = file.readAll(); //считываем все данные с файла в объект data
    QString blah = QString(QCryptographicHash::hash(data,QCryptographicHash::Md5).toHex());

    return blah;
}

