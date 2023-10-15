#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_QuitButton_pressed();

    void on_NewGameButton_pressed();

    void on_LoadGameButton_pressed();

    void on_SettingsButton_pressed();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
