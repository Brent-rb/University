#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "textfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    void init();

    Ui::MainWindow *ui;
    TextFile *_textFile;
};

#endif // MAINWINDOW_H
