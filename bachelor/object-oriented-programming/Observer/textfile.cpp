#include "textfile.h"

#include <QFileSystemWatcher>
#include <QFile>
#include <QStringList>
#include <QTextStream>

TextFile::TextFile(const QString &path)
    : TextFileSubject(this), _path(path), _file(NULL), _watcher(NULL), _contents("")
{
    init();
}

TextFile::~TextFile()
{
    if (_file != NULL)
    {
        _file->close();
        delete _file;
    }

    if (_watcher != NULL)
    {
        _watcher->removePath(_path);
        delete _watcher;
    }
}

int TextFile::getNumChars() const
{
    return _contents.size();
}

int TextFile::getNumWords() const
{
    if (_contents.isEmpty())
        return 0;
    else
        return _contents.split(QRegExp("\\s+")).size();
}

void TextFile::init()
{
    _file = new QFile(_path);
    if (!_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("couldn't find the file");
        return; // FIXME: better error handling
    }

    // read the contents of the file
    readContents(false);

    // watch for changes to the file
    _watcher = new QFileSystemWatcher();
    _watcher->addPath(_path);
    connect(_watcher, SIGNAL(fileChanged(QString)),
            this, SLOT(fileUpdated(QString)));

    qDebug("watcher connected to %s", qPrintable(_watcher->files().first()));

    // close file
    _file->close();
}

void TextFile::readContents(bool update)
{
    if (update)
    {
        // re-open file
        _file->open(QIODevice::ReadOnly | QIODevice::Text);
    }

    // read contents
    _contents = "";
    while (!_file->atEnd())
        _contents.append(_file->readLine());

    // close file
    _file->close();
}

void TextFile::fileUpdated(const QString &path)
{
    /*
    qDebug("file is updated");
    */

    // refresh contents
    readContents(true);

    /*
    qDebug("content: %s", qPrintable(_contents));
    qDebug("num words: %d", getNumWords());
    qDebug("num chars: %d", getNumChars());
    */

    // Work-around for Qt bug 19350
    if (_watcher->files().empty())
    {
        // add it again
        _watcher->addPath(_path);
    }

    // notify all observers
    notifyAll();
}

