#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QWidget>
#include <QCloseEvent>
#include <QActionGroup>
#include <QRadioButton>
#include <QSignalMapper>
#include <QState>


#include "Transition.h"
#include "dessinzone.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTextEdit* text;
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent*);
    ~MainWindow();
    QStateMachine* shape_mac;

public slots:
    void openFile();
    void saveFile();
    void quitApp();

private:
    Ui::MainWindow *ui;
    Dessinzone* dessinzone;
    /*
    delete openAct;
    delete saveAct;
    delete quitAct;
    delete menuBar;
    delete fileMenu;
    delete QToolBar;
    delete stBar;
    delete color_group;
    delete color_mapper;
    delete p_red;
    delete p_black;
    delete p_blue;
    delete p_green;
    delete penMenu;
    delete width_group;
    delete width_mapper;
    delete p_w1;
    delete p_w3;
    delete p_w5;
    delete style_group;
    delete style_mapper;
    delete solid;
    delete dashdot;
    delete dash;
    delete shape_group;
    delete shape_mapper;
    delete d_l;
    delete d_r;
    delete d_o;
    delete d_polygone;
    delete back;
    delete clear;
    delete shapeMenu;
    delete toolsMenu;
    delete tools;
    delete act_select;
*/
};

#endif // MAINWINDOW_H

