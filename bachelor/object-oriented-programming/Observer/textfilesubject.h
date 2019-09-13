#ifndef TEXTFILESUBJECT_H
#define TEXTFILESUBJECT_H

class TextFileObserver;
class TextFile;

class TextFileSubject
{
public:
    TextFileSubject(TextFile *model);
    void addObserver(TextFileObserver *observer);
    void removeObserver(TextFileObserver *observer);
    void notifyAll();
private:
    QList<TextFileObserver*> _observers;
    TextFile *_model;
};

#endif // TEXTFILESUBJECT_H
