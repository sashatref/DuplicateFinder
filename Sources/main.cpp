#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <locale>
#include "cmdlineparser.h"
#include "functions.h"
#include "myfileinfo.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QCoreApplication a(argc, argv);

    CmdLineParser parser;
    parser << CmdLineItem("path", true, false, false, "Каталог для поиска дубликатов файлов");

    int result = parser.parse(argc, argv);
    switch(result)
    {
    case CmdLineParser::Error:
        qDebug() << (parser.getLastError() + "\n\n" + parser.getHelpString()).toStdString().c_str();
        return 0;
        break;
    case CmdLineParser::Help:
        qDebug() << parser.getHelpString().toStdString().c_str();
        return 0;
        break;
    }

    QElapsedTimer timer;
    timer.start();


    QString path = parser.at("path")->getValue().at(0);
    qDebug() << "Указанный каталог: " << path;

    QStringList files = Files::countDir(path, QStringList());
    qDebug() << "Найдено файлов: " << files.size();
    qDebug() << "Timer:" << timer.elapsed();

    QVector<MyFileInfo> fileInfoList;

    for(int i = 0 ; i < files.size(); i++)
    {
        fileInfoList.append(MyFileInfo(files[i]));
        fileInfoList.last().calcSize();
    }

    qDebug() << "Посчитаны размеры всех файлов";
    qDebug() << "Timer:" << timer.elapsed();

    qSort(fileInfoList.begin(), fileInfoList.end(), [](const MyFileInfo &_item1, const MyFileInfo &_item2)
    {
        return _item1.getFileSize() < _item2.getFileSize();
    });

    qDebug() << "Массив отсортирован по размеру";
    qDebug() << "Timer:" << timer.elapsed();

    for(int i = 1 ; i < fileInfoList.size(); i++)
    {
        if(fileInfoList[i].getFileSize() == fileInfoList[i - 1].getFileSize())
        {
            if(!fileInfoList[i].isHashPresent()) fileInfoList[i].calcHash();
            if(!fileInfoList[i - 1].isHashPresent()) fileInfoList[i - 1].calcHash();
            if(fileInfoList[i].getHash() == fileInfoList[i - 1].getHash())
            {
                if(fileInfoList[i].compareFiles(fileInfoList[i - 1]))
                {
                    qDebug() << fileInfoList[i];
                    qDebug() << fileInfoList[i - 1];
                    qDebug() << "------------------------\n";
                }
            }
        }
    }

    qDebug() << "Timer:" << timer.elapsed();
    qDebug() << "Завершено";

    return 0;
}
