#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
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
    emit quitButtonPressed();
}


void MainMenu::on_NewGameButton_pressed()
{
    emit newGameButtonPressed();
}


void MainMenu::on_LoadGameButton_pressed()
{
    emit loadGameButtonPressed();
}


void MainMenu::on_SettingsButton_pressed()
{
    emit settingsButtonPressed();
}

