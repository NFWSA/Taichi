#include "flashtext.h"
#include <string>
#include <ege.h>

FlashText::FlashText(const int &times_t, const long &holdtime_t, const std::string &str, const int &arg1, const int &arg2)
    : times(times_t), holdtime(holdtime_t), blurring1(arg1), blurring2(arg2)
{
    pimg = new ege::PIMAGE[times+1];
    for(int i=0; i<=times; ++i)
        pimg[i] = ege::newimage(50, ege::getheight());
    ege::setbkcolor(ege::BLACK, pimg[0]);
    ege::setcolor(ege::WHITE, pimg[0]);
    ege::setfont(38, 0, "Î¢ÈíÑÅºÚ", pimg[0]);
    delayed = -1;
    setText(str);
}

void FlashText::setDelays(const int &delays_t)
{
    delays = delays_t;
}

void FlashText::setText(const std::string &str)
{
    flag = false;
    ready = true;
    index = times+1;
    holds = -1;
    text = str;
    ege::cleardevice(pimg[0]);
    ege::outtextrect(10, 10, 32, ege::getheight()-10, text.c_str(), pimg[0]);
    for(int i=1; i<=times; ++i){
        ege::cleardevice(pimg[i]);
        ege::putimage(pimg[i], 0, 0, pimg[i-1]);
        ege::imagefilter_blurring(pimg[i], blurring1, blurring2);
    }
}

void FlashText::setHoldtime(const long &htime)
{
    holdtime = htime;
}

void FlashText::setBlurring(const int &arg1, const int &arg2)
{
    blurring1 = arg1;
    blurring2 = arg2;
}

void FlashText::setFont(const int &height, const int &width, const std::string &fontName)
{
    ege::setfont(height, width, fontName.c_str(), pimg[0]);
}

void FlashText::setFont(const LOGFONT &fontType)
{
    ege::setfont(&fontType, pimg[0]);
}

void FlashText::setColor(const ege::color_t &clr)
{
    ege::setcolor(clr, pimg[0]);
}

void FlashText::setX(const long &x_t)
{
    x = x_t;
}

int FlashText::getDelays() const
{
    return delays;
}

std::string FlashText::getText() const
{
    return text;
}

long FlashText::getHoldtime() const
{
    return holdtime;
}

void FlashText::getBlurring(int &arg1, int &arg2) const
{
    arg1 = blurring1;
    arg2 = blurring2;
}

void FlashText::getFont(LOGFONT &fontType) const
{
    ege::getfont(&fontType, pimg[0]);
}

ege::color_t FlashText::getColor() const
{
    return ege::getcolor(pimg[0]);
}
long FlashText::getX() const
{
    return x;
}

void FlashText::reDelay()
{
    delayed = -1;
}

bool FlashText::isReady() const
{
    return ready;
}

void FlashText::update()
{
    if(!ready)
        return;
    if(flag){
        if(holds<holdtime){
            ++holds;
            return;
        }
        ++index;
        if(index>times)
            ready = false;
        return;
    }
    else{
        if(delayed<delays){
            ++delayed;
            return;
        }
        --index;
        if(index<0){
            index = 0;
            flag = true;
        }
        return;
    }
}

void FlashText::draw()
{
    if(delayed<delays)
        return;
    if(ready&&index<=times)
        ege::putimage_transparent(NULL, pimg[index], x-10, (ege::getheight()-20*text.size())/2-10, ege::BLACK);
}

FlashText::~FlashText()
{
    for(int i=0; i<=times; ++i)
        ege::delimage(pimg[i]);
    delete[] pimg;
}
