#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lastScene = nullptr;
    lastData = nullptr;
    lastImage = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage(QImage* image) {
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(*image));

    ui->graphicsView->setScene(scene);
    if(lastScene != nullptr)
        delete lastScene;
    lastScene = scene;
    ui->graphicsView->repaint();
}

void MainWindow::updateImage(QImage *image, uint8_t* data) {
    setImage(image);
    if(lastImage != nullptr)
        delete lastImage;
    if(lastData = nullptr)
        delete[] lastData;

    lastImage = image;
    lastData = data;
}
