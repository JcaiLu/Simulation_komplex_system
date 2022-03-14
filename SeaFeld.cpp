//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Plan.h"

#include "SeaFeld.h"
#include "ObjectGroup.h"
#include <vector>

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
//The Function FeldInit() is used to initialize a Object with Class SeaFeld.
//The following variable values are given.
//    1) pixelW;    the heigh and the width of each element in SeaFeld.
//    2) startScreenToLeft, startScreenToRight, startScreenToTop,startScreenToBottom
//(This is ez to understand :) )
//    3) playScreenW,playScreenH;    This describes how many rows and columns
//there are in the matrix.
//Input Type: (int)GetMaxW(),(int)GetMaxH()
//---------------------------------------------------------------------------

void SeaFeld::FeldInit(int &getW,int &getH){
	this->pixelW = 10;
	this->startScreenToLeft = (int)(getW*0.05);
	this->startScreenToRight = (int)(getW*0.5);
	this->startScreenToTop =(int)(getH*0.1);
	this->startScreenToBottom =(int)(getH*0.05);
	this->playScreenW = (int)((getW - this->startScreenToLeft - this->startScreenToRight)/this->pixelW);
	this->playScreenH = (int)((getH - this->startScreenToTop - this->startScreenToBottom)/this->pixelW);
	this->w = playScreenW;
	this->h = playScreenH;
}

//---------------------------------------------------------------------------
//The Function InitObject() is used to initialize the object in the matrix
//
//Beside all the object is initialized to the "Sea",the following variable
//values are also given.
//    1) x,y;  the coordiate of this object
//---------------------------------------------------------------------------

void SeaFeld::InitObject(){
	Object initObject(0);
	for(int j = 0; j < this->h; j++){          //initiazation the position of each element
		for(int i = 0; i < this->w; i++){
			//int k = this->XYIntoNum(i,j);
			initObject.xInPixel = this->startScreenToLeft+i*this->pixelW;
			initObject.yInPixel = this->startScreenToTop+j*this->pixelW;
			initObject.X = i;
			initObject.Y = j;
			initObject.w = this->w;
			initObject.h = this->h;
			this->matrix.push_back(initObject);
		}
	}

}

//---------------------------------------------------------------------------
//The Function Update() is the main and the most important program. It descirbes
//the flow chart of our Rules.
//  最重要的地方
//---------------------------------------------------------------------------
void SeaFeld::Update(){

	this->Hai();
	//this->BigFish();
	//this->Fish();
}

void SeaFeld::Hai(){
	for(int i = 0;i < this->matrix.size();i++){
		if (this->matrix[i].code == 3) {       // if not Hai
			if(this->ifHaveTarget(this->matrix[i])){      //if Hai has target
				int tx = this->matrix[i].target[0];
				int ty = this->matrix[i].target[1];
				int m1 = this->GetObjectA(tx,ty).possibleFeld[0];
				int m2 = this->GetObjectA(tx,ty).possibleFeld[1];
				int n1 = this->GetObjectA(tx,ty).possibleFeld[2];
				int n2 = this->GetObjectA(tx,ty).possibleFeld[3];
				int FishScaleMax = 0;
				int maxFishX = 0;
				int maxFishY = 0;

				if(m1<m2){
					for(int m = m1; m <= m2; m++){
						for(int n = n1; n <= n2; n++){
							if(this->GetObjectA(m,n).fishScale>FishScaleMax){
								if(this->GetObjectA(m,n).code == 1 ||this->GetObjectA(m,n).code == 2){
									FishScaleMax = this->GetObjectA(m,n).fishScale;
									maxFishX = m;
									maxFishY = n;
								}
							}
						}
					}
				}else if(m1>m2){
					for(int m = 0; m <= m2; m++){
						for(int n = n1; n <= n2; n++){
							if(this->GetObjectA(m,n).fishScale>FishScaleMax){
								if(this->GetObjectA(m,n).code == 1 ||this->GetObjectA(m,n).code == 2){
									FishScaleMax = this->GetObjectA(m,n).fishScale;
									maxFishX = m;
									maxFishY = n;
								}
							}
						}

					}
					for(int m = m1; m <= this->w; m++){
						for(int n = n1; n <= n2; n++){
							if(this->GetObjectA(m,n).fishScale>FishScaleMax){
								if(this->GetObjectA(m,n).code == 1 ||this->GetObjectA(m,n).code == 2){
									FishScaleMax = this->GetObjectA(m,n).fishScale;
									maxFishX = m;
									maxFishY = n;
								}
							}
						}

					}
				}

				if(maxFishX != 0 && maxFishY !=0){
					this->matrix[i].target[0] = maxFishX;
					this->matrix[i].target[1] = maxFishY;
				}else{
					this->SerchNewTarget(this->matrix[i]);
				}


			}else{
				this->SerchNewTarget(this->matrix[i]);
				//this->Move(this->matrix[i]);

			}
			this->Move(this->matrix[i]);

		}

	}

}


void SeaFeld::BigFish(){
    	for(int i = 0;i < this->matrix.size();i++){
		if(this->matrix[i].code == 2){   // if BigFish
		//////////////////////////////////
			int m1 =  this->matrix[i].warnFeld[0];
			int m2 =  this->matrix[i].warnFeld[1];
			int n1 =  this->matrix[i].warnFeld[2];
			int n2 =  this->matrix[i].warnFeld[3];
			for(int m = m1; m <= m2;m++){
				for (int n = n1; i <= n2; n++) {
					if(this->GetObjectA(m,n).code);
				}
			}
		//////////////////////////////////
		}
	}

	for(int i = 0;i < this->matrix.size();i++){
		if(this->matrix[i].code == 1){    // if SmallFish

		}
	}



}


void SeaFeld::Fish(){



}
//---------------------------------------------------------------------------
//The following three Function are used to translate the X,Y to the Nummer of
//the Vector.
// Why?   Because this Vector is 1D, but the Matrix is 2D.
//Function GetObject() can be used to get a object at x,y.
//---------------------------------------------------------------------------

int SeaFeld::XYIntoNum(int &x,int &y){             // transfer x,y into num of Vector

    int num;
    num = this->w*y + x;
    return num;

}

int SeaFeld::NumIntoX(int &num){             // transfer x,y into num of Vector
    int x;
    x = num - this->w*((int)(num/this->w));
    return x;
}

int SeaFeld::NumIntoY(int &num){             // transfer x,y into num of Vector
    int y;
    y = num / this->w;
    return y;

}

Object SeaFeld::GetObject(int i, int j){
	int n = 0;
	n = j*this->w +i;
	return this->matrix[n];
}
//---------------------------------------------------------------------------
//The following Function are used to creat or destory a object according to
// the code in the SeaFeld.
//---------------------------------------------------------------------------
void SeaFeld::CreatObject(int m, int n,int code,int dir,int scale){  //
	 int num = this->XYIntoNum(m,n);
	 this->matrix[num].CopyOf(code);
	 this->matrix[num].direction = dir;
	 this->matrix[num].fishScale = scale;
	 this->matrix[num].GetValueRange();
	 this->matrix[num].GetHuntFeld();
	 this->matrix[num].GetPossibleFeld();
	 this->matrix[num].GetWarnFeld();
	 this->matrix[num].GetDetectFeld();
}

void SeaFeld::DestoryObject(int m,int n){
	 int num = this->XYIntoNum(m,n);
	 this->matrix[num].CopyOf(0);
}

void SeaFeld::DestoryObject(int num){
	 this->matrix[num].CopyOf(0);

}

//---------------------------------------------------------------------------
//The following Function are used to realize a Movement of a object according
//to the given direction.
//---------------------------------------------------------------------------
/*
void SeaFeld::Move(Object object){      //Movement

	int distancey=object.target[1]-object.Y;
	int distancex=object.target[0]-object.X;
	int ax=object.target[0]-this->w-object.X;
	if (abs(distancex)>abs(ax)) {
	   distancex=ax;
	}
	int s=sqrt(distancex^2+distancey^2);
	object.directiond=asin(distancey/s);
	if (distancex<=0) {
		object.directiond=3.14-object.directiond;
	}

	bool flag=0;
	if(object.target[1]>=0){
		if (s<=object.speed) {
		   flag=1;      //target exist && in this updata catch the target
		}
	}

	// eat the target range
	if (flag==1) {
		int xmin,xmax,ymin,ymax;
		xmin= object.possibleFeld[0];
		xmax= object.possibleFeld[1];
		ymin= object.possibleFeld[2];
		ymax= object.possibleFeld[3];

		if (xmax<xmin) {
		   for(int j = ymin; j<=ymax;j++ ){
				for(int i = xmin;i<=w;i++){
					this->DestoryObject(i,j);
				}
				for(int i = 0;i<=xmax;i++){
					this->DestoryObject(i,j);
				}
			}
		}else{
			for(int j = ymin; j<=ymax;j++ ){
				for(int i = xmin;i<=xmax;i++){
					this->DestoryObject(i,j);
				}
			}
		}
	 }

	 int a=object.X;
	 int b=object.Y;
	 int imax=0;
	 if (flag==1) {
			imax =(int)s;     //++++++++++++++
	 }else{
		  imax=object.speed;
	  }
	 for (int p = 0; p < imax; p++) {
		   a=(int)(cos(object.directiond)+0.5)+a;
		   b=(int)(sin(object.directiond)+0.5)+b;
		   if (a<0) {
			   a=a+this->w;
		   }
		   if(b<0){
				b=0;
				int anglet=rand()%2;
				if (anglet==0) {
					object.directiond=-3.14;
				}else{
					object.directiond=3.14;
                }
		   }

		   this->DestoryObject(a,b);
	 }
	  int targetx = object.target[0];
	  int targety = object.target[1];
	  int targeti = this->XYIntoNum(targetx,targety);

	  this->matrix[targeti].CopyOf(object);
	  this->matrix[targeti].X = a;
	  this->matrix[targeti].Y = b;
	  this->DestoryObject(object.X,object.Y);
}


*/

void SeaFeld::MoveObject(Object object,const char &c){
	
}

//---------------------------------------------------------------------------
//The following Function SerchNewTarget is used to judge if this object has
// a
//---------------------------------------------------------------------------


bool SeaFeld::ifHaveTarget(const Object &object){

	int tx,ty;
	bool ifThis = false;
	tx = object.target[0];
	ty = object.target[1];

	if( tx >= 0 && tx <= this->w && ty >= 0 && ty <= this->h){
		ifThis = true;
	}else if(tx==0 & ty ==0){
		ifThis = false;
	}
	return ifThis;

}

//---------------------------------------------------------------------------
//The following Function SerchNewTarget is used to rewrite the target Information
//of this object.
//---------------------------------------------------------------------------
void SeaFeld::SerchNewTarget(Object object){
	object.GetDetectFeld();
	int m1 =  object.detectFeld[0];
	int m2 =  object.detectFeld[1];
	int n1 =  object.detectFeld[2];
	int n2 =  object.detectFeld[3];
	int max = 0;
	int maxX = 0;
	int maxY = 0;
	int codeDiff = 0;
	
	if(m1 < m2){
		for(int m = m1; m <= m2; m++){
			for(int n = n1; n <= n2; n++){
				codeDiff = object.code - this->GetObjectA(m,n).code;
				if(codeDiff == 1 && this->GetObjectA(m,n).fishScale>max){
					max = this->GetObjectA(m,n).fishScale;
					maxX = m;
					maxY = n;
				}		
			}
		}
	}else if(m1>m2){
		for(int m = 0; m <= m2; m++){
			for(int n = n1; n <= n2; n++){
				codeDiff = object.code - this->GetObjectA(m,n).code;
				if(codeDiff == 1 && this->GetObjectA(m,n).fishScale>max){
					max = this->GetObjectA(m,n).fishScale;
					maxX = m;
					maxY = n;
				}		
			}
		}
		for(int m = m1; m <= this->w; m++){
			for(int n = n1; n <= n2; n++){
				codeDiff = object.code - this->GetObjectA(m,n).code;
				if(codeDiff == 1 && this->GetObjectA(m,n).fishScale>max){
					max = this->GetObjectA(m,n).fishScale;
					maxX = m;
					maxY = n;
				}		
			}
		}
		int num = this->XYIntoNum(object.X,object.Y);
		this->matrix[num].target[0] = maxX;
		this->matrix[num].target[1] = maxY;

		//根据目标改变的方向目前只有左右
		if(maxX>object.X){           //目标在自己的右边
			object.direction = 3;
		}else{
			object.direction = 2;    //目标在自己的左边
		}
	}
}

///////需要补充

//---------------------------------------------------------------------------
//The following Function are used to decide if the object has target
//---------------------------------------------------------------------------
bool SeaFeld::ifTarget(int i){       //if target exist
	if (this->matrix[i].target[1]>=0) {
		return 1;
	}else{
		return 0;
	}
}
bool SeaFeld::ifTarget(int x,int y){       //if target exist
	int i = this->XYIntoNum(x,y);
	if (this->matrix[i].target[1]>=0) {
		return 1;
	}else{
		return 0;
	}
}


//---------------------------------------------------------------------------
//The following Function are used to realize a Movement of a object according
//to the given direction.
//---------------------------------------------------------------------------
void SeaFeld::Move(Object object){      //Movement

	if(this->ifTarget(object.X,object.Y)){
		int distancey=object.target[1]-object.Y;
		int distancex=object.target[0]-object.X;
		int ax=object.target[0]-this->w-object.X;
		if (abs(distancex)>abs(ax)) {
		   distancex=ax;
		}
		float s=sqrt(distancex^2+distancey^2);   //++s=0?
		object.directiond=asin(distancey/s);
		if (distancex<=0) {
			object.directiond=3.14-object.directiond;
		}
		if (s<=object.speed) {
		   this->targetEat(object);
		   this->targetMove(object,s);
		}
	}else{                             //target not exist ==only have direction?direction
		this->noTargetMove(object);
	}
}


//---------------------------------------------------------------------------
//The following Function are used to eat fish of the direction&&move
// to the furthest position
//---------------------------------------------------------------------------

void SeaFeld::noTargetMove(Object object ){
     int a=object.X;
	 int b=object.Y;
	 for (int p = 0; p < object.speed; p++) {
		   a=(int)(cos(object.directiond)+0.5)+a;      //directiond?direction
		   b=(int)(sin(object.directiond)+0.5)+b;
//         a=cos(object.direction)+a;
//		   b=sin(object.direction)+b;

		   if (a<0) {
			   a=a+this->w;
		   }
		   if(b<0){
				b=0;
				int anglet=rand()%2;
				if (anglet==0) {
					object.directiond=-3.14;
				}else{
					object.directiond=3.14;
				}
		   }

		   this->DestoryObject(a,b);
	 }
	  int targetx = object.target[0];
	  int targety = object.target[1];
	  int targeti = this->XYIntoNum(targetx,targety);

	  this->matrix[targeti].CopyOf(object);
	  this->matrix[targeti].X = a;
	  this->matrix[targeti].Y = b;

	//  this->matrix[targeti].X = object.target[0];
	//  this->matrix[targeti].Y = object.target[1];
	  this->DestoryObject(object.X,object.Y);
}


//---------------------------------------------------------------------------
//The following Function are used eat the fish of in the target area
//---------------------------------------------------------------------------
void SeaFeld:: targetEat(Object object){
	int xmin,xmax,ymin,ymax;
	xmin= object.possibleFeld[0];
	xmax= object.possibleFeld[1];
	ymin= object.possibleFeld[2];
	ymax= object.possibleFeld[3];
	if (xmax<xmin) {
	   for(int j = ymin; j<=ymax;j++ ){
			for(int i = xmin;i<=w;i++){
				this->DestoryObject(i,j);
			}
			for(int i = 0;i<=xmax;i++){
				this->DestoryObject(i,j);
			}
		}
	}else{
		for(int j = ymin; j<=ymax;j++ ){
			for(int i = xmin;i<=xmax;i++){
				this->DestoryObject(i,j);
			}
		}
	}
}

//---------------------------------------------------------------------------
//The following Function are used eat the fish eat fish of the direction&&move
// to the target position&&move to the target position
//---------------------------------------------------------------------------
void SeaFeld::targetMove(Object object,double s){
   int a=object.X;
   int b=object.Y;
   for (int p = 0; p < (int)s; p++) {
	   a=(int)(cos(object.directiond)+0.5)+a;
	   b=(int)(sin(object.directiond)+0.5)+b;
	   if (a<0) {
		   a=a+this->w;
	   }
	   if(b<0){
			b=0;
			int anglet=rand()%2;
			if (anglet==0) {
				object.directiond=-3.14;
			}else{
				object.directiond=3.14;
			}
	   }
	   this->DestoryObject(a,b);
	}
	int targetx = object.target[0];
	int targety = object.target[1];
	int targeti = this->XYIntoNum(targetx,targety);

	this->matrix[targeti].CopyOf(object);
	this->matrix[targeti].X = object.target[0];
	this->matrix[targeti].Y = object.target[1];
    this->DestoryObject(object.X,object.Y);
}

void SeaFeld::RunAway(){

}

void SeaFeld::KeepMoveObject(Object object,const char &c){

}

