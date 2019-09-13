#ifndef TEXTFILEVIEW_H
#define TEXTFILEVIEW_H

#include <QTextEdit>
#include "textfile.h"

#include "textfileobserver.h"

class TextFileView : public QTextEdit, public TextFileObserver
{
    Q_OBJECT
public:
    explicit TextFileView(QWidget *parent = 0);
    virtual ~TextFileView();
    void setTextFile(TextFile *file);
    virtual void notify(TextFile *model);
signals:
    
public slots:
    void loadUpdate(TextFile *model);
};

#endif // TEXTFILEVIEW_H
