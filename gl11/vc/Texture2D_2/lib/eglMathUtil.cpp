#include "eglMathUtil.h"
#include <math.h>

/**************************************************************
 {
 { 2D, 3D Vector Utility
 {
 { 
 {
**************************************************************/
namespace egl {

/* 3D operator */
Vector operator+(const Vector& v1, const Vector& v2)
{
	Vector v( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z );
	return v;
}
Vector operator-(const Vector& v1, const Vector& v2)
{
	Vector v( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z );
	return v;
}
Vector operator*(const Vector& v1, const float factor)
{
	Vector v( v1.x*factor, v1.y*factor, v1.z*factor );
	return v;
}
Vector operator*(const float factor, const Vector& v1)
{
	Vector v( v1.x*factor, v1.y*factor, v1.z*factor );
	return v;
}
Vector operator/(const Vector& v1, float factor)
{
	if( factor == 0.0f )
		factor = 1.0f;

	Vector v( v1.x/factor, v1.y/factor, v1.z/factor );
	return v;
}
Vector operator+=(Vector& v1,const Vector& v2)
{
	v1.x = v1.x + v2.x;
	v1.y = v1.y + v2.y;
	v1.z = v1.z + v2.z;
	return v1;
}
Vector operator-=(Vector& v1,const Vector& v2)
{
	v1.x = v1.x - v2.y;
	v1.y = v1.x - v2.y;
	v1.z = v1.z - v2.z;
	return v1;	
}
float getLength(const Vector& v1)
{
	float length = 0.0f;
	length = (float)sqrt( (v1.x*v1.x) + (v1.y*v1.y) + (v1.z*v1.z) );
	return length;
}
//단위벡터
Vector getUnit(const Vector& v1)
{
	float length = getLength(v1);
	if(length == 0.0f)
		length = 1.0f;

	Vector v( v1.x/length, v1.y/length, v1.z/length );
	return v;
}
//법선벡터구하기
Vector getNormal(const Vector& p1, const Vector& p2, const Vector& p3)
{
	Vector v1(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
	Vector v2(p2.x-p3.x, p2.y-p3.y, p2.z-p3.z);
	Vector v = Cross(v1, v2);
	return getUnit(v);
}
/*Vector getNormal(const Vector& v1, const Vector& v2)
{
	Vector v = Cross(v1, v2);
	return getUnit(v);
}*/
//내적
float	Dot(const Vector& v1, const Vector& v2)
{
	float dot=0.0f;
	
	dot = (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
	return dot;
}
//외적
Vector Cross(const Vector& v1, const Vector& v2)
{
	Vector v( ((v1.y*v2.z) - (v1.z*v2.y)),
		        ((v1.z*v2.x) - (v1.x*v2.z)),
				((v1.x*v2.y) - (v1.y*v2.x)) );
	return v;
}

}; //end of namespace