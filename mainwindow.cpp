#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_centralWidget(nullptr)
{
    ui->setupUi(this);

    MainMenu* menu = new MainMenu(this);
    switchCentralWidget(menu);
    setUpMainMenu(menu);

    GameControl* control = new GameControl(this);
    ui->menubar->setCornerWidget(control);

    // Connect AssetManagement update signals to GameControl's slots to update the labels
    connect(AssetManagement::getInstance(), &AssetManagement::dateChanged, control, &GameControl::updateDateLabel);
    connect(AssetManagement::getInstance(), &AssetManagement::moneyChanged, control, &GameControl::updateMoneyLabel);

    // Connect GameControl advance time button to AssetManagement's time control
    connect(control, &GameControl::advanceTime, AssetManagement::getInstance(), &AssetManagement::advanceGameTime);

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
    if(m_centralWidget) delete m_centralWidget;
    m_centralWidget = newWidget;
}

void MainWindow::setUpMainMenu(MainMenu *menu)
{
    connect(menu, &MainMenu::newGameButtonPressed, this, &MainWindow::newGame);
    connect(menu, &MainMenu::loadGameButtonPressed, this, &MainWindow::loadGame);
    connect(menu, &MainMenu::quitButtonPressed, this, &MainWindow::quit);
    connect(menu, &MainMenu::settingsButtonPressed, this, &MainWindow::settings);
}

void MainWindow::newGame()
{
    // TODO: reset everything to actually a new game (pending assets are saved).
    enableMenuBar(true);
    AssetManagement::getInstance()->setMoney(1000000000); // TODO: make parameter
    AssetManagement::getInstance()->setStartingDate("2023-January-1"); // TODO: make parameter
    on_actionStorage_triggered();
}

void MainWindow::loadGame()
{
    // TODO: find the load folder
    // TODO: give option to select from it
    // TODO: when loading multiple times, the assets increase.
    QDir saveGameFolder = QDir("./save_games");
    QDir saveGame = saveGameFolder.filePath("test");

    if(saveGameFolder.exists())
    {
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


void MainWindow::on_actionNew_game_triggered()
{
    newGame();
}


void MainWindow::on_actionLoad_game_triggered()
{
    loadGame();
}


void MainWindow::on_actionSettings_triggered()
{
    settings();
}


void MainWindow::on_actionQuit_triggered()
{
    quit();
}

