#ifndef VECTORUTILS_H_INCLUDED
#define VECTORUTILS_H_INCLUDED

#include <iostream>

using namespace std;

class Point;

class Mat
{
    public:
        Mat();
        Mat(const Mat &m2);
        ~Mat();

        Mat operator*(const Mat &m2);                           // This * 4x4 mat m2.
        void operator*=(const Mat &m2);                         // This = This * 4x4 mat m2.
        Point operator*(const Point &pt);                       // This * homogenous vector pt.
        Point operator*(const Point *pt);                       // This * homogenous vector pt.
        float& operator[](int n);                               // [n] take reference to element n.

        Mat operator+(const Mat &m2);                           // This + m2
        Mat operator-(const Mat &m2);                           // This - m2

        void operator=(const Mat &m2);                           // Copy constructor.

        void makeEye();                         //Construct an identity matrix

        void addTranslate(const Point *pt);     //Add translation to matrix with pt
        void setTranslate(const Point *pt);     //Set translation part of matrix to pt
        void makeTranslate(const Point *pt);    //Make this a translation matrix to pt

        void addScale(const float alpha);       //Multiply scaling alpha onto matrix.
        void makeScale(const float alpha);      //Make this a scale matrix of alpha.

        void makeRotationX(const float angle);
        void rotateX(const float angle);

        void makeRotationY(const float angle);
        void rotateY(const float angle);

        void makeRotationZ(const float angle);
        void rotateZ(const float angle);


        Mat transpose();    //Returns a transpose of this matrix.

        friend ostream& operator<<(ostream& o, const Mat& mat);       // For printing a matrix.

        void switchRows(int r1, int r2);           //Switches the rows r1 and r2.
        Point gaussElimination(const Point &b);    // Returns x that solves A*x = b, when A and b are given.

        float* m;
};

class Indice
{
    public:
        Indice(int i1 = 0, int i2 = 0, int i3 = 0);
        ~Indice();

        //Indice& operator=(const Indice& in);
        Indice(const Indice& in);

        unsigned int* vert; //3 vertex numbers for triangles
};

class Point
{
    public:
        Point();
        Point(const Point &pt);
        Point(int n);
        Point(float x, float y, float z);
        Point(float x, float y, float z, float h);
        ~Point();

        friend ostream& operator<<(ostream& o, const Point& pt);        // For printing points.
        Point& operator=(const Point &p2);                    // Copy constructor.
        float& operator[](int n);                           // [] take element n.
        Point operator+(const Point a);                     // This + vector a.
        Point operator+(float a);                           // This + scalar a.
        Point operator-(const Point a);                     // This - vector a.
        Point operator-(float a);                           // This - scalar a.
        Point operator*(const Point a);                     // This .* vector a.
        Point operator*(float a);                           // This * scalar a.
        float dotProduct(const Point a);                    // This dot a.
        Point crossProduct(const Point a, const Point b);   // a cross b.
        Point crossProduct(const Point a);                  // This cross a.
        Point normalize(const Point a);                     // Normalize a.     (if numel != 4, length will be 1.0f if numel == 4, homogenous normalization.)
        void normalize();                                   // Normalize this.  (if numel != 4, length will be 1.0f if numel == 4, homogenous normalization.)
        Point normalizeAndGet();
        Point negate(Point a);                              // Return negative of a (change a to -a).
        void negate();                                      // Negate this.
        Point negateAndGet();                                      // Negate this.
        void switchElements(int e1, int e2);

        Mat matMult(const Point &a);                        // This * a' -> Mat(numel x numel);

        bool drawing;
        void addToDrawnPoints();

        int numel;          //Number of elements, 4 for homogenous.
        float* coord;     //x,y,z coordinates or u,v for texture coordinates
};

#endif // VECTORUTILS_H_INCLUDED
