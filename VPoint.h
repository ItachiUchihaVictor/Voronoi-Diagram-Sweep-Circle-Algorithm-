#ifndef VPoint_h
#define VPoint_h
#include <cmath>
/*
	A structure that stores 2D point
*/

struct VPoint
{
public:
    
	double x, y, tx,ty,angle,r,rc;

	/*
		Constructor for structure; x, y - coordinates
	*/
    VPoint(double nx, double ny,double qx,double qy) 
	{
		x = nx; 
		y = ny;
		tx=qx;
		ty=qy;
		r=std::sqrt((x-qx)*(x-qx)+(y-qy)*(y-qy));
		rc=-1*r;
		if(y>=0 && x==0)angle=90.0;
		else {if(y<=0 && x==0)angle=270.0;
		else{
		angle=atan(y/x) *180.0/3.141592653;
		if(x<0)angle=angle+180.0;
		else{if(angle<0)angle=360.0+angle;}
		}}
	};
	    VPoint(double nx, double ny) 
	{
		x = nx; 
		y = ny;
//		r=sqrt(pow(x-qx,2.0)+pow(y-qy,2.0));
//		angle=GetAngle(x,y);
	};

};
#endif