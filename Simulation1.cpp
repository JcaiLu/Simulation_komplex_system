//====================================================================
// Simulation dynamischer Systeme mit PLAN
//====================================================================
// Projektbeschreibung:
//
//====================================================================
#include <vcl.h>
#pragma hdrstop
#include "Plan.h"
#include "ObjectGroup.h"
#include "SeaFeld.h"




class TUser : public TPlan{

public:

    int GetMW,GetMH;

    SeaFeld Feld;

    
    void Init(){

        GetMW = GetMaxW();
        GetMH = GetMaxH();
        Feld.FeldInit(GetMW,GetMH);
        Reset();
        DrawInit();

        Feld.creatObject(1,1,1);
        //Feld.getObject(1,1).objectDraw(0);

    }

    void Reset(){
        SetPen(Schwarz);SetBrush(Weiss); SetTextSize(30);               // adjust the size and color of the word
        Text((int)(GetMaxW()*0.25),(int)(GetMaxH()*0.05),"Feld of Sea");
    }

    void Run(){


    }

    void DrawInit(){
        SetBrush(TColor(RGB(0,255,255)));
        for(int y = 0; y < Feld.H; y++  ){     //Zeilen
            for(int x = 0; x < Feld.W; x++){          //Spalten
            int ColorDiff =255-(float)y/(float)Feld.H*100;
            SetBrushColor(TColor(RGB(0,ColorDiff,255)));
            SetPenColor(Schwarz);
            //SetPen(TColor(RGB(0,ColorDiff,255)));
                Rectangle(Feld.StartScreenToLeft+x*Feld.PixelW,Feld.StartScreenToTop+y*Feld.PixelW,Feld.PixelW,Feld.PixelW);
            }
        }

    }


 };



//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____



