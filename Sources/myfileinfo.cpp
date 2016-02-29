#include "myfileinfo.h"
#include <QDebug>






MyFileInfo::MyFileInfo(const QString &_filePath):
    m_fileSize(0),
    m_hash(),
    m_isHashPresent(false),
    m_filePath(_filePath)
{

}

void MyFileInfo::calcHash()
{
    QFile file(m_filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        m_hash = Files::calcHash(file.read(10000));
        file.close();
        m_isHashPresent = true;
    }
}

void MyFileInfo::calcSize()
{
    QFile file(m_filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        m_fileSize = file.size();
        file.close();
    }
}

const qint64 &MyFileInfo::getFileSize() const
{
    return m_fileSize;
}

const QString &MyFileInfo::getHash() const
{
    return m_hash;
}

const QString &MyFileInfo::getFilePath() const
{
    return m_filePath;
}

bool MyFileInfo::isHashPresent() const
{
    return m_isHashPresent;
}

QDebug &operator <<(QDebug &_debug, const MyFileInfo &_value)
{
    _debug
            << "Размер: " << _value.m_fileSize
            << " Хэш: " << _value.m_hash
            << " Файл: " << _value.m_filePath;
    return _debug;
}

bool MyFileInfo::compareFiles(const MyFileInfo &other)
{
    QFile file1(this->m_filePath);
    if(!file1.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QFile file2(other.m_filePath);
    if(!file2.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray data1 = file1.read(1024);
    QByteArray data2 = file2.read(1024);
    while(data1.size() != 0 && data2.size() != 0)
    {
        if(data1 != data2)
        {
            return false;
        }
        data1 = file1.read(1024);
        data2 = file2.read(1024);
    }

    return true;
}

QString MyFileInfo::toString() const
{
    return QString("Размер: %1 | Хэш: %2 | Файл: %3")
            .arg(m_fileSize)
            .arg(m_hash)
            .arg(m_filePath);
}
