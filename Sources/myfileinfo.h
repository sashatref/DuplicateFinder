#pragma once

#include <QString>
#include <QFile>
#include "functions.h"

class MyFileInfo
{
public:
    MyFileInfo(const QString &_filePath = "");

    void calcHash();

    void calcSize();

    const qint64 &getFileSize() const;

    const QString &getHash() const;
    const QString &getFilePath() const;

    bool isHashPresent() const;
    bool compareFiles(const MyFileInfo &other);

    friend QDebug & operator <<(QDebug &_debug, const MyFileInfo &_value);

private:
    QString m_filePath;
    qint64 m_fileSize;
    bool m_isHashPresent;
    QString m_hash;

};


