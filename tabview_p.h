#ifndef TABVIEW_P_H
#define TABVIEW_P_H

#include <QTabWidget>

class TabViewPrivate : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabViewPrivate(QWidget *parent = 0);
    int tabAt(const QPoint &pos);
    
signals:
    
public slots:
    
};

#endif // TABVIEW_P_H
