#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mainmenu.h"
#include "generalassetform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainMenu* menu = new MainMenu;
    GeneralAssetForm* form = new GeneralAssetForm;

    this->setCentralWidget(form);
}

MainWindow::~MainWindow()
{
    delete ui;
}

