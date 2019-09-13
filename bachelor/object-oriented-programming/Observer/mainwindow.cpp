#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "textfile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

void MainWindow::init()
{
    _textFile = new TextFile("test.txt");
    // register observers for next updates
    _textFile->addObserver(ui->textEdit);
    _textFile->addObserver(ui->textFileStats);

    // force a first update ourselves to initialize
    ui->textEdit->notify(_textFile);
    ui->textFileStats->notify(_textFile);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (_textFile != NULL)
        delete _textFile;
}
