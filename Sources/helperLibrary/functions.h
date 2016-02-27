#pragma once

class QTranslator;

#include <QFile>
#include <QVariant>
#include <QString>


QString getCommandLine();


namespace Files
{
    /*!
     * \brief возвращает список свех файлов в указанном каталоге и подкаталогах, с заданным фильтром.
     * \param _path
     * \param _ext
     * \return
     */

QStringList countDir(const QString &_path, const QStringList &_ext, bool *_stop = 0);

QString calcHash(const QByteArray &_bData);
}
