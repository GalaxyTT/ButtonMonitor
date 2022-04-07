#include "config.h"
#include "widget.h"
#include <QGridLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // Widget s &QTimer::timeouttructure
    setWindowTitle("ButtonMonitor");
    resize(300, 100);
    QGridLayout* grid = new QGridLayout(this);
    setLayout(grid);

    // Labels for input pins / buttons
    int column = 0;
    for (auto pin : BUTTONS) {
        // pin numbers
        QLabel* label = new QLabel("GPIO " + QString::number(pin), this);
        label->setAlignment(Qt::AlignCenter);
        grid->addWidget(label, 0, column);

        // pin states
        QLabel* state = new QLabel("0", this);
        state->setAlignment(Qt::AlignCenter);
        grid->addWidget(state, 1, column++);
        m_input_display.push_back(state);
    }

    // initialize hardware
    m_gpio = new gpio();

    // Zähler Label
    m_countLabel = new QLabel(this);
    m_countLabel->setAlignment(Qt::AlignCenter);
    grid->addWidget(m_countLabel, 3, 1);
    updateCount();

    m_timer = new QTimer(this);
    // Connect QTimer (Signal) with GUI function (Slot) "update display"
    connect(m_timer, &QTimer::timeout, this, &Widget::updateButtonState);
    connect(m_timer, &QTimer::timeout, this, &Widget::updateCount);
    m_timer->start(T_UPDATE);
}

Widget::~Widget()
{

}

void Widget::updateButtonState()
{
    int n = 0;
    for (auto pin : BUTTONS){
        int state = !m_gpio->get(pin);
        m_input_display[n++]->setText(QString::number(state));
    }
}

void Widget::updateCount()
{
    if(m_gpio->get(BUTTONS[0], true))
        m_count--;

    else if(m_gpio->get(BUTTONS[2], true))
        m_count++;

    else if(m_gpio->get(BUTTONS[1], true))
        m_count = 0;

    m_countLabel->setText(QString("Counter: ") + QString::number(m_count));
}
