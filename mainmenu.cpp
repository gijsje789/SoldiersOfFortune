#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent, MainWindow* main) :
    QWidget(parent),
    mainWindow(main),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_QuitButton_pressed()
{
    mainWindow->quit();
}


void MainMenu::on_NewGameButton_pressed()
{
    mainWindow->newGame();
}


void MainMenu::on_LoadGameButton_pressed()
{
    mainWindow->loadGame();
}


void MainMenu::on_SettingsButton_pressed()
{
    mainWindow->settings();
}

