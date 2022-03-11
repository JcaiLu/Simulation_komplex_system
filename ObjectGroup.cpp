//--------------------------------------------------------------------------


#include <vcl.h>
#include "Plan.h"
#include "SeaFeld.h"
#include "ObjectGroup.h"

//---------------------------------------------------------------------------
//Initialization the object according to the given code(c) or the
//coordinate(px,py) and given code(c)
//---------------------------------------------------------------------------

Object::Object(int c){
	this->code = c;
	this->GetValueRange();
	this->xInPixel = 0;
	this->yInPixel = 0;
	this->X = 0;
	this->Y = 0;
	this->direction = 1;
	this->RandomDirection();
	this->fishScale = 0;
	memset(this->shape,0,sizeof(this->shape)) ;
}

Object::Object(int px,int py,int c){

	this->code = c;
	this->GetValueRange();
	this->xInPixel = 0;
	this->yInPixel = 0;
	this->X = px;
	this->Y = py;
	this->direction = 1;
	this->RandomDirection();
	this->fishScale = 0;
	memset(this->shape,0,sizeof(this->shape)) ;

}

//---------------------------------------------------------------------------
//The following Function is used to change the relevant range of the object.
//---------------------------------------------------------------------------

void Object::GetValueRange(){         //Set corresponding Value of the range
	switch(this->code){
		case 0:this->detectRange = 0;
			   this->warnRange = 0;
			   this->possibleRange = 0;
			   this->huntRange = 0;
			   break;
		case 1:this->detectRange = 1;
			   this->warnRange = 2;
			   this->possibleRange = 1;
			   this->huntRange = 0;
			   break;
		case 2:this->detectRange = 6;
			   this->warnRange = 6;
			   this->possibleRange = 2;
			   this->huntRange = 1;
			   break;
		case 3:this->detectRange = 14;
			   this->warnRange = 12;
			   this->possibleRange = 3;
			   this->huntRange = 2;
			   break;
	}
}

void Object::GetDetectFeld(){           //detecting Range

	this->GetValueRange();
	int Range = this->detectRange;
	this->detectFeld[0] = this->X - Range;
	this->detectFeld[1] = this->X + Range;
	this->detectFeld[2] = this->Y - Range;
	this->detectFeld[3] = this->Y + Range;
	this->BoundaryTreatment(this->detectFeld);

}

void Object::GetWarnFeld(){            //Warning Range

	this->GetValueRange();
	int Range = this->warnRange;
	this->warnFeld[0] = this->X - Range;
	this->warnFeld[1] = this->X + Range;
	this->warnFeld[2] = this->Y - Range;
	this->warnFeld[3] = this->Y + Range;
	this->BoundaryTreatment(this->warnFeld);

}

void Object::GetHuntFeld(){            //Hunting Range

	this->GetValueRange();
	int Range = this->huntRange;
	this->huntFeld[0] = this->X - Range;
	this->huntFeld[1] = this->X + Range;
	this->huntFeld[2] = this->Y - Range;
	this->huntFeld[3] = this->Y + Range;
	this->BoundaryTreatment(this->huntFeld);

}

void Object::GetPossibleFeld(){        //Possible Range

	this->GetValueRange();
	int Range = this->possibleRange;
	this->possibleFeld[0] = this->X - Range;
	this->possibleFeld[1] = this->X + Range;
	this->possibleFeld[2] = this->Y - Range;
	this->possibleFeld[3] = this->Y + Range;
	this->BoundaryTreatment(this->possibleFeld);
}

//---------------------------------------------------------------------------
//The following Function is used to copy a basic object to this
//Input Type: (int)code
//---------------------------------------------------------------------------

void Object::CopyOf(int t){
	this->code = t;
	switch (this->code){
		case 0 :{
				for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeSea[i][j];
					  }
				   }
				 }
				 break;
		case 1 :{
				 for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeFish[i][j];
					  }
				  }
				 }
				 break;
		case 2 :{
				  for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeBigFish[i][j];
					  }
					}
				 }
				 break;
		case 3 :{
				  for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeHai[i][j];
					  }
				  }
				 }
				 break;
	}
}
//---------------------------------------------------------------------------
//The following Function is  update the Shape of this according to this code
//---------------------------------------------------------------------------

void Object::CodeShapeUpdate(){
	switch (this->code){
		case 0 :{
				for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeSea[i][j];
					  }
				   }
				 }
				 break;
		case 1 :{
				 for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeFish[i][j];
					  }
				  }
				 }
				 break;
		case 2 :{
				  for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeBigFish[i][j];
					  }
					}
				 }
				 break;
		case 3 :{
				  for(int j =0;j<10;j++){
					  for(int i = 0;i <10;i++){
						  this->shape[i][j] = this->shapeHai[i][j];
					  }
				  }
				 }
				 break;
	}
}

//---------------------------------------------------------------------------
//The following Function is  to deal with the problem of the Boundary
//Input Type: array
//---------------------------------------------------------------------------

void Object::BoundaryTreatment(int arr[]){      // this is used to avoid the object run out of SeaFeld

	SeaFeld *a;

	if(arr[0]<0){
		arr[0] = a->w+arr[0];
	}

	if(arr[1]>a->w){
		arr[1] = arr[1] - a->w;
	}

	if(arr[2]<0){
		arr[2] = 0;
	}

	if(arr[3]>0){
		arr[3] = a->h;
	}

	delete a;

}
//---------------------------------------------------------------------------
// The Following Function is used to set a Random Direction to this object.
//
//---------------------------------------------------------------------------
/*
void Object::RandomDirection(){

	int r = 0;
	r = rand()%4;
	this->direction = r;

}
*/
   void Object :: RandomDirection(){
		double r=0.0;
		r=(rand()%3-1)*3.14;
		this->direction =r;
   }

void Object::RandomDirectionLR(){

	int r = 0;
	r = rand()%2+2;
	this->direction = r;

}
//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------

int Object::GetX(){
   return X;
}

int Object::GetY(){
   return Y;
}
void Object::ReadX(int value){
   this->X = value;
}

void Object::ReadY(int value){
   this->Y = value;
}



bool Object::IfFull(){
		if(this->degreeFull>0.8){
			return true;
		}else{
			return false;
		}
}


bool Object::IfLive(){
		if(this->degreeLife>0.8){
			return true;
		}else{
			return false;
		}
}

//---------------------------------------------------------------------------
//The following constants are used to describe the shape of the code
//---------------------------------------------------------------------------
void Object::Rotation(int arr[10][10]){
	int arr2[10][10];
	for(int ai = 0;ai<10;ai++){


		}


}

const int Object::shapeSea[10][10]={
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
};

const int Object::shapeHai[10][10]={
{1,0,0,0,1,1,0,0,0,0},
{1,0,0,1,1,1,1,0,0,0},
{1,0,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,0},
{1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,0},
{1,1,1,1,1,1,1,1,0,0},
{1,0,0,1,1,1,1,0,0,0},
{1,0,0,0,1,1,0,0,0,0},
};

const int Object::shapeBigFish[10][10]={
{0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,1,1,0,0,0,0},
{0,0,0,0,1,1,1,0,0,0},
{1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,1,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0},
};

const int Object::shapeFish[10][10]={
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0},
{1,0,1,1,1,1,0,0,0,0},
{1,1,0,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,0,0,0},
{1,0,0,1,1,1,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
};

