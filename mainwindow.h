#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "mainmenu.h"
#include "organizationstorage.h"
#include "assetmanagement.h"
#include "gamecontrol.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadGame();
    void newGame();
    void quit();
    void settings();
    void saveGame();

private slots:
    void on_actionStorage_triggered();

    void on_actionSave_game_triggered();

private:
    Ui::MainWindow *ui;

    QWidget* m_centralWidget;

    void enableMenuBar(bool value);
    void switchCentralWidget(QWidget* newWidget);
    void setUpMainMenu(MainMenu* menu);
};
#endif // MAINWINDOW_H
