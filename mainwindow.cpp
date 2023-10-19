#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mainmenu.h"
#include "organizationstorage.h"

#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget = new MainMenu(this, this);
    this->setCentralWidget(centralWidget);

    moneyLabel = new QLabel();
    moneyLabel->setMinimumWidth(100);
    moneyLabel->setAlignment(Qt::AlignLeft);
    ui->menubar->setCornerWidget(moneyLabel);

    ui->menubar->setEnabled(false);

    updateMoney(100000000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMoney(double value)
{
    moneyLabel->setText(convertNumberToDollarString(value));
}

void MainWindow::enableMenuBar(bool value)
{
    ui->menubar->setEnabled(value);
}

void MainWindow::newGame()
{
    enableMenuBar(true);
    on_actionStorage_triggered();
}

QString MainWindow::convertNumberToDollarString(double value)
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


void MainWindow::on_actionStorage_triggered()
{
    QWidget* tempWidget = new OrganizationStorage;
    this->setCentralWidget(tempWidget);
    delete centralWidget;
    centralWidget = tempWidget;
}

