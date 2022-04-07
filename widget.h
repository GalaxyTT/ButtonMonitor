#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "gpio.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void updateButtonState();
    void updateCount();

private:
    QList<QLabel*> m_input_display;
    QTimer* m_timer;
    gpio* m_gpio;
    QLabel* m_countLabel = nullptr;
    unsigned int m_count = 0;

};

#endif // WIDGET_H
