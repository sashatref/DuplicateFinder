#include "functions.h"
#include <QDir>
#include <QCryptographicHash>

QStringList Files::countDir(const QString &_path, const QStringList &_ext, bool *_stop)
{
    QStringList files;
    if(_stop && *_stop) ///<остановка процесса поиска каталогов
    {
        return files;
    }

    QDir dir(_path);

    QStringList entryListFiles = dir.entryList(_ext, QDir::Files);
    QStringList entryListDirs = dir.entryList(QDir::Dirs);

    for(int i = 0 ; i < entryListFiles.size(); i++)
    {
        files.append(_path + "/" + entryListFiles[i]);
    }

    for(int i = 0; i < entryListDirs.size(); i++)
    {
        if(entryListDirs[i] != "." && entryListDirs[i] != "..")
        {
            files.append(countDir(_path + "/" + entryListDirs[i], _ext, _stop));
        }
    }

    return files;
}

QString Files::calcHash(const QByteArray &_bData)
{
    return QString(QCryptographicHash::hash(_bData, QCryptographicHash::Md5).toHex());
}
