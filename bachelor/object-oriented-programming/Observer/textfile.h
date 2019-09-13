#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QObject>
#include <QString>

class QFileSystemWatcher;
class QFile;
class QTextStream;

#include "textfilesubject.h"

class TextFile : public QObject, public TextFileSubject
{
    Q_OBJECT

public:
    TextFile(const QString &path);
    ~TextFile();

    QString getContents() const { return _contents; }
    int getNumWords() const;
    int getNumChars() const;
protected slots:
    void fileUpdated(const QString &path);
private:
    void init();
    void readContents(bool update);

    QString _path;
    QFile *_file;
    QFileSystemWatcher *_watcher;

    QString _contents;
};

#endif // TEXTFILE_H
