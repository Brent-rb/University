#include "textfileview.h"
#include "textfileobserver.h"

TextFileView::TextFileView(QWidget *parent) :
    QTextEdit(parent)
{
}

TextFileView::~TextFileView()
{
}

void TextFileView::loadUpdate(TextFile *model)
{
    /*
    qDebug("in loadUpdate()");
    */

    if (model == NULL)
        return;

    setPlainText(model->getContents());
}

void TextFileView::notify(TextFile *model)
{
    loadUpdate(model);
}
