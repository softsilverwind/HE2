#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#define SIZEX 800
#define SIZEY 600

typedef struct Coordinate2d
{
	double x,y;
	Coordinate2d(double x, double y) : x(x), y(y) {};
	Coordinate2d() {};
	Coordinate2d operator+(Coordinate2d second) { return Coordinate2d(x + second.x, y + second.y); }
	Coordinate2d operator-(Coordinate2d second) { return Coordinate2d(x - second.x, y - second.y); }
	Coordinate2d operator/(int second) { return Coordinate2d(x / second, y / second); }
}
Coordinate2d;

typedef struct Coordinate2dPolar
{
	double r,a;
	Coordinate2dPolar() {};
}
Coordinate2dPolar;

typedef struct Coordinate3d
{
	double x,y,z;
	Coordinate3d() {};
	Coordinate3d(double x, double y, double z) : x(x), y(y), z(z) {};
}
Coordinate3d;

typedef struct Color3d
{
	double r,g,b;
	Color3d(double r, double g, double b) : r(r), g(g), b(b) {};
	Color3d() {};
}
Color3d;

typedef enum
{
	        morning, noon, afternoon, rainy, night
}
timeOfDayType;

#endif /* __STRUCTS_H__ */
