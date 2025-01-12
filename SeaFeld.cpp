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
	for(int i = 0;i < this->matrix.size();i++){
		this->matrix[i].ifmoved = 0;
		this->matrix[i].CodeShapeUpdate();
	}

}

void SeaFeld::Hai(){
	for(int i = 0;i < this->matrix.size();++i){
		 int test  =   this->matrix[5].code;
		if (this->matrix[i].code == 3 ) {       // if not Hai     && this->matrix[i].ifmoved == 0
			this->Target(i);
		}
		this->Move(i);
	}

}


/*
void SeaFeld::Hai(){
	for(int i = 0;i < this->matrix.size();i++){
		if (this->matrix[i].code == 3 && this->matrix[i].ifmoved == 0) {       // if not Hai

			if(this->ifTarget(i)){      //if Hai has target
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
				/////Test
				int dddddd = this->matrix[5].target[0];
					dddddd = this->matrix[5].target[1];
					dddddd = this->matrix[9].code;


			}
			this->Move(i);
		}

	}

}

*/


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


//---------------------------------------------------------------------------
//The following Function SerchNewTarget is used to judge if this object has
// a
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//The following Function SerchNewTarget is used to rewrite the target Information
//of this object.
//---------------------------------------------------------------------------
void SeaFeld::SerchNewTarget(int i){
	this->matrix[i].GetDetectFeld();
	int m1 =  this->matrix[i].detectFeld[0];
	int m2 =  this->matrix[i].detectFeld[1];
	int n1 =  this->matrix[i].detectFeld[2];
	int n2 =  this->matrix[i].detectFeld[3];
	int max = 0;
	int maxX = -1;
	int maxY = -1;
	int codeDiff = 0;

	if(m1 < m2){
		for(int m = m1; m <= m2; m++){
			for(int n = n1; n <= n2; n++){
				codeDiff = this->matrix[i].code - this->GetObjectA(m,n).code;
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
				codeDiff =this->matrix[i].code - this->GetObjectA(m,n).code;
				if(codeDiff == 1 && this->GetObjectA(m,n).fishScale>max){
					max = this->GetObjectA(m,n).fishScale;
					maxX = m;
					maxY = n;
				}
			}
		}
		for(int m = m1; m <= this->w; m++){
			for(int n = n1; n <= n2; n++){
				codeDiff = this->matrix[i].code - this->GetObjectA(m,n).code;
				if(codeDiff == 1 && this->GetObjectA(m,n).fishScale>max){
					max = this->GetObjectA(m,n).fishScale;
					maxX = m;
					maxY = n;
				}
			}
		}
		int num = this->XYIntoNum(this->matrix[i].X,this->matrix[i].Y);       //存入目标坐标值
		this->matrix[num].target[0] = maxX;
		this->matrix[num].target[1] = maxY;

		//根据目标改变的方向目前只有左右
		if(this->matrix[num].target[0]!=-1){
			if(maxX>this->matrix[i].X ){           //目标在自己的右边
				this->matrix[i].direction = 3;
			}else{
				this->matrix[i].direction = 2;    //目标在自己的左边
			}
		}
	}
 }

///////需要补充

//---------------------------------------------------------------------------
//The following Function are used to decide if the object has target
//---------------------------------------------------------------------------
bool SeaFeld::ifTarget(int i){       //if target exist
	if (this->matrix[i].target[1]!=-1) {
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
void SeaFeld::Move(int i){      //Movement


	this->matrix[i].ifmoved =1;

	//test

	int testx = this->matrix[i].target[0];
	int	testy = this->matrix[i].target[1];


	int ddd = this->matrix[1].ifmoved;
	ddd = this->matrix[0].ifmoved;
	ddd = this->matrix[1].ifmoved;
	ddd = this->matrix[2].ifmoved;
	ddd = this->matrix[3].ifmoved;

	if(this->ifTarget(this->matrix[i].X,this->matrix[i].Y)){
		int distancey=this->matrix[i].target[1]-this->matrix[i].Y;
		int distancex=this->matrix[i].target[0]-this->matrix[i].X;
		int ax=this->matrix[i].target[0]-this->w-this->matrix[i].X;
		if (abs(distancex)>abs(ax)) {
		   distancex=ax;
		}
		double s=sqrt(pow(distancex,2)+pow(distancey,2));   //++s=0?
		this->matrix[i].directiond=asin(distancey/s);
		if (distancex<=0) {
			this->matrix[i].directiond =3.14-this->matrix[i].directiond;
		}
		if (s<=this->matrix[i].speed && this->matrix[i].target[0] != -1) {
		   //this->targetEat(i);
		///////Test
		int  ddd = this->matrix[0].ifmoved;
		ddd = this->matrix[1].ifmoved;
		ddd = this->matrix[2].ifmoved;
		ddd = this->matrix[3].ifmoved;
		   this->targetMove(i,s);
		}
	}else{                             //target not exist ==only have direction?direction
		this->noTargetMove(i);
	}


}


//---------------------------------------------------------------------------
//The following Function are used to eat fish of the direction&&move
// to the furthest position
//---------------------------------------------------------------------------

void SeaFeld::noTargetMove(int i ){
	 int a=this->matrix[i].X;
	 int b=this->matrix[i].Y;
	 for (int p = 0; p < this->matrix[i].speed; p++) {
		   a=(int)(cos(this->matrix[i].directiond)+0.5)+a;      //directiond?direction
		   b=(int)(sin(this->matrix[i].directiond)+0.5)+b;
//         a=cos(object.direction)+a;
//		   b=sin(object.direction)+b;

		   if (a<0) {
			   a=a+this->w;
		   }

		   if(b<0){
				b=0;
				int anglet=rand()%2;
				if (anglet==0) {
					this->matrix[i].directiond=-3.14;
				}else{
					this->matrix[i].directiond=3.14;
				}
		   }

		   this->DestoryObject(a,b);
	 }
	  int targetx = a;
	  int targety = b;
	  int targeti = this->XYIntoNum(targetx,targety);

	  this->matrix[targeti].CopyOf(this->matrix[i]);
	  this->matrix[targeti].X = a;
	  this->matrix[targeti].Y = b;

	//  this->matrix[targeti].X = object.target[0];
	//  this->matrix[targeti].Y = object.target[1];
	  this->DestoryObject(this->matrix[i].X,this->matrix[i].Y);
}


//---------------------------------------------------------------------------
//The following Function are used eat the fish of in the target area
//---------------------------------------------------------------------------
void SeaFeld:: targetEat(int num){
	int xmin,xmax,ymin,ymax;
	xmin= this->matrix[num].huntFeld[0];
	xmax= this->matrix[num].huntFeld[1];
	ymin= this->matrix[num].huntFeld[2];
	ymax= this->matrix[num].huntFeld[3];
	int c =0;
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


void SeaFeld::targetMove(int i,double s){
   int a=this->matrix[i].X;
   int b=this->matrix[i].Y;
   for (int p = 0; p < (int)s; p++) {
	   a=(int)(cos(this->matrix[i].directiond)+0.5)+a;
	   b=(int)(sin(this->matrix[i].directiond)+0.5)+b;
	   if (a<0) {
		   a=a+this->w;
	   }
	   if(b<0){
			b=0;
			int anglet=rand()%2;
			if (anglet==0) {
				this->matrix[i].directiond=-3.14;
			}else{
				this->matrix[i].directiond=3.14;
			}

	   }
	   this->DestoryObject(a,b);
	}
	int targeti = this->XYIntoNum(this->matrix[i].target[0],this->matrix[i].target[1]);
	 /////////////////////////

	 int ccc = this->matrix[i].code;

	this->matrix[targeti].CopyOf(this->matrix[i]);
	this->matrix[targeti].X = this->matrix[i].target[0];
	this->matrix[targeti].Y = this->matrix[i].target[1];

	 ccc = this->matrix[i].code;

	int num = this->XYIntoNum(this->matrix[i].target[0],this->matrix[i].target[1]);
	this->matrix[num].target[0] = -1;
	this->matrix[num].target[1] = -1;

	this->DestoryObject(this->matrix[i].X,this->matrix[i].Y);
}

void SeaFeld::RunAway(){

}

void SeaFeld::KeepMoveObject(Object object,const char &c){

}



void SeaFeld::BigFish(){
	for(int i = 0;i < this->matrix.size();i++){
		if(this->matrix[i].code == 2){   // if BigFish
			if(this->Chased(i)==0){
				this->Target(i);
			}
			this->Move(i);

		  }
	}
}


void SeaFeld::Fish(){
	for(int i = 0;i < this->matrix.size();i++){
		if (this->matrix[i].code == 1) {  //if SmallFish
			this->Chased(i);
			this->Move(i);
		}
	}
}




void SeaFeld::Target(int i){
	if(this->ifTarget(i)){
		int tx = this->matrix[i].target[0];
		int ty = this->matrix[i].target[1];
		int m1 = this->GetObjectA(tx,ty).possibleFeld[0];
		int m2 = this->GetObjectA(tx,ty).possibleFeld[1];
		int n1 = this->GetObjectA(tx,ty).possibleFeld[2];
		int n2 = this->GetObjectA(tx,ty).possibleFeld[3];
		int FishScaleMax = 0;
		int maxFishX = -1;
		int maxFishY = -1;

		if(m1<m2){
			for(int m = m1; m <= m2; m++){
				for(int n = n1; n <= n2; n++){
					if(this->GetObjectA(m,n).fishScale>FishScaleMax){
						if(this->GetObjectA(m,n).code <=this->matrix[i].code){
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
						if(this->GetObjectA(m,n).code <=this->matrix[i].code){
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
						if(this->GetObjectA(m,n).code <=this->matrix[i].code){
							FishScaleMax = this->GetObjectA(m,n).fishScale;
							maxFishX = m;
							maxFishY = n;
						}
					}
				}
			}
		}

		if(maxFishX != -1 || maxFishY !=-1){
			this->matrix[i].target[0] = maxFishX;
			this->matrix[i].target[1] = maxFishY;
		}else{
			this->SerchNewTarget(i);
		}

	}else{
		this->SerchNewTarget(i);
	}
}


bool SeaFeld::Chased(int i){
	bool t;
	t = false;
	int tx= this->matrix[i].X;
	int ty= this->matrix[i].Y;
	for (int j = 1; j < this->matrix[i].warnRange; j++) {
		for (int k = -j; k < j; k++) {
			for (int t = -j; t <j; t++) {
				if(ty+t<=0||ty+t>this->h){
					break;
				}
				int numx1 = tx+k+this->w;
				int numx2 = tx+k;
				int numy = ty+t;
				int a = 0;
				if (tx+k<0) {
					a=this->XYIntoNum(numx1,numy);
				}else{
					a=this->XYIntoNum(numx2,numy);
				}
				if (this->matrix[a].code>this->matrix[i].code) {
					double s=sqrt((tx+k)^2+(ty+t)^2);
					double angle=asin((ty+t)/s)+3.14;
					if (k<0) {
						angle=3.14-angle;
					}
					this->matrix[i].directiond=angle;
					return 1;
				}
			}

		 }
	}
	return 0;
}
