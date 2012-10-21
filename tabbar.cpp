#include "tabbar.h"
#include "tabview.h"
#include "ghostwindow.h"
#include "tabbedwindow.h"

#include <QMouseEvent>
#include <QApplication>


TabBar::TabBar(QWidget *parent) :
    QTabBar(parent),
    m_ghost(NULL)
{
}


TabBar::~TabBar()
{
    delete m_ghost;
}


void TabBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_ghost) {
        m_ghost->moveWithOffset(event->globalPos());
    }
}


void TabBar::mousePressEvent(QMouseEvent *event)
{
    // If left button is pressed start tab move event
    if (event->button() == Qt::LeftButton && tabAt(event->pos()) > -1) {
        m_ghost = new GhostWindow(this, event->pos());
        m_ghost->show();
    }

    // Call superclass
    QTabBar::mousePressEvent(event);
}


void TabBar::mouseReleaseEvent(QMouseEvent *event)
{
    // Call superclass if a button different than the left one was released
    // and return
    if (event->button() != Qt::LeftButton) {
        QTabBar::mouseReleaseEvent(event);
        return;
    }

    // Execute drag code only if far enough
    if (m_ghost->manhattanLength(event->globalPos())) {
        TabBar *w = dynamic_cast<TabBar*>(
                    QApplication::widgetAt(event->globalPos()));

        // Choose action by the widget under the mouse's coordinates
        if (w == NULL) {
            if (count() == 1) {
                // Move the current window into the new position
                window()->move(m_ghost->pos());
            } else {
                // Creates a new window with the dragged tab
                createNewWindow(m_ghost);
            }
        } else {
            // Move the dragged tab into the window under the cursor
            TabbedWindow *wnd = dynamic_cast<TabbedWindow*>(w->window());

            if (wnd != NULL) {
                moveToWindow(wnd, event->globalPos(), m_ghost);
            }
        }
    }

    // Close ghost
    m_ghost->close();
}


void TabBar::moveToWindow(TabbedWindow *wnd, const QPoint &pos,
                                 GhostWindow *ghost)
{
    // Remove view from this window
    TabView *view = static_cast<TabView*>(parent());
    int index = ghost->index();
    QString text = tabText(index);
    QWidget *page = view->widget(index);

    view->removeTab(index);

    // Insert tab into the new window at the given cursor's position
    index = wnd->insertTab(pos, page, text);

    // Set it as the current tab and move focus to the new window
    wnd->setCurrentView(index);
    wnd->raise();
}


void TabBar::tabRemoved(int index)
{
    if (count() == 0) {
        window()->close();
    }
}


void TabBar::createNewWindow(GhostWindow *ghost)
{
    // Create the new window with the same size and centered under the cursor
    TabbedWindow *wnd = new TabbedWindow();

    wnd->setGeometry(ghost->geometry());

    // Move widget to the new window
    TabView *view = static_cast<TabView*>(parent());
    int index = ghost->index();
    QWidget *tab = view->widget(index);
    QString text = view->tabText(index);

    view->removeTab(index);
    wnd->addView(tab, text);

    // Show the new window
    wnd->show();
}
