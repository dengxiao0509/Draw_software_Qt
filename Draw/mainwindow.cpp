#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(1000,600);
    QAction* openAct=new QAction(QIcon(":/images/open.png"),tr("Open..."),this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setToolTip(tr("Open"));
    openAct->setStatusTip(tr("Open file"));

    QAction* saveAct=new QAction(QIcon(":/images/save.png"),tr("Save..."),this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setToolTip(tr("Save"));
    saveAct->setStatusTip(tr("Save file"));

    QAction* quitAct=new QAction(QIcon(":/images/quit.png"),tr("Quit..."),this);
    quitAct->setShortcut(tr("Ctrl+Q"));
    quitAct->setToolTip(tr("Quit"));
    quitAct->setStatusTip(tr("Quit App"));

    //construct a menubar and add some menu to it
    QMenuBar* menuBar=this->menuBar();
    //add a menu with title to the menubar
    QMenu* fileMenu=menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(quitAct);

    QToolBar* toolBar=this->addToolBar(tr("File"));
    toolBar->addAction(openAct);
    toolBar->addAction(saveAct);
    toolBar->addAction(quitAct);


    /*
    text=new QTextEdit(this);
    setCentralWidget(text);
    */

    dessinzone=new Dessinzone();
    setCentralWidget(dessinzone);

    QStatusBar* stBar=this->statusBar();
    stBar->addAction(openAct);
    stBar->addAction(saveAct);
    stBar->addAction(quitAct);

    connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(quitAct,SIGNAL(triggered()),this,SLOT(quitApp()));

    /***************************************************************
    *************************  Pen Color  **************************
    ***************************************************************/

    QActionGroup* color_group = new QActionGroup(this);
    QSignalMapper* color_mapper = new QSignalMapper(this);

    QAction* p_red=new QAction(tr("red"),color_group);
    //p_red->setShortcut(tr("Ctrl+S"));
    p_red->setToolTip(tr("red"));
    p_red->setStatusTip(tr("Use red pen"));
    p_red->setCheckable(true);
    connect(p_red,SIGNAL(triggered()),color_mapper,SLOT(map()));
    connect(ui->c_red_2,SIGNAL(clicked()),color_mapper,SLOT(map()));

    QAction* p_green=new QAction(tr("green"),color_group);
    //p_red->setShortcut(tr("Ctrl+S"));
    p_green->setToolTip(tr("green"));
    p_green->setStatusTip(tr("Use green pen"));
    p_green->setCheckable(true);
    connect(p_green,SIGNAL(triggered()),color_mapper,SLOT(map()));
    connect(ui->c_green_2,SIGNAL(clicked()),color_mapper,SLOT(map()));

    QAction* p_blue=new QAction(tr("blue"),color_group);
    //p_red->setShortcut(tr("Ctrl+S"));
    p_blue->setToolTip(tr("blue"));
    p_blue->setStatusTip(tr("Use blue pen"));
    p_blue->setCheckable(true);
    connect(p_blue,SIGNAL(triggered()),color_mapper,SLOT(map()));
    connect(ui->c_blue_2,SIGNAL(clicked()),color_mapper,SLOT(map()));

    QAction* p_black=new QAction(tr("black"),color_group);
    //p_red->setShortcut(tr("Ctrl+S"));
    p_black->setToolTip(tr("black"));
    p_black->setStatusTip(tr("Use black pen"));
    p_black->setCheckable(true);
    p_black->setChecked(true);
    connect(p_black,SIGNAL(triggered()),color_mapper,SLOT(map()));
    connect(ui->c_black_2,SIGNAL(clicked()),color_mapper,SLOT(map()));

    QMenu* penMenu=menuBar->addMenu(tr("&Pen setting"));
    penMenu->addSeparator()->setText("Pen color");
    penMenu->addAction(p_black);
    penMenu->addAction(p_red);
    penMenu->addAction(p_green);
    penMenu->addAction(p_blue);

    /*
    QToolBar* colorBar=this->addToolBar(tr("Color"));
    colorBar->addAction(p_black);
    colorBar->addAction(p_red);
    colorBar->addAction(p_green);
    colorBar->addAction(p_blue);
*/
    color_mapper->setMapping(p_black,1);
    color_mapper->setMapping(p_red,2);
    color_mapper->setMapping(p_green,3);
    color_mapper->setMapping(p_blue,4);

    color_mapper->setMapping(ui->c_black_2,1);
    color_mapper->setMapping(ui->c_red_2,2);
    color_mapper->setMapping(ui->c_green_2,3);
    color_mapper->setMapping(ui->c_blue_2,4);

    connect(color_mapper,SIGNAL(mapped(int)),dessinzone,SLOT(setPenColor(int)));

    /***************************************************************
    *************************  Pen Width  **************************
    ***************************************************************/

    QActionGroup* width_group = new QActionGroup(this);
    QSignalMapper* width_mapper = new QSignalMapper(this);

    QAction* p_w1=new QAction(tr("1"),width_group);
    //p_red->setShortcut(tr("Ctrl+S"));
    p_w1->setToolTip(tr("1"));
    p_w1->setStatusTip(tr("Use pen of width 1"));
    p_w1->setCheckable(true);
    p_w1->setChecked(true);
    connect(p_w1,SIGNAL(triggered()),width_mapper,SLOT(map()));
    connect(ui->w_1_2,SIGNAL(clicked()),width_mapper,SLOT(map()));
    ui->w_1_2->setIcon(QIcon(":/images/w_1.png"));

    QAction* p_w3=new QAction(tr("3"),width_group);
    //p_red->setShortcut(tr("Ctrl+S"));
    p_w3->setToolTip(tr("3"));
    p_w3->setStatusTip(tr("Use pen of width 3"));
    p_w3->setCheckable(true);
    connect(p_w3,SIGNAL(triggered()),width_mapper,SLOT(map()));
    connect(ui->w_3_2,SIGNAL(clicked()),width_mapper,SLOT(map()));
    ui->w_3_2->setIcon(QIcon(":/images/w_3.png"));

    QAction* p_w5=new QAction(tr("5"),width_group);
    //p_red->setShortcut(tr("Ctrl+S"));
    p_w5->setToolTip(tr("5"));
    p_w5->setStatusTip(tr("Use pen of width 5"));
    p_w5->setCheckable(true);
    connect(p_w5,SIGNAL(triggered()),width_mapper,SLOT(map()));
    connect(ui->w_5_2,SIGNAL(clicked()),width_mapper,SLOT(map()));
    ui->w_5_2->setIcon(QIcon(":/images/w_5.png"));

    penMenu->addSeparator()->setText("Pen width");
    penMenu->addAction(p_w1);
    penMenu->addAction(p_w3);
    penMenu->addAction(p_w5);
    /*
    QToolBar* widthBar=this->addToolBar(tr("Width"));
    widthBar->addAction(p_w1);
    widthBar->addAction(p_w3);
    widthBar->addAction(p_w5);
*/
    width_mapper->setMapping(p_w1,1);
    width_mapper->setMapping(p_w3,2);
    width_mapper->setMapping(p_w5,3);
    width_mapper->setMapping(ui->w_1_2,1);
    width_mapper->setMapping(ui->w_3_2,2);
    width_mapper->setMapping(ui->w_5_2,3);
    connect(width_mapper,SIGNAL(mapped(int)),dessinzone,SLOT(setPenWidth(int)));

    /***************************************************************
    *************************  Pen Style  **************************
    ***************************************************************/

    QActionGroup* style_group = new QActionGroup(this);
    QSignalMapper* style_mapper = new QSignalMapper(this);

    QAction* solid=new QAction(tr("solid"),style_group);
    solid->setToolTip(tr("solid"));
    solid->setStatusTip(tr("to draw solidline"));
    solid->setCheckable(true);
    solid->setChecked(true);
    connect(solid,SIGNAL(triggered()),style_mapper,SLOT(map()));
    connect(ui->s_solid_2,SIGNAL(clicked()),style_mapper,SLOT(map()));
    //ui->s_solid_2->setIcon(QIcon(":/images/line.png"));


    QAction* dash=new QAction(tr("dash"),style_group);
    dash->setToolTip(tr("dash"));
    dash->setStatusTip(tr("to draw dashline"));
    dash->setCheckable(true);
    connect(dash,SIGNAL(triggered()),style_mapper,SLOT(map()));
    connect(ui->s_dosh_2,SIGNAL(clicked()),style_mapper,SLOT(map()));
    //ui->s_dosh_2->setIcon(QIcon(":/images/dotline.png"));

    QAction* dashdot=new QAction(tr("dashdot"),style_group);
    dashdot->setToolTip(tr("dashdot"));
    dashdot->setStatusTip(tr("to draw dashdotline"));
    dashdot->setCheckable(true);
    connect(dashdot,SIGNAL(triggered()),style_mapper,SLOT(map()));
    connect(ui->s_dashdot_2,SIGNAL(clicked()),style_mapper,SLOT(map()));
    //ui->s_dashdot_2->setIcon(QIcon(":/images/dashdot.png"));

    penMenu->addSeparator()->setText("Pen Style");
    penMenu->addAction(solid);
    penMenu->addAction(dash);
    penMenu->addAction(dashdot);
    /*
    QToolBar* styleBar=this->addToolBar(tr("Style"));
    styleBar->addAction(solid);
    styleBar->addAction(dash);
    styleBar->addAction(dashdot);
*/
    style_mapper->setMapping(solid,1);
    style_mapper->setMapping(dash,2);
    style_mapper->setMapping(dashdot,3);
    style_mapper->setMapping(ui->s_solid_2,1);
    style_mapper->setMapping(ui->s_dosh_2,2);
    style_mapper->setMapping(ui->s_dashdot_2,3);

    connect(style_mapper,SIGNAL(mapped(int)),dessinzone,SLOT(setPenStyle(int)));

    /***************************************************************
    ********************** Geometic form  **************************
    ***************************************************************/

    QActionGroup* shape_group = new QActionGroup(this);
    QSignalMapper* shape_mapper = new QSignalMapper(this);

    QAction* d_l=new QAction(tr("line"),shape_group);
    d_l->setToolTip(tr("line"));
    d_l->setStatusTip(tr("Draw a line"));
    d_l->setCheckable(true);
    d_l->setChecked(true);
    connect(d_l,SIGNAL(triggered()),shape_mapper,SLOT(map()));
    connect(ui->s_line_2,SIGNAL(clicked()),shape_mapper,SLOT(map()));
    ui->s_line_2->setIcon(QIcon(":/images/line.png"));

    QAction* d_r=new QAction(tr("rec"),shape_group);
    d_r->setToolTip(tr("rec"));
    d_r->setStatusTip(tr("Draw a rectangle"));
    d_r->setCheckable(true);
    connect(d_r,SIGNAL(triggered()),shape_mapper,SLOT(map()));
    connect(ui->s_rect_2,SIGNAL(clicked()),shape_mapper,SLOT(map()));
    ui->s_rect_2->setIcon(QIcon(":/images/rec.png"));

    QAction* d_o=new QAction(tr("ellipse"),shape_group);
    d_o->setToolTip(tr("ellipse"));
    d_o->setStatusTip(tr("Draw an ellipse"));
    d_o->setCheckable(true);
    connect(d_o,SIGNAL(triggered()),shape_mapper,SLOT(map()));
    connect(ui->s_ellip_2,SIGNAL(clicked()),shape_mapper,SLOT(map()));
    ui->s_ellip_2->setIcon(QIcon(":/images/ellip.png"));

    /******  to draw polygone **********/
    QAction* d_polygone=new QAction(tr("polygone"),shape_group);
    d_polygone->setToolTip(tr("polygone"));
    d_polygone->setStatusTip(tr("Draw a polygone"));
    d_polygone->setCheckable(true);
    connect(d_polygone,SIGNAL(triggered()),shape_mapper,SLOT(map()));
    connect(ui->s_polygone_2,SIGNAL(clicked()),shape_mapper,SLOT(map()));
    ui->s_polygone_2->setIcon(QIcon(":/images/polygone.png"));

    QMenu* shapeMenu=menuBar->addMenu(tr("&Shape setting"));
    shapeMenu->addSeparator()->setText("Shape to draw");
    shapeMenu->addAction(d_l);
    shapeMenu->addAction(d_r);
    shapeMenu->addAction(d_o);
    shapeMenu->addAction(d_polygone);
    /*
    QToolBar* shapeBar=this->addToolBar(tr("Shape"));
    shapeBar->addAction(d_l);
    shapeBar->addAction(d_r);
    shapeBar->addAction(d_o);
    shapeBar->addAction(d_polygone);
*/

    shape_mapper->setMapping(d_l,1);
    shape_mapper->setMapping(d_r,2);
    shape_mapper->setMapping(d_o,3);
    shape_mapper->setMapping(d_polygone,4);
    shape_mapper->setMapping(ui->s_line_2,1);
    shape_mapper->setMapping(ui->s_rect_2,2);
    shape_mapper->setMapping(ui->s_ellip_2,3);
    shape_mapper->setMapping(ui->s_polygone_2,4);
    connect(shape_mapper,SIGNAL(mapped(int)),dessinzone,SLOT(shapeDraw(int)));

    /***************************************************************
    *************remove the last drawn line and clear all***********
    ***************************************************************/

    // button "back"
    QAction* back=new QAction(QIcon(":/images/back.png.jpg"),tr("Back"),this);
    back->setToolTip(tr("Back"));
    back->setStatusTip(tr("to erase the last drawn line"));
    connect(back,SIGNAL(triggered()),dessinzone,SLOT(back()));

    QAction* clear=new QAction(QIcon(":/images/clear.png"),tr("Clear"),this);
    clear->setToolTip(tr("Clear"));
    clear->setStatusTip(tr("to erase all"));
    connect(clear,SIGNAL(triggered()),dessinzone,SLOT(clearall()));

    QMenu* toolsMenu=menuBar->addMenu(tr("&Tools"));
    toolsMenu->addAction(back);
    toolsMenu->addAction(clear);

    QToolBar* tools=this->addToolBar(tr("Tools"));
    tools->addAction(back);
    tools->addAction(clear);

    /***************************************************************
    **************************  select  ****************************
    ***************************************************************/

    QAction* act_select=new QAction(tr("Select"),this);
    act_select->setToolTip(tr("Select"));
    act_select->setStatusTip(tr("to select one form"));
    connect(act_select,SIGNAL(triggered()),dessinzone,SLOT(to_select()));

    tools->addAction(act_select);

    //***********************piemenu******************************/


}


void MainWindow::openFile(){

    QString filename=
            QFileDialog::getOpenFileName(this,tr("Open file"),
                                         "/home/mylocu/Desktop/inf344/tp1",
                                         tr("All Files(*.*);;Text Files(*.txt);;HTML Files(*.html);;Image Files(*.png *.jpg *.bmp)"));

    const char* f_name = qPrintable(filename);
    cout<<"open "<<f_name<<endl;

    //open a file
    QFile file(f_name);
    //add the contenue of the file opened to a text stream
    if(file.open(QIODevice::ReadOnly)){

        QDataStream in(&file);
        int n;
        in >> n;
        dessinzone->displayList.clear();
        for(int i=0;i<n;i++){
            Dessinzone::shape sh;
            in>> sh.pen;
            in>> sh._path;
            sh.is_selected=0;
            dessinzone->displayList.append(sh);
        }

        //QTextStream in(&file);

        //QString mText=in.readAll();
        //qDebug()<<mText;
        //text->setPlainText(mText);
        //text->setHtml(mText);
        file.flush();
        file.close();
    }
    //else cout<<"Open file error!"<<endl;

}

void MainWindow::saveFile(){
    QString filename=
            QFileDialog::getSaveFileName(this,tr("Save file"),
                                         "/home/mylocu/Desktop/inf344/tp1",
                                         tr("All Files(*.*);;HTML Files(*.html);;Image Files(*.png *.jpg *.bmp);;Text Files(*.txt)"));

    const char* f_name = qPrintable(filename);
    cout<<"save "<<f_name<<endl;
    //open a file
    QFile file(f_name);
    if(file.open(QIODevice::WriteOnly)){

        //QTextStream out(&file);
        //out<<text->toPlainText();
        //get the contenue of the textedit

        QDataStream out(&file);
        out<<dessinzone->displayList.size();

        for(int i=0;i<dessinzone->displayList.size();i++){
            out<< dessinzone->displayList[i].pen;
            out<< dessinzone->displayList[i]._path;
            //text->clear();
        }
        file.flush();
        file.close();
        // else cout<<"Open file error!"<<endl;
    }
}

void MainWindow::quitApp(){
    QMessageBox::StandardButton sb=QMessageBox::question(this,"Confirm","Do you want to quit?",
                                                         QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(sb==QMessageBox::Yes){
        exit(0);
    }

}

void MainWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton sb=QMessageBox::question(this,"Confirm","Do you want to quit?",
                                                         QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(sb==QMessageBox::Yes){
        //  exit(0);
        event->accept();
    }
    else event->ignore();
}

MainWindow::~MainWindow()
{
    delete ui;

}




