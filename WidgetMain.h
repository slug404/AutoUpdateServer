#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include "ui_WidgetMain.h"

class WidgetMain : public QWidget, private Ui::WidgetMain
{
    Q_OBJECT
    
public:
    explicit WidgetMain(QWidget *parent = 0);
    
protected:
    void changeEvent(QEvent *e);
};

#endif // WIDGETMAIN_H
