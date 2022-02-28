//--------------------------------------------------------------------------


#include <vcl.h>
#include "Plan.h"
#include "SeaFeld.h"
#include "ObjectGroup.h"

//---------------------------------------------------------------------------

Object::Object(int code){

    SeaFeld *a = new SeaFeld();
    this->LocationInPixel[0] = a->StartScreenToLeft+this->X * a->PixelW;
    this->LocationInPixel[1] = a->StartScreenToTop+this->Y *a->PixelW;
    delete a;
    Code = code;

}


int Object::getX(){
   return X;
}

int Object::getY(){
   return Y;
}

void Object::objectDraw(int ColorNum){
    switch(this->Code){
        case 0: ;
               //SetBrushColor(Schwarz);
               //SetPenColor(Schwarz);
              // Rectangle(this->LocationInPixel[0],this->LocationInPixel[1],20,20);

        case 1: ;//Rectangle(this->LocationInPixel[0],this->LocationInPixel[1],20,20);
               //SetBrushColor(Schwarz);
               //SetPenColor(Schwarz);
    }
}

void Object::detectFeld(){       //

}


void Object::judegObject(){      //

}


bool Object::ifFull(){
        if(this->DegreeFull>0.8){
            return true;
        }else{
            return false;
        }
}


bool Object::ifLive(){
        if(this->DegreeLife>0.8){
            return true;
        }else{
            return false;
        }
}

void Object::objectencode(int t){
    switch(t){
        case 0 : break;
    }
}

void Object::copyOf(Object t,int s){
    this->Code = s;
    switch (this->Code){
        case 0 :{
                for(int i =0;i<20;i++){
                      for(int j = 0;j <20;j++){
                          this->Shape[i][j] = t.ShapeSea[i][j];
                      }
                   }
                 }
        case 1 :{
                 for(int i =0;i<20;i++){
                      for(int j = 0;j <20;j++){
                          this->Shape[i][j] = t.ShapeFish[i][j];
                      }
                  }
                 }
        case 2 :{
                  for(int i =0;i<20;i++){
                      for(int j = 0;j <20;j++){
                          this->Shape[i][j] = t.ShapeBigFish[i][j];
                      }
                    }
                 }
        case 3 :{
                  for(int i =0;i<20;i++){
                      for(int j = 0;j <20;j++){
                          this->Shape[i][j] = t.ShapeHai[i][j];
                      }
                  }
                 }
    }
}


ShapeSea[20][20]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

ShapeFish[20][20]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

ShapeBigFish[20][20]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,
0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,
2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,
2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,
0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,
2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,
2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,
2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,
0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

ShapeHai[20][20]={
0,0,0,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,
3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,
3,3,0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,
3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,
3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,
3,3,0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,
3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,
0,0,0,0,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0};
