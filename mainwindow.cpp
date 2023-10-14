#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mainmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainMenu* menu = new MainMenu;

    this->setCentralWidget(menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

