#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "widgetViewer.h"
#include "widgetSettings.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget() = default;

private:
    WidgetViewer *m_pViewer;
    WidgetSettings *m_pSettings;
};

#endif // MAINWIDGET_H
