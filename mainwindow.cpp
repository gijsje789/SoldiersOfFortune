#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mainmenu.h"
#include "organizationstorage.h"
#include "gameinfo.h"

#include <QMenuBar>
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>

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

void MainWindow::switchCentralWidget(QWidget *newWidget)
{
    this->setCentralWidget(newWidget);
    delete centralWidget;
    centralWidget = newWidget;
}

void MainWindow::newGame()
{
    enableMenuBar(true);
    on_actionStorage_triggered();
}

void MainWindow::loadGame()
{
    // find the load folder
    // give option to select from it
    if(QDir("./save_games").exists())
    {
        qDebug() << "Saved games folder exists.";
        enableMenuBar(true);
        GameInfo::getInstance()->loadGame("");
        on_actionStorage_triggered();
    }
    else
    {
        qDebug() << "Saved games does not exist.";
        // TODO: give warning
    }
}

void MainWindow::saveGame()
{
    // TODO: save a game
    // TODO: create folder if needed.
}

void MainWindow::settings()
{

}

void MainWindow::quit()
{
    QCoreApplication::quit();
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
    switchCentralWidget(new OrganizationStorage);
}

