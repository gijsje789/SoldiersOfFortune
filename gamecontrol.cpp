#include "gamecontrol.h"
#include "ui_gamecontrol.h"

#include "assetmanagement.h"

#include <QDebug>

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

void GameControl::updateDateLabel(QString date)
{
    ui->dateLabel->setText(date);
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

void GameControl::on_advanceTimeButton_pressed()
{
    int days = 0;
    int months = 0;
    int years = 0;
    switch(ui->timeSelectionComboBox->currentIndex())
    {
        case 0:
            days = 1;
            break;
        case 1:
            days = 7;
            break;
        case 2:
            months = 1;
            break;
        case 3:
            years = 1;
            break;
        default:
            break;
    }
    qDebug() << "Adding time: days(" << days << "), months(" << months << "), years(" << years << ")";
    AssetManagement::getInstance()->advanceTime(days, months, years);
}

