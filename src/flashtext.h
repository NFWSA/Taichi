#ifndef FLASHTEXT_H
#define FLASHTEXT_H

#include <ege.h>
#include <string>

class FlashText{
private:
    long x, y;
    ege::PIMAGE *pimg;
    std::string text;
    const int times;
    int delays, delayed;
    bool flag, ready;
    long index, holdtime, holds;
    int blurring1, blurring2;
    
public:
    FlashText(const int &times_t = 180, const long &holdtime_t = 120, const std::string &str = "", const int &arg1 = 0x0C, const int &arg2 = 0x100);
    
    void setDelays(const int &delays_t);
    void setText(const std::string &str = "");
    void setHoldtime(const long &htime);
    void setBlurring(const int &arg1, const int &arg2);
    void setFont(const int &height, const int &width, const std::string &fontName);
    void setFont(const LOGFONT &fontType);
    void setColor(const ege::color_t &clr);
    void setX(const long &x_t);
    
    int getDelays() const;
    std::string getText() const;
    long getHoldtime() const;
    void getBlurring(int &arg1, int &arg2) const;
    void getFont(LOGFONT &fontType) const;
    ege::color_t getColor() const;
    long getX() const;
    
    void reDelay();
    bool isReady() const;
    void update();
    void draw();
    
    ~FlashText();

};

#endif //FLASHTEXT_H
