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
    QCoreApplication::quit();
}


void MainMenu::on_NewGameButton_pressed()
{

}


void MainMenu::on_LoadGameButton_pressed()
{

}


void MainMenu::on_SettingsButton_pressed()
{

}

