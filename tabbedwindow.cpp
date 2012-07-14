#include "tabbedwindow.h"
#include "tabbedwindow_p.h"


TabbedWindow::TabbedWindow(QWidget *parent) :
    QMainWindow(parent),
    d_ptr(new TabbedWindowPrivate(this))
{
}


TabbedWindow::~TabbedWindow()
{
    delete d_ptr;
}


int TabbedWindow::insertTab(QPoint pos, QWidget *page, QString text)
{
    return d_ptr->insertTab(pos, page, text);
}


int TabbedWindow::addView(QWidget *view, const QString &title)
{
    return d_ptr->addView(view, title);
}


void TabbedWindow::removeView(int index)
{
    d_ptr->removeView(index);
}
