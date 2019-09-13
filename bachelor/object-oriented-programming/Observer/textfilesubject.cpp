#include <QList>
#include "textfilesubject.h"
#include "textfileobserver.h"

TextFileSubject::TextFileSubject(TextFile *model)
{
    _model = model;
}

void TextFileSubject::addObserver(TextFileObserver *observer)
{
    _observers.append(observer);
}

void TextFileSubject::removeObserver(TextFileObserver *observer)
{
    _observers.removeAll(observer);
}

void TextFileSubject::notifyAll()
{
    TextFileObserver *o;
    foreach (o, _observers)
    {
        o->notify(_model);
    }
}
