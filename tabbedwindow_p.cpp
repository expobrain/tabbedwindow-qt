#include "tabbedwindow_p.h"
#include "viewtabs_p.h"


TabbedWindowPrivate::TabbedWindowPrivate(TabbedWindow* q_ptr)
{
    // Create tab widget
    tabs = new ViewTabsPrivate();
    tabs->setTabsClosable(true);
    tabs->setDocumentMode(true);

    // Set up main window
    this->q_ptr = q_ptr;
    this->q_ptr->setCentralWidget(tabs);
}


int TabbedWindowPrivate::addView(QWidget *view, const QString &title)
{
    return tabs->addTab(view, title);
}


void TabbedWindowPrivate::removeView(int index)
{
    tabs->removeTab(index);
}
