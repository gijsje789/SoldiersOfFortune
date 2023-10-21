#include "gamecontrol.h"
#include "ui_gamecontrol.h"

GameControl::GameControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameControl)
{
    ui->setupUi(this);
}

GameControl::~GameControl()
{
    delete ui;
}

void GameControl::updateMoneyLabel(double value)
{
    ui->moneyLabel->setText(convertNumberToDollarString(value));
}

QString GameControl::convertNumberToDollarString(double value)
{
    QString currency = QString::number(value, 'f', 2);
    auto decimal = currency.indexOf('.');  // find decimal point
    if(decimal == std::string::npos)    // no decimal point
        decimal = currency.length();
    if (decimal > 3) // Insert commas
    {
        for (auto x = decimal - 3; x > 0; x -= 3)
            currency.insert(x, ",");
    }
    currency.insert(0, "$"); // Insert dollar sign
    return currency;
}
