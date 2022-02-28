//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Plan.h"

#include "SeaFeld.h"
#include "ObjectGroup.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void SeaFeld::FeldInit(int &GetW,int &GetH){
    this->PixelW = 20;
    this->StartScreenToLeft = (int)(GetW*0.05);
    this->StartScreenToRight = (int)(GetW*0.5);
    this->StartScreenToTop =(int)(GetH*0.1);
    this->StartScreenToBottom =(int)(GetH*0.05);
    this->PlayScreenW = (int)((GetW - this->StartScreenToLeft - this->StartScreenToRight)/this->PixelW);
    this->PlayScreenH = (int)((GetH - this->StartScreenToTop - this->StartScreenToBottom)/this->PixelW);
    this->W =  PlayScreenW;
    this->H =  PlayScreenH;
    for(int i = 0;i<this->W*this->H;i++){
        this->Matrix.push_back(Object(0));

    }

}

int SeaFeld::xyIntoNum(int &x,int &y){             // transfer x,y into num of Vector

    int num;
    num = this->W*y + x;
    return num;

}

int SeaFeld::numIntoX(int &num){             // transfer x,y into num of Vector
    int x;
    x = num - this->W*((int)(num/this->W));
    return x;
}

int SeaFeld::numIntoY(int &num){             // transfer x,y into num of Vector
    int y;
    y = num / this->W;
    return y;

}

void SeaFeld::creatObject(int m, int n,int code){  //
     Object f(1);
     int num = this->xyIntoNum(m,n);
     this->Matrix[num].copyOf(f,1);
     
}



Object SeaFeld::getObject(int i, int j){
    int n;
    n = j*this->H +i;
    return this->Matrix.at(n);
}


