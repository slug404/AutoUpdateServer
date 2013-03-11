#include "WidgetMain.h"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void WidgetMain::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            retranslateUi(this);
            break;
        default:
            break;
    }
}
