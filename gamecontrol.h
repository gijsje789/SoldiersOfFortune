#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QWidget>

namespace Ui {
class GameControl;
}

class GameControl : public QWidget
{
    Q_OBJECT

public:
    explicit GameControl(QWidget *parent = nullptr);
    ~GameControl();

public slots:
    void updateMoneyLabel(double value);
    void updateDateLabel(QString date);

private slots:
    void on_advanceTimeButton_pressed();

signals:
    void advanceTime(int days, int months, int years);

private:
    Ui::GameControl *ui;

    QString convertNumberToDollarString(double value);
};

#endif // GAMECONTROL_H
