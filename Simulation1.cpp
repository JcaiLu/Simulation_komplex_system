//====================================================================
// Simulation dynamischer Systeme mit PLAN
//====================================================================
// Projektbeschreibung:
//
//====================================================================
#include <vcl.h>
#pragma hdrstop
#include "Plan.h"
#include "TIntFeld.h"



class TUser : public TPlan {

public:

    TIntFeld Feld;
    int PixelW; //PixelW = PixelH the wide and heigh are the same

    int PlayScreenW,PlayScreenH;
    int StartScreenToLeft;//the distance from the left PlayScreen to the left Frame
    int StartScreenToRight;
    int StartScreenToTop;//the distance from the top PlayScreen to the top Frame
    int StartScreenToBottom;




    void Init(){

        PixelW = 10;
        StartScreenToLeft = (int)(GetMaxW()*0.05);
        StartScreenToRight = (int)(GetMaxW()*0.5);
        StartScreenToTop =(int)(GetMaxH()*0.1);
        StartScreenToBottom =(int)(GetMaxH()*0.05);
        PlayScreenW = (int)((GetMaxW() - StartScreenToLeft - StartScreenToRight)/10);
        PlayScreenH = (int)((GetMaxH() - StartScreenToTop - StartScreenToBottom)/10);
        Feld.Size(PlayScreenW,PlayScreenH);
        SetPen(Schwarz);SetBrush(Weiss); SetTextSize(30);
        Text((int)(GetMaxW()*0.25),(int)(GetMaxH()*0.05),"Feld of Sea"); //��Ҫ���������С

        DrawInit();

    }

    void Reset(){

    }

    void Run(){

    }

    void DrawInit(){

        SetPen(Blau);SetBrush((TColor)(#0000BFFF));

        for(int x = 0; x < PlayScreenW; x++){          //Spalten
            for(int y = 0; y < PlayScreenH; y++  ){     //Zeilen
                Rectangle(StartScreenToLeft+x*PixelW,StartScreenToTop+y*PixelW,PixelW,PixelW);
            }
        }

    }

 };

class PlayFeld : public TIntFeld{


};

class Animal{

enum Richtung{
    left.
    right.


}

private:
       int Code;//the code of animal
       int Shape[10][10]; //the shape of the animal
       double DegreeFull; //the degree of full
       double DegreeLife;//the Degreeof Life


public:


      bool ifFull(){

      }

      bool ifLive(){

      }



};

class Hai : public Animal{    //��Ҫ��Ҫд����ĺ�����

};

class Firsch : public Animal{

};

//====================================================================
#pragma argsused
int main(int argc, char* argv[]){ TUser a; a.Execute(); return 0; }
//__________________________________________________________Ost08_____
