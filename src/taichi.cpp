#include "taichi.h"
#include <ege.h>
#include <cmath>

/******************************************************************Taichi realize******************************************************************/

Taichi::Taichi(const unsigned long &x_t, const unsigned long &y_t, const unsigned long &r_t, const double &angle_t)
    : x(x_t), y(y_t), radius(r_t)
{
    setRadius(angle_t);
}

void Taichi::setPos(const unsigned long &x_t, const unsigned long &y_t)
{
    x = x_t;
    y = y_t;
}

void Taichi::setRadius(const unsigned long &r_t)
{
    radius = r_t;
}

void Taichi::setAngle(const double &angle_t)
{
    angle = angle_t;
    for(; angle>=360.0; angle-=360.0);  //empty loop
    for(; angle<0.0; angle+=360.0); //empty loop
}

unsigned long Taichi::getX() const
{
    return x;
}

unsigned long Taichi::getY() const
{
    return y;
}

void Taichi::getPos(unsigned long &x_t, unsigned long &y_t) const
{
    x_t = x;
    y_t = y;
}

unsigned long Taichi::getRadius() const
{
    return radius;
}

double Taichi::getAngle() const
{
    return angle;
}

void Taichi::draw() const
{
    ege::color_t cl = ege::getcolor(), fillcl = ege::getfillcolor();
    int r1 = radius, r2 = radius / 2.0, r3 = 0.15 * radius;
    double radian = angle * ege::PI / 180.0;
    int x1 = x, y1 = y;
    int x2w = x1 - r2 * std::sin(radian), y2w = y1 - r2 * std::cos(radian);
    int x2b = x1 + r2 * std::sin(radian), y2b = y1 + r2 * std::cos(radian);
    int xl1 = x1 + r1 * std::sin(radian), yl1 = y1 + r1 * std::cos(radian);
    int xl2 = x1 - r1 * std::sin(radian), yl2 = y1 - r1 * std::cos(radian);
    int fx = x1 + r2 * std::cos(radian), fy = y1 - r2 * std::sin(radian);
    ege::setcolor(ege::BLACK);
    ege::setfillcolor(ege::WHITE);
    ege::fillellipse(x1, y1, r1, r1);
    ege::line(xl1, yl1, xl2, yl2);
    ege::setfillcolor(ege::BLACK);
    ege::floodfill(fx, fy, ege::BLACK);
    ege::fillellipse(x2b, y2b, r2, r2);
    ege::setcolor(ege::WHITE);
    ege::setfillcolor(ege::WHITE);
    ege::fillellipse(x2w, y2w, r2, r2);
    ege::fillellipse(x2b, y2b, r3, r3);
    ege::setcolor(ege::BLACK);
    ege::setfillcolor(ege::BLACK);
    ege::fillellipse(x2w, y2w, r3, r3);
    ege::circle(x1, y1, r1);
    ege::setcolor(cl);
    ege::setfillcolor(fillcl);
}

Taichi::~Taichi()
{

}

/******************************************************************Bagua realize******************************************************************/

inline double Bagua::a2r(const double &angle_t) const
{
    return angle_t * ege::PI / 180.0;
}

void Bagua::drawYangyao(const unsigned long &x_t, const unsigned long &y_t,
                     const unsigned long &w_t, const double &angle_t, const unsigned long &h_t) const
{
    double r = w_t / 10 * std::sqrt(26.0);
    double angle1 = angle_t + std::asin( 5 / std::sqrt(26.0) ),
           angle2 = angle_t - std::asin( 5 / std::sqrt(26.0) );
    if(angle1 >= ege::PI * 2)
        angle1 -= ege::PI * 2;
    if(angle2 >= ege::PI * 2)
        angle2 -= ege::PI * 2;
    int pt[] = {
        x_t + r * std::cos(angle1), y_t + r * std::sin(angle1),
        x_t - r * std::cos(angle2), y_t - r * std::sin(angle2),
        x_t - r * std::cos(angle1), y_t - r * std::sin(angle1),
        x_t + r * std::cos(angle2), y_t + r * std::sin(angle2)
    };
    ege::color_t clr = ege::getcolor(), flclr = ege::getfillcolor();
    ege::setcolor(ege::BLACK);
    ege::setfillcolor(ege::BLACK);
    ege::fillpoly(4, pt);
    ege::setcolor(clr);
    ege::setfillcolor(flclr);
}

void Bagua::drawYinyao(const unsigned long &x_t, const unsigned long &y_t,
                     const unsigned long &w_t, const double &angle_t, const unsigned long &h_t) const
{
    //double r = w / 10 * sqrt(2.0);
    double r = w_t / 50 * std::sqrt(72.0);
    double angle1 = angle_t + std::asin( 5 / std::sqrt(72.0) ),
           angle2 = angle_t - std::asin( 5 / std::sqrt(72.0) );
    if(angle1 >= ege::PI * 2)
        angle1 -= ege::PI * 2;
    if(angle2 >= ege::PI * 2)
        angle2 -= ege::PI * 2;
    int pt[] = {
        x_t + r * std::cos(angle1), y_t + r * std::sin(angle1),
        x_t - r * std::cos(angle2), y_t - r * std::sin(angle2),
        x_t - r * std::cos(angle1), y_t - r * std::sin(angle1),
        x_t + r * std::cos(angle2), y_t + r * std::sin(angle2)
    };
    drawYangyao(x_t, y_t, w_t, angle_t, h_t);
    ege::color_t clr = ege::getcolor(), flclr = ege::getfillcolor();
    ege::setcolor(ege::getbkcolor());
    ege::setfillcolor(ege::getbkcolor());
    ege::fillpoly(4, pt);
    ege::setcolor(clr);
    ege::setfillcolor(flclr);
}

void Bagua::drawGuaxiang(const unsigned long &x_t, const unsigned long &y_t,
                           const unsigned long &w_t, const double &angle_t, const unsigned long &h_t, const Guaxiang &gua_type) const
{
    
    double r = w_t * 4.0 / 15.0;
    int xh = x_t + r * std::cos(angle_t), yh = y_t + r * std::sin(angle_t),
        xl = x_t - r * std::cos(angle_t), yl = y_t - r * std::sin(angle_t);
    switch(gua_type){
        case QIAN:
            drawYangyao(xh, yh, w_t, angle_t);
            drawYangyao(x_t, y_t, w_t, angle_t);
            drawYangyao(xl, yl, w_t, angle_t);
            break;
        case KUN:
            drawYinyao(xh, yh, w_t, angle_t);
            drawYinyao(x_t, y_t, w_t, angle_t);
            drawYinyao(xl, yl, w_t, angle_t);
            break;
        case ZHEN:
            drawYinyao(xh, yh, w_t, angle_t);
            drawYinyao(x_t, y_t, w_t, angle_t);
            drawYangyao(xl, yl, w_t, angle_t);
            break;
        case GEN:
            drawYangyao(xh, yh, w_t, angle_t);
            drawYinyao(x_t, y_t, w_t, angle_t);
            drawYinyao(xl, yl, w_t, angle_t);
            break;
        case LI:
            drawYangyao(xh, yh, w_t, angle_t);
            drawYinyao(x_t, y_t, w_t, angle_t);
            drawYangyao(xl, yl, w_t, angle_t);
            break;
        case KAN:
            drawYinyao(xh, yh, w_t, angle_t);
            drawYangyao(x_t, y_t, w_t, angle_t);
            drawYinyao(xl, yl, w_t, angle_t);
            break;
        case DUI:
            drawYinyao(xh, yh, w_t, angle_t);
            drawYangyao(x_t, y_t, w_t, angle_t);
            drawYangyao(xl, yl, w_t, angle_t);
            break;
        case XUN:
            drawYangyao(xh, yh, w_t, angle_t);
            drawYangyao(x_t, y_t, w_t, angle_t);
            drawYinyao(xl, yl, w_t, angle_t);
            break;
    }
}

Bagua::Bagua(const unsigned long &x_t, const unsigned long &y_t,
      const unsigned long &w_t, const unsigned long &r_t,
      const double &angle_t, const unsigned long &h_t)
    : x(x_t), y(y_t), weight(w_t), radius(r_t), height(h_t)
{
    if( 1==height && 5!=weight )
        height = weight / 5.0;
    setAngle(angle_t);
}

void Bagua::setX(const unsigned long &x_t)
{
    x = x_t;
}

void Bagua::setY(const unsigned long &y_t)
{
    y = y_t;
}

void Bagua::setPos(const unsigned long &x_t, const unsigned long &y_t)
{
    x = x_t;
    y = y_t;
}

void Bagua::setWeight(const unsigned long &w_t)
{
    weight = w_t;
}

void Bagua::setHeight(const unsigned long &h_t)
{
    height = h_t;
}

void Bagua::setSize(const unsigned long &w_t, const unsigned long &h_t)
{
    weight = w_t;
    height = h_t;
}

void Bagua::setRadius(const unsigned long &r_t)
{
    radius = r_t;
}

void Bagua::setAngle(const double &angle_t)
{
    angle = angle_t;
    for(; angle>=360.0; angle-=360.0);  //empty loop
    for(; angle<0.0; angle+=360.0); //empty loop
}

unsigned long Bagua::getX() const
{
    return x;
}

unsigned long Bagua::getY() const
{
    return y;
}

void Bagua::getPos(unsigned long &x_t, unsigned long &y_t) const
{
    x_t = x;
    y_t = y;
}

unsigned long Bagua::getWeight() const
{
    return weight;
}

unsigned long Bagua::getHeight() const
{
    return height;
}

void Bagua::getSize(unsigned long &w_t, unsigned long &h_t) const
{
    w_t = weight;
    h_t = height;
}

unsigned long Bagua::getRadius() const
{
    return radius;
}

double Bagua::getAngle() const
{
    return angle;
}

void Bagua::draw(const Guaxiang &gua_type) const
{
    switch(gua_type){
        case YIN:
            drawYinyao(x, y, weight, angle, height);
            return;
        case YANG:
            drawYangyao(x, y, weight, angle, height);
            return;
        case QIAN: case KUN: case LI: case KAN:
        case ZHEN: case GEN: case DUI: case XUN:
            drawGuaxiang(x, y, weight, angle, height, gua_type);
            return;
        default:
            break;
    }
    
}

//正在施工中...
/******************************



void drawBAGUA(int x, int y, int w, int r, int angle, int choice)
{
    double l = r + w * 11.0 / 30.0;
    Guaxiang gua[8];
    if(choice == 1){
        gua[0] = QIAN;
        gua[1] = XUN;
        gua[2] = KAN;
        gua[3] = GEN;
        gua[4] = KUN;
        gua[5] = ZHENG;
        gua[6] = LI;
        gua[7] = DUI;
    }
    if(choice == 2){
        gua[0] = QIAN;
        gua[1] = XUN;
        gua[2] = KAN;
        gua[3] = GEN;
        gua[4] = KUN;
        gua[5] = ZHENG;
        gua[6] = LI;
        gua[7] = DUI;
    }
    double a[] = {
        a2r(angle), a2r(angle + 45),
        a2r(angle + 90), a2r(angle + 135),
        a2r(angle + 180), a2r(angle + 225),
        a2r(angle + 270), a2r(angle + 315)
    };
    for(int i = 0; i < 8; ++i)
        if(a[i] >= PI * 2)
            a[i] -= PI * 2;
    int gx[8];
    int gy[8];
    for(int i = 0; i < 8; ++i){
        gx[i] = x + l * cos(a[i]);
        gy[i] = y + l * sin(a[i]);
    }
    for(int i = 0; i < 8; ++i){
        drawGUA(gx[i], gy[i], w, a[i], gua[i]);
    }
    return;
}
******************************/

Bagua::~Bagua()
{

}
