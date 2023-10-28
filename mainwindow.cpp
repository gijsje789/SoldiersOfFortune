#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mainmenu.h"
#include "organizationstorage.h"
#include "assetmanagement.h"
#include "gamecontrol.h"

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

    GameControl* control = new GameControl(this);
    ui->menubar->setCornerWidget(control);
    AssetManagement::getInstance()->setGameControl(control);

    ui->menubar->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    AssetManagement::getInstance()->setMoney(1000000000); // TODO: make parameter
    AssetManagement::getInstance()->setStartingDate("2023-January-1"); // TODO: make parameter
    on_actionStorage_triggered();
}

void MainWindow::loadGame()
{
    // find the load folder
    // give option to select from it
    QDir saveGameFolder = QDir("./save_games");
    QDir saveGame = saveGameFolder.filePath("test");
    qDebug() << "Save game: " << saveGame;

    if(saveGameFolder.exists())
    {
        qDebug() << "Saved games folder exists.";
        enableMenuBar(true);
        // TODO: trigger pop-up with available save games
        if(AssetManagement::getInstance()->loadGame(saveGame.path()))
        {
            on_actionStorage_triggered();
        }
        else
        {
            qDebug() << "Could not load game.";
            // TODO: give warning
        }
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
    AssetManagement::getInstance()->saveGame("./save_games/test");
}

void MainWindow::settings()
{

}

void MainWindow::quit()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionStorage_triggered()
{
    switchCentralWidget(new OrganizationStorage);
}


void MainWindow::on_actionSave_game_triggered()
{
    saveGame();
}

