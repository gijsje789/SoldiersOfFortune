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

    void updateMoneyLabel(double value);

private:
    Ui::GameControl *ui;

    QString convertNumberToDollarString(double value);
};

#endif // GAMECONTROL_H
