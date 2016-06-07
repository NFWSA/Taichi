#ifndef TAICHI_H
#define TAICHI_H

class Taichi{
private:
    unsigned long x, y, radius;
    double angle;
    
public:
    Taichi(const unsigned long &x_t = 0, const unsigned long &y_t = 0,
          const unsigned long &r_t = 1, const double &angle_t = 0.0);
         
    void setX(const unsigned long &x_t);
    void setY(const unsigned long &y_t);
    void setPos(const unsigned long &x_t, const unsigned long &y_t);
    void setRadius(const unsigned long &r_t);
    void setAngle(const double &angle_t);
    
    unsigned long getX() const;
    unsigned long getY() const;
    void getPos(unsigned long &x_t, unsigned long &y_t) const;
    unsigned long getRadius() const;
    double getAngle() const;
    
    void draw() const;
    
    ~Taichi();
};

class Bagua{
public:
    typedef enum Guaxiang{
        QIAN = 1, KUN = 2, ZHEN = 4, GEN = 8, LI = 16, KAN = 32, DUI = 64, XUN = 128,
        YANG = 0, YIN = -1,
        ALL = 0xFF
    }Guaxiang;
    
private:
    unsigned long x, y;
    unsigned long weight, height, radius;
    double angle;
    
    inline double a2r(const double &angle_t) const;
    void drawYangyao(const unsigned long &x_t, const unsigned long &y_t,
                     const unsigned long &w_t, const double &angle_t, const unsigned long &h_t = 1) const;
    void drawYinyao(const unsigned long &x_t, const unsigned long &y_t,
                     const unsigned long &w_t, const double &angle_t, const unsigned long &h_t = 1) const;
    void drawGuaxiang(const unsigned long &x_t, const unsigned long &y_t,
                     const unsigned long &w_t, const double &angle_t, const unsigned long &h_t, const Guaxiang &gua_type) const;

public:
    Bagua(const unsigned long &x_t = 0, const unsigned long &y_t = 0,
          const unsigned long &w_t = 5, const unsigned long &r_t = 1,
          const double &angle_t = 0.0, const unsigned long &h_t = 1);

    void setX(const unsigned long &x_t);
    void setY(const unsigned long &y_t);
    void setPos(const unsigned long &x_t, const unsigned long &y_t);
    void setWeight(const unsigned long &w_t);
    void setHeight(const unsigned long &h_t);
    void setSize(const unsigned long &w_t, const unsigned long &h_t);
    void setRadius(const unsigned long &r_t);
    void setAngle(const double &angle_t);
    
    unsigned long getX() const;
    unsigned long getY() const;
    void getPos(unsigned long &x_t, unsigned long &y_t) const;
    unsigned long getWeight() const;
    unsigned long getHeight() const;
    void getSize(unsigned long &w_t, unsigned long &h_t) const;
    unsigned long getRadius() const;
    double getAngle() const;
    
    void draw(const Guaxiang &gua_type = ALL) const;
    
    ~Bagua();
};

#endif //TAICHI_H
