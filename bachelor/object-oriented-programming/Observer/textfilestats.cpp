#include "textfilestats.h"
#include "ui_textfilestats.h"

#include "textfilesubject.h"

TextFileStats::TextFileStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextFileStats)
{
    ui->setupUi(this);
}

TextFileStats::~TextFileStats()
{
    delete ui;
}

void TextFileStats::loadUpdate(TextFile *model)
{
    if (model == NULL)
        return;

    ui->numChars->display(model->getNumChars());
    ui->numWords->display(model->getNumWords());
}

void TextFileStats::notify(TextFile *model)
{
    loadUpdate(model);
}
