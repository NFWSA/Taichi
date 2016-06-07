#include "taichi.h"
#include "flashtext.h"
#include <ege.h>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;
const int fps = 60;

int mainloop()
{
    int x = ege::getwidth() / 2, y = ege::getheight() / 2;
    int taichi_r = ( ege::getwidth()>ege::getheight() ? ege::getheight() : ege::getwidth() ) * 22 / 48;
    Taichi taichi(x, y, taichi_r, 360.2);

    ifstream fin("./Taichi.lst", ifstream::in);
    string str;
    FlashText flashtext[12];
    for(int i=0; i<12; ++i){
        flashtext[i].setDelays(120*i);
        flashtext[i].setHoldtime(1080);
        flashtext[i].setColor(ege::DARKGRAY);
        getline(fin, str);
        flashtext[i].setText(str);
    }
    for(int i=0; i<6; ++i)
        flashtext[i].setX(20+i*50);
    for(int i=6; i<12; ++i)
        flashtext[i].setX(taichi_r*2+60+i*50);
    
    //int w = getwidth() * 5 / 12 / (1 + sqrt(2.0));
    ege::setbkcolor(ege::LIGHTGRAY);
    for(; ege::is_run(); ege::delay_fps(fps) ){
        //logical todo:
        taichi.setAngle(taichi.getAngle() - 0.1);
        
        for(int i=0; i<12; ++i){
            flashtext[i].update();
            if(!flashtext[i].isReady()){
                if(!getline(fin, str)){
                    fin.close();
                    fin.clear();
                    fin.open("./Taichi.lst");
                    getline(fin, str);
                }
                flashtext[i].setText(str);
                flashtext[i].update();
            }
        }
        
        //paint todo:
        ege::cleardevice();
        taichi.draw();
        //drawBAGUA(x, y, w, rBAGUA, angle2, 1);
        ege::imagefilter_blurring( nullptr,0xFF,0x100 );
        
        for(int i=0; i<12; ++i)
            if(flashtext[i].isReady())
                flashtext[i].draw();
        
        int key = 0;
        if(ege::kbhit())
            key = ege::getch();
        if(key == ege::key_esc)
            break;
            
    }
}
	
int main()
{
    //setinitmode( INIT_NOFORCEEXIT | INIT_RENDERMANUAL | INIT_TOPMOST );
    ege::setinitmode( ege::INIT_NOFORCEEXIT | ege::INIT_RENDERMANUAL | ege::INIT_NOBORDER | ege::INIT_TOPMOST );
    //initgraph(640, 480);
    ege::initgraph(-1, -1);
    ege::setcaption("EGE involve TAICHI"); 
    ege::ege_enable_aa(true);
    ege::showmouse(0);
	ege::MUSIC bgm;
	bgm.OpenFile("./Taichi.mp3");
	bgm.Play();
    mainloop();
	bgm.Close();
    ege::closegraph();
    return 0;
}
