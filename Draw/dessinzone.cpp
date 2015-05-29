#include "dessinzone.h"


Dessinzone::Dessinzone(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(100,100);

    color_pen=Qt::black;
    pen_wid=1;
    pen_style=Qt::SolidLine;
    shape_chosen=LINE;
    poly_path=QPainterPath();
    mono_path=QPainterPath();
    is_select=0;
    is_done=0;

    QState* s_select=new QState();
    QState* s_paint=new QState();

    QState* s_mono=new QState(s_paint);
    QState* s_poly=new QState(s_paint);

    QState* s_draw1=new QState(s_poly);
    QState* s_draw2=new QState(s_poly);
    QState* s_draw3=new QState(s_poly);
    QState* s_draw4=new QState(s_poly);

    QState* s1=new QState(s_mono);
    QState* s2=new QState(s_mono);

    QState* s_s1=new QState(s_select);
    QState* s_s2=new QState(s_select);
    QState* s_s3=new QState(s_select);
    QState* s_s4=new QState(s_select);

    dess=new QStateMachine();
    dess->addState(s_paint);
    dess->addState(s_select);

    dess->setInitialState(s_paint);
    s_paint->setInitialState(s_mono);
    s_select->setInitialState(s_s1);
    s_mono->setInitialState(s1);
    s_poly->setInitialState(s_draw1);

    //draw a mono shape
    addMouseTrans(s1,s2,this,QEvent::MouseButtonPress,Qt::LeftButton,
                  this,SLOT(beginDraw()),pos);
    addMouseTrans(s2,s2,this,QEvent::MouseMove,Qt::NoButton,
                  this,SLOT(ajustDraw()),pos);
    addMouseTrans(s2,s1,this,QEvent::MouseButtonRelease,Qt::LeftButton,
                  this,SLOT(endDraw()));


    //draw polygone
    addMouseTrans(s_draw1,s_draw2,this,QEvent::MouseButtonPress,Qt::LeftButton,
                  this,SLOT(beginDraw()),pos);
    addMouseTrans(s_draw2,s_draw2,this,QEvent::MouseMove,Qt::NoButton,
                  this,SLOT(ajustDraw()),pos);

    addMouseTrans(s_draw2,s_draw3,this,QEvent::MouseButtonRelease,Qt::LeftButton,
                  this,SLOT(endDraw()),pos);
    addMouseTrans(s_draw3,s_draw4,this,QEvent::MouseButtonPress,Qt::LeftButton,
                  this,SLOT(newaddLine()),pos);
    addMouseTrans(s_draw4,s_draw4,this,QEvent::MouseMove,Qt::NoButton,
                  this,SLOT(ajustDraw()),pos);
    addMouseTrans(s_draw4,s_draw3,this,QEvent::MouseButtonRelease,Qt::LeftButton,
                  this,SLOT(endDraw()),pos);

    addMouseTrans(s_draw3,s_draw1,this,QEvent::MouseButtonPress,Qt::RightButton,
                  this,SLOT(endaddLine()),pos);

    addTrans(s_mono,s_poly,this,SIGNAL(change_mono_to_poly()));
    addTrans(s_poly,s_mono,this,SIGNAL(change_poly_to_mono()));

    addTrans(s_poly,s_draw1,this,SIGNAL(backoper()));
    addTrans(s_poly,s_draw1,this,SIGNAL(clearoper()));

    //select
    addTrans(s_paint,s_select,this,SIGNAL(select_sig()),this,SLOT(enterselect()));
    addTrans(s_select,s_s1,this,SIGNAL(select_sig()),this,SLOT(enterselect()));
    addMouseTrans(s_s1,s_s2,this,QEvent::MouseButtonPress,Qt::LeftButton,
                  this,SLOT(beginselect()),pos);
    addMouseTrans(s_s2,s_s2,this,QEvent::MouseMove,Qt::NoButton,
                  this,SLOT(ajustselect()),pos);
    addMouseTrans(s_s2,s_s3,this,QEvent::MouseButtonRelease,Qt::LeftButton,
                  this,SLOT(endselect()));
   // addMouseTrans(s_s3,s_s1,this,QEvent::MouseButtonPress,Qt::LeftButton,
    //              this,SLOT(beginselect()),pos);
    addMouseTrans(s_s3,s_s4,this,QEvent::MouseButtonPress,Qt::LeftButton,
                  this,SLOT(beginmove()),pos);
    addMouseTrans(s_s4,s_s4,this,QEvent::MouseMove,Qt::NoButton,
                  this,SLOT(ajustmove()),pos);
    addMouseTrans(s_s4,s_s3,this,QEvent::MouseButtonRelease,Qt::LeftButton);
    addMouseTrans(s_select,s_paint,this,QEvent::MouseButtonPress,Qt::RightButton,
                  this,SLOT(quitselect()));


    dess->start();
}


void Dessinzone::paintEvent(QPaintEvent * e){
    QWidget::paintEvent(e);
    QPainter painter(this);

    //set background
    color_bg=Qt::white;

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background,color_bg);
    this->setPalette(Pal);
    this->setAutoFillBackground(true);

    /*
     * repaint existing lines
     *
     */

    for(int i=0;i<displayList.size();i++){
         if(displayList[i].is_selected==1){
            QPen s_pen(color_pen,pen_wid,pen_style);
            displayList[i].pen=s_pen;
        }

         painter.setPen(displayList[i].pen);
         painter.drawPath(displayList[i]._path);
    }
    QPen pen_n(color_pen,pen_wid,pen_style);
    painter.setPen(pen_n);
    painter.drawPath(poly_path);

    /*
     * to paint a new line
     */

    if(!is_done){

        if(is_select){
            QPen pen_n(Qt::red,1,Qt::DotLine);
            shape_chosen=RECT;
            painter.setPen(pen_n);
        }

        else {
            QPen pen_n(color_pen,pen_wid,pen_style);
            painter.setPen(pen_n);
        }
        painter.drawPath(poly_path);
        mono_path=QPainterPath();

        if(shape_chosen==LINE || shape_chosen==POLYGONE){
            mono_path.moveTo(pos_mouse_b.x(),pos_mouse_b.y());
            mono_path.lineTo(pos_mouse_e.x(),pos_mouse_e.y());
            painter.drawPath(mono_path);
        }
        else if(shape_chosen==RECT){
            QRectF rec_n= QRectF(pos_mouse_b,pos_mouse_e);
            mono_path.addRect(rec_n);
            painter.drawPath(mono_path);
        }
        else if(shape_chosen==OVAL){
            QRectF bounding_rec= QRectF(pos_mouse_b,pos_mouse_e);
            mono_path.addEllipse(bounding_rec);
            painter.drawPath(mono_path);
        }
    }

}
/*
#if IS_USE_SIGNAL
void Dessinzone::mousePressEvent(QMouseEvent * e){
    if(e->button()==Qt::LeftButton){
        pos_mouse_b=e->pos();
        pos_mouse_e=e->pos();
        is_done=0;
        update();
    }
}

void Dessinzone::mouseMoveEvent(QMouseEvent * e){
    pos_mouse_e=e->pos();
    update();
}

void Dessinzone::mouseReleaseEvent(QMouseEvent * e){

    shape shape_temp;
    shape_temp.from=pos_mouse_b;
    shape_temp.to=pos_mouse_e;
    shape_temp.c=color_pen;
    shape_temp.w=pen_wid;
    shape_temp.s=pen_style;
    displayList.append(shape_temp);
    is_done=1;
    update();
}
#endif
*/


void Dessinzone::beginDraw(){


    pos_mouse_b=pos;
    pos_mouse_e=pos;
    is_done=0;

    if(shape_chosen==POLYGONE){
        pos_poly_b=pos;
    }
    update();
}

void Dessinzone::ajustDraw(){
    pos_mouse_e=pos;
    update();
}

void Dessinzone::endDraw(){
    if(shape_chosen==POLYGONE){
        pos_var=pos;
        poly_path.moveTo(pos_mouse_b);
        poly_path.lineTo(pos);
    }
    else{
        shape shape_temp;

        QPen pen_temp(color_pen,pen_wid,pen_style);
        shape_temp.pen=pen_temp;

        shape_temp.is_selected=0;
        // shape_temp.shape_type=shape_chosen;
        shape_temp._path=mono_path;
        displayList.append(shape_temp);
    }

    is_done=1;
    update();
}

void Dessinzone::enterselect(){
    for(int i=0;i<displayList.size();i++){
        displayList[i].is_selected=0;
    }
    update();

}

void Dessinzone::beginselect(){
    select_rect=QRect();
    pos_mouse_b=pos;
    pos_mouse_e=pos;
    is_done=0;
    update();
}

void Dessinzone::ajustselect(){
    pos_mouse_e=pos;
    update();
}

void Dessinzone::endselect(){
    is_done=1;
    select_rect=QRect(pos_mouse_b.x(),pos_mouse_b.y(),pos_mouse_e.x(),pos_mouse_e.y());

    for(int i=0;i<displayList.size();i++){
        if(displayList[i]._path.intersects(select_rect))
        {
            displayList[i].is_selected=1;
        }
    }
    update();

}

void Dessinzone::quitselect(){

    for(int i=0;i<displayList.size();i++){
        displayList[i].is_selected=0;
    }
     is_select=0;
}

void Dessinzone::beginmove(){
    pos_mouse_b=pos;
    update();
}

void Dessinzone::ajustmove(){

    for(int i=0;i<displayList.size();i++){
        if(displayList[i].is_selected==1){
            displayList[i]._path.translate(pos.x()-pos_mouse_b.x(),pos.y()-pos_mouse_b.y());
        }
    }
     pos_mouse_b=pos;
    update();
}


void Dessinzone::newaddLine(){
    pos_mouse_b=pos_var;
    pos_mouse_e=pos;
    is_done=0;
    update();
}

void Dessinzone::endaddLine(){
    if(pos_poly_b!=pos_var){
        poly_path.moveTo(pos_var);
        poly_path.lineTo(pos_poly_b);
        }

        shape shape_temp;

        shape_temp.pen.setColor(color_pen);
        shape_temp.pen.setWidth(pen_wid);
        shape_temp.pen.setStyle(pen_style);
        shape_temp._path=poly_path;
        shape_temp.is_selected=0;
        displayList.append(shape_temp);

        is_done=1;

    poly_path=QPainterPath();

    update();
}

void Dessinzone::setPenColor(int sender){

    if(sender==1){
        color_pen=Qt::black;
    }
    else if(sender==2){
        color_pen=Qt::red;
    }
    else if(sender==3){
        color_pen=Qt::green;
    }
    else if(sender==4){
        color_pen=Qt::blue;
    }
    update();
}

void Dessinzone::setPenWidth(int sender){
    if(sender==1)  pen_wid=1;
    else if(sender==2)   pen_wid=3;
    else if(sender==3)   pen_wid=5;
    update();
}


void Dessinzone::setPenStyle(int sender){
    if(sender==1)  pen_style=Qt::SolidLine;
    else if(sender==2)   pen_style=Qt::DashLine;
    else if(sender==3)   pen_style=Qt::DashDotDotLine;
    update();
}

void Dessinzone::setBackGround(QColor c_b){
    color_bg=c_b;
}

void Dessinzone::back(){
    if(!displayList.isEmpty()){
        displayList.removeLast();
        emit backoper();
        this->update();
    }
}


void Dessinzone::clearall(){
    if(!displayList.isEmpty()){
        displayList.clear();
        emit clearoper();
        this->update();
    }
}

void Dessinzone::shapeDraw(int s){

    if(shape_chosen==POLYGONE && s!=POLYGONE){
        emit change_poly_to_mono();
    }
    else if(shape_chosen!=POLYGONE && s==POLYGONE){
        emit change_mono_to_poly();
    }

    switch(s){
    case 1:
        shape_chosen=LINE; break;
    case 2:
        shape_chosen=RECT; break;
    case 3:
        shape_chosen=OVAL; break;
    case 4:
        shape_chosen=POLYGONE;break;
    default:
        shape_chosen=LINE;
    }
}

void Dessinzone::to_select(){
    pen_var.setColor(color_pen);
    pen_var.setStyle(pen_style);
    pen_var.setWidth(pen_wid);
    is_select=1;
    emit select_sig();
   //cout<<"select";
}

Dessinzone::~Dessinzone(){
      delete dess;

  }

