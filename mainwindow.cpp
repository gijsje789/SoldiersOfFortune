#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mainmenu.h"
#include "organizationstorage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainMenu* menu = new MainMenu;
    OrganizationStorage* form = new OrganizationStorage;

    this->setCentralWidget(form);
}

MainWindow::~MainWindow()
{
    delete ui;
}

