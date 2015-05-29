#ifndef DESSINZONE_H
#define DESSINZONE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QColor>
#include <iostream>
#include <QList>
#include <QFinalState>
#include "Transition.h"

using namespace std;
enum Shape {LINE=1, RECT=2, OVAL=3,POLYGONE=4};

class Dessinzone : public QWidget
{
    Q_OBJECT
public:
    explicit Dessinzone(QWidget *parent = 0);
    ~Dessinzone();
    Shape shape_chosen;
    QPainterPath poly_path,mono_path;
    QRect select_rect;

    struct shape{
        QPen pen;
        QPainterPath _path;
        bool is_selected;
    };

    QList<shape> displayList;

protected:
    virtual void paintEvent(QPaintEvent*);
    /*
#if IS_USE_SIGNAL
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
#endif
  */
    QPointF pos_mouse_b,pos_mouse_e;

    QColor color_pen,color_bg;
    int pen_wid;
    Qt::PenStyle pen_style;

    bool is_done,is_select;
    QPoint pos,pos_var,pos_poly_b;
    QStateMachine* dess;
    QPen pen_var;

signals:
    void change_poly_to_mono();
    void change_mono_to_poly();
    void backoper();
    void clearoper();
    void select_sig();

public slots:
    void setPenColor(int);
    void setPenWidth(int);
    void setPenStyle(int);
    void setBackGround(QColor);

    void back();
    void clearall();
    void shapeDraw(int);
    void to_select();


    void beginDraw();
    void ajustDraw();
    void endDraw();
    void newaddLine();
    void endaddLine();

    void beginselect();
    void ajustselect();
    void endselect();
    void quitselect();
    void beginmove();
    void ajustmove();
    void enterselect();

};

#endif // DESSINZONE_H


