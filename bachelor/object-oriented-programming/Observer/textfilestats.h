#ifndef TEXTFILESTATS_H
#define TEXTFILESTATS_H

#include <QWidget>

namespace Ui {
class TextFileStats;
}

#include "textfile.h"
#include "textfileobserver.h"
class TextFile;

class TextFileStats : public QWidget, public TextFileObserver
{
    Q_OBJECT
    
public:
    explicit TextFileStats(QWidget *parent = 0);
    virtual ~TextFileStats();
    virtual void notify(TextFile *model);
private:
    void loadUpdate(TextFile *model);
    Ui::TextFileStats *ui;    
};

#endif // TEXTFILESTATS_H
