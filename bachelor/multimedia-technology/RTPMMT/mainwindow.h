#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <stdio.h>
#include <QImage>
#include <stdlib.h>
#include <stdint.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setImage(QImage* image);

private:
    Ui::MainWindow *ui;

    QGraphicsScene* lastScene;

    QImage* lastImage;
    uint8_t* lastData;

public slots:
    void updateImage(QImage* image, uint8_t* data);
};

#endif // MAINWINDOW_H
