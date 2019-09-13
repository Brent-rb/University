#ifndef TEXTFILEOBSERVER_H
#define TEXTFILEOBSERVER_H

class TextFile;

class TextFileObserver
{
public:
    TextFileObserver() {}
    virtual void notify(TextFile *model) = 0;
};

#endif // TEXTFILEOBSERVER_H
