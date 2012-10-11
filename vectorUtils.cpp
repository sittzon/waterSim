#include "vectorUtils.h"
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

Mat::Mat()
{
    m = new float[16];
    for(int i = 0; i<16 ; i++) { m[i] = 0.0f; }
}

Mat::Mat(const Mat &m2)
{
    m = new float[16];
    for(int i = 0; i<16 ; i++) { m[i] = m2.m[i]; }
}

Mat::~Mat()
{
    if(m != NULL)
    {
        //delete m; //Throws error- glibc detected : invalid pointer
        m = NULL;
    }
}

Mat Mat::operator*(const Mat &m2)
{
    Mat* out = new Mat();
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            out->m[4*r + c] =   m[4*r]   * m2.m[c]   + m[4*r+1] * m2.m[c+4] +
                                m[4*r+2] * m2.m[c+8] + m[4*r+3] * m2.m[c+12];
        }
    }

	return *out;
}

void Mat::operator*=(const Mat &m2)
{
    Mat newMat = *new Mat();
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            newMat[4*r + c] =   m[4*r]  *  m2.m[c]   + m[4*r+1] * m2.m[c+4] +
                                m[4*r+2] * m2.m[c+8] + m[4*r+3] * m2.m[c+12];
        }
    }

    m[ 0] = newMat[ 0];    m[ 1] = newMat[ 1];    m[ 2] = newMat[ 2];    m[ 3] = newMat[ 3];
    m[ 4] = newMat[ 4];    m[ 5] = newMat[ 5];    m[ 6] = newMat[ 6];    m[ 7] = newMat[ 7];
    m[ 8] = newMat[ 8];    m[ 9] = newMat[ 9];    m[10] = newMat[10];    m[11] = newMat[11];
    m[12] = newMat[12];    m[13] = newMat[13];    m[14] = newMat[14];    m[15] = newMat[15];

    return;
}


Point Mat::operator*(const Point &pt)
{
    Point out = *new Point(0.0f, 0.0f, 0.0f, 0.0f);

    out[0] = m[ 0]*pt.coord[0] + m[ 1]*pt.coord[1] + m[ 2]*pt.coord[2] + m[ 3]*pt.coord[3];
    out[1] = m[ 4]*pt.coord[0] + m[ 5]*pt.coord[1] + m[ 6]*pt.coord[2] + m[ 7]*pt.coord[3];
    out[2] = m[ 8]*pt.coord[0] + m[ 9]*pt.coord[1] + m[10]*pt.coord[2] + m[11]*pt.coord[3];
    out[3] = m[12]*pt.coord[0] + m[13]*pt.coord[1] + m[14]*pt.coord[2] + m[15]*pt.coord[3];

	return out;
}


Point Mat::operator*(const Point *pt)
{
    Point out = *new Point(0.0f, 0.0f, 0.0f, 0.0f);

    out[0] = m[ 0]*pt->coord[0] + m[ 1]*pt->coord[1] + m[ 2]*pt->coord[2] + m[ 3]*pt->coord[3];
    out[1] = m[ 4]*pt->coord[0] + m[ 5]*pt->coord[1] + m[ 6]*pt->coord[2] + m[ 7]*pt->coord[3];
    out[2] = m[ 8]*pt->coord[0] + m[ 9]*pt->coord[1] + m[10]*pt->coord[2] + m[11]*pt->coord[3];
    out[3] = m[12]*pt->coord[0] + m[13]*pt->coord[1] + m[14]*pt->coord[2] + m[15]*pt->coord[3];

	return out;
}

float& Mat::operator[](int n)
{
    return m[n];
}


Mat Mat::operator+(const Mat &m2)
{
    Mat newMat = *new Mat();
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            newMat[4*r + c] =   m[4*r + c] + m2.m[4*r + c];
        }
    }
    return newMat;
};

Mat Mat::operator-(const Mat &m2)
{
    Mat newMat = *new Mat();
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            newMat[4*r + c] =   m[4*r + c] - m2.m[4*r + c];
        }
    }
    return newMat;
};


void Mat::operator=(const Mat &m2)
{
    m[ 0] = m2.m[ 0]; m[ 1] = m2.m[ 1]; m[ 2] = m2.m[ 2]; m[ 3] = m2.m[ 3];
    m[ 4] = m2.m[ 4]; m[ 5] = m2.m[ 5]; m[ 6] = m2.m[ 6]; m[ 7] = m2.m[ 7];
    m[ 8] = m2.m[ 8]; m[ 9] = m2.m[ 9]; m[10] = m2.m[10]; m[11] = m2.m[11];
    m[12] = m2.m[12]; m[13] = m2.m[13]; m[14] = m2.m[14]; m[15] = m2.m[15];
    return;
}

void Mat::makeEye()
{
    m[ 0] = 1.0f; m[ 1] = 0.0f; m[ 2] = 0.0f; m[ 3] = 0;
    m[ 4] = 0.0f; m[ 5] = 1.0f; m[ 6] = 0.0f; m[ 7] = 0;
    m[ 8] = 0.0f; m[ 9] = 0.0f; m[10] = 1.0f; m[11] = 0;
    m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

void Mat::addTranslate(const Point *pt)
{
    m[ 3] += pt->coord[0];
    m[ 7] += pt->coord[1];
    m[11] += pt->coord[2];
}

void Mat::setTranslate(const Point *pt)
{
    m[ 3] = pt->coord[0];
    m[ 7] = pt->coord[1];
    m[11] = pt->coord[2];
}


void Mat::makeTranslate(const Point *pt)
{
    m[ 0] = 1.0f; m[ 1] = 0.0f; m[ 2] = 0.0f; m[ 3] = pt->coord[0];
    m[ 4] = 0.0f; m[ 5] = 1.0f; m[ 6] = 0.0f; m[ 7] = pt->coord[1];
    m[ 8] = 0.0f; m[ 9] = 0.0f; m[10] = 1.0f; m[11] = pt->coord[2];
    m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;

    // Alt.
    //makeEye();
    //addTranslate(pt);
    return;
}

void Mat::addScale(const float alpha)
{
    m[ 0] *= alpha;    m[ 1] *= alpha;    m[ 2] *= alpha;
    m[ 4] *= alpha;    m[ 5] *= alpha;    m[ 6] *= alpha;
    m[ 8] *= alpha;    m[ 9] *= alpha;    m[10] *= alpha;
    return;
}
void Mat::makeScale(const float alpha)
{
    m[ 0] = alpha; m[ 1] = 0.0f;  m[ 2] = 0.0f;  m[ 3] = 0.0f;
    m[ 4] = 0.0f;  m[ 5] = alpha; m[ 6] = 0.0f;  m[ 7] = 0.0f;
    m[ 8] = 0.0f;  m[ 9] = 0.0f;  m[10] = alpha; m[11] = 0.0f;
    m[12] = 0.0f;  m[13] = 0.0f;  m[14] = 0.0f;  m[15] = 1.0f;

    //Alt.
    //makeEye();
    //addScale(alpha);
    return;
}

void Mat::makeRotationX(const float angle)
{
    m[ 0] = 1.0f;   m[ 1] = 0.0f;           m[ 2] = 0.0f;           m[ 3] = 0.0f;
    m[ 4] = 0.0f;   m[ 5] = cos(angle);     m[ 6] = -sin(angle);    m[ 7] = 0.0f;
    m[ 8] = 0.0f;   m[ 9] = sin(angle);     m[10] = cos(angle);     m[11] = 0.0f;
    m[12] = 0.0f;   m[13] = 0.0f;           m[14] = 0.0f;           m[15] = 1.0f;
}
void Mat::rotateX(const float angle)
{
    Mat temp = Mat();
    temp.makeRotationX(angle);
    *this = temp*(*this);
}

void Mat::makeRotationY(const float angle)
{
    m[ 0] = cos(angle);     m[ 1] = 0.0f;  m[ 2] = sin(angle);      m[ 3] = 0.0f;
    m[ 4] = 0.0f;           m[ 5] = 1.0f;  m[ 6] = 0.0f;            m[ 7] = 0.0f;
    m[ 8] = -sin(angle);    m[ 9] = 0.0f;  m[10] = cos(angle);      m[11] = 0.0f;
    m[12] = 0.0f;           m[13] = 0.0f;  m[14] = 0.0f;            m[15] = 1.0f;
}
void Mat::rotateY(const float angle)
{
    Mat temp = Mat();
    temp.makeRotationY(angle);
    *this = temp*(*this);
}

void Mat::makeRotationZ(const float angle)
{
    m[ 0] = cos(angle);     m[ 1] = -sin(angle);    m[ 2] = 0.0f;   m[ 3] = 0.0f;
    m[ 4] = sin(angle);     m[ 5] = cos(angle);     m[ 6] = 0.0f;   m[ 7] = 0.0f;
    m[ 8] = 0.0f;           m[ 9] = 0.0f;           m[10] = 1.0f;   m[11] = 0.0f;
    m[12] = 0.0f;           m[13] = 0.0f;           m[14] = 0.0f;   m[15] = 1.0f;
}
void Mat::rotateZ(const float angle)
{
    Mat temp = Mat();
    temp.makeRotationZ(angle);
    *this = temp*(*this);
}

Mat Mat::transpose()
{
    Mat newMat = *new Mat();

    newMat[ 0] = m[ 0]; newMat[ 1] = m[ 4]; newMat[ 2] = m[ 8]; newMat[ 3] = m[12];
    newMat[ 4] = m[ 1]; newMat[ 5] = m[ 5]; newMat[ 6] = m[ 9]; newMat[ 7] = m[13];
    newMat[ 8] = m[ 2]; newMat[ 9] = m[ 6]; newMat[10] = m[10]; newMat[11] = m[14];
    newMat[12] = m[ 3]; newMat[13] = m[ 7]; newMat[14] = m[11]; newMat[15] = m[15];

    return newMat;
}

ostream& operator<<(ostream& o, const Mat& mat)
{
    o << endl << "[";

    for (int r = 0 ; r < 4 ; ++r)
    {
        o << endl << "  [" << setw(13) << mat.m[r*4];

        for (int c = 1 ; c < 4 ; ++c)
        {
            o << ", " << setw(13) << mat.m[r*4 + c];
        }

        o << "]";
    }

    o << endl << "]";

    return o;
}

void Mat::switchRows(int r1, int r2)
{
    float tmp1 = m[0 + 4*r1];
    float tmp2 = m[1 + 4*r1];
    float tmp3 = m[2 + 4*r1];
    float tmp4 = m[3 + 4*r1];

    m[0 + 4*r1] = m[0 + 4*r2];
    m[1 + 4*r1] = m[1 + 4*r2];
    m[2 + 4*r1] = m[2 + 4*r2];
    m[3 + 4*r1] = m[3 + 4*r2];

    m[0 + 4*r2] = tmp1;
    m[1 + 4*r2] = tmp2;
    m[2 + 4*r2] = tmp3;
    m[3 + 4*r2] = tmp4;

    return;
}

// Returns x that solves A*x = b, when A and b are given.
Point Mat::gaussElimination(const Point &b)
{
    // Multiplication factors.
    Mat mults = *new Mat();

    // Copy this mat to A;
    Mat A = *new Mat();
    A = *this;

    //Copy n to x
    Point x = *new Point(4);
    x = b;

    int rowOrder[4] = {0, 1, 2, 3};

    int n = 0;
    int temp = 0;
    int r1 = 0;
    int r2 = 0;


//
//    cout << endl << "Starting A matrix: " << endl;
//    cout << A << endl;
//    cout << "b vector: " << b << endl;
//    cout << "x vector: " << x << endl;

    for(int k = 0; k < 4; ++k)
    {
        //Check if element is zero
        if(m[k + 4*k] == 0.0f)
        {
            //Change row order until element i, i isn't zero.
            n = 0;
            while(A[k + 4*k] == 0.0f)
            {
                n++;
                r1 = k;
                r2 = k+n;

                if(r2 >= 4)
                {
                    cout << "Matrix is singular, no Gauss elimination could be done!" << endl;
                    cout << *this << endl;
                    cout << "Failed in row " << k << endl;
                    cout << "A mat: " << endl << A << endl;
                    break;
                }

                A.switchRows(r1, r2);
                x.switchElements(r1, r2);

                // Keep track of rowchanges.
                temp = rowOrder[r1];
                rowOrder[r1] = rowOrder[r2];
                rowOrder[r2] = temp;
            }

        }

        for(int i = k+1; i < 4; ++i) // Rows
        {
            mults[k + 4*i] = A[k + 4*i]/A[k + 4*k];
        }
//
//        cout << "Multiplications mat:" << endl;
//        cout << mults << endl;

        for(int i = k+1; i < 4; ++i) // Rows.
        {
            for(int j = k; j < 4; ++j) // Collumns
            {
                A[j + i*4] -= mults[k + 4*i]*A[j + 4*k];
            }
//            cout << " : " << x[i];
            x[i] -= mults[k + 4*i]*x[k];
//            cout << " - " << mults[k + 4*i] << " * " << x[k] <<  " = " << x[i] << endl;
        }
//
//        cout << "A matrix: " << endl;
//        cout << A << endl;
//        cout << "x vector: " << x << endl;
//        cout << "Row order:" << rowOrder[0] << ", " << rowOrder[1] << ", " << rowOrder[2] << ", " << rowOrder[3] << endl;
//        cout << endl << endl;

    }

    // Switch back elements in x.
    for(int i = 0; i < 3; ++i) // Last element is ok if the others are.
    {
        // If wrong order, switch.
        if(rowOrder[i] != i)
        {
            x.switchElements(i, i+1);
                temp = rowOrder[i];
                rowOrder[i] = rowOrder[i+1];
                rowOrder[i+1] = temp;
        }
    }

    // Here A is a right triangular matrix;

    for(int k = 3; k >= 0 ; k--)
    {

        for(int i = k + 1; i < 4 ; i++) // Collumns
        {
            x[k] -= x[i]* A[i + 4*k];
        }

        x[k] = x[k] / A[k + 4*k];
    }
//
//    cout << "Result: " << x << endl;
//
//    cout << "b = " << b << endl << "A*x = " << (*this)*x << endl;

    return x;

}

// ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ Indice ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

Indice::Indice(int i1, int i2, int i3)
{
    vert = new unsigned int[3];

    vert[0] = i1;
    vert[1] = i2;
    vert[2] = i3;

//    cout  << "Number: "<< nr << " Created!" << endl;

}

Indice::~Indice()
{
    delete[] vert;
    vert = NULL;

//    cout << "Number: "<< nr <<" Deleted!!" << endl;
}

Indice::Indice(const Indice &in)
{
    vert = new unsigned int[3];

    vert[0] = in.vert[0];
    vert[1] = in.vert[1];
    vert[2] = in.vert[2];

//    cout << "New Number: " << nr << " Copied from " << in.nr << endl;
}

// ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ Point ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

Point::Point()
{
    numel = 3;
    coord = new float[3];
    drawing = false;
}

Point::Point(const Point &pt)
{
    numel = pt.numel;
    coord = new float[numel];
    drawing = false;

    for(int n = 0 ; n < numel ; ++n)
    {
        coord[n] = pt.coord[n];
    }
}

Point::Point(int n)
{
    numel = n;
    coord = new float[n];
    drawing = false;
}

Point::Point(float x, float y, float z)
{
    numel = 3;
    coord = new float[3];
    drawing = false;
    coord[0] = x; coord[1] = y; coord[2] = z;
}

Point::Point(float x, float y, float z, float h)
{
    numel = 4;
    coord = new float[4];
    drawing = false;
    coord[0] = x; coord[1] = y; coord[2] = z; coord[3] = h;
}

Point::~Point()
{
    if(drawing)
    {
        //getGlobal()->DPH->removePoint(this);
    }

    if(coord != NULL)
    {
        delete coord;
        coord = NULL;
    }
}

ostream& operator<<(ostream& o, const Point& pt)
{
    o << "["  << setw(13) << pt.coord[0];

    for (int n = 1 ; n < pt.numel ; ++n)
    {
        o << ", " << setw(13) << pt.coord[n];
    }

    o << "]";

    return o;
}

Point& Point::operator=(const Point &p2)
{
    // Copy the first values from p2 change size if necessary.
    if(numel != p2.numel)
    {
        numel = p2.numel;
        coord = new float[numel];
    }

    for(int n = 0 ; n < numel ; ++n)
    {
        coord[n] = p2.coord[n];
    }

    return *this;
}

float& Point::operator[](int n)
{
    return coord[n];
}

Point Point::operator+(const Point a)
{
    Point out = *new Point(numel);//Point out;
    out.coord[0] = coord[0] + a.coord[0];
    out.coord[1] = coord[1] + a.coord[1];

    if(numel >=3 && a.numel >=3)
    {
        out.coord[2] = coord[2] + a.coord[2];
        if(numel == 4 && a.numel == 4)
        {
            out.coord[3] = coord[3] + a.coord[3];
        }
    }

    return out;
}
Point Point::operator+(float a)
{
    Point out = *new Point(numel);//Point out;
    out.coord[0] = coord[0] + a;
    out.coord[1] = coord[1] + a;

    if(numel >=3)
    {
        out.coord[2] = coord[2] + a;
        if(numel == 4)
        {
            out.coord[3] = coord[3] + a;
        }
    }
    return out;
}
Point Point::operator-(const Point a)
{
    Point out = *new Point(numel);//Point out;
    out.coord[0] = coord[0] - a.coord[0];
    out.coord[1] = coord[1] - a.coord[1];

    if(numel >=3 && a.numel >=3)
    {
        out.coord[2] = coord[2] - a.coord[2];

        if(numel == 4 && a.numel == 4)
        {
            out.coord[3] = coord[3] - a.coord[3];
        }
    }
    return out;
}
Point Point::operator-(float a)
{
    Point out = *new Point(numel);//Point out;
    out.coord[0] = coord[0] - a;
    out.coord[1] = coord[1] - a;

    if(numel >=3)
    {
        out.coord[2] = coord[2] - a;
        if(numel == 4)
        {
            out.coord[3] = coord[3] - a;
        }
    }
    return out;
}
Point Point::operator*(const Point a)
{
    Point out = *new Point(numel);//Point out;
    out.coord[0] = coord[0] * a.coord[0];
    out.coord[1] = coord[1] * a.coord[1];

    if(numel >=3 && a.numel >=3)
    {
        out.coord[2] = coord[2] * a.coord[2];

        if(numel == 4 && a.numel == 4)
        {
            out.coord[3] = coord[3] * a.coord[3];
        }
    }
    return out;
}
Point Point::operator*(float a)
{
    Point out = *new Point(numel);//Point out;
    out.coord[0] = coord[0] * a;
    out.coord[1] = coord[1] * a;

    if(numel >=3)
    {
        out.coord[2] = coord[2] * a;
        if(numel == 4)
        {
            out.coord[3] = coord[3] * a;
        }
    }
    return out;
}
float Point::dotProduct(const Point a)
{
    float out = 0.0f;

    if(numel >= 2)
    {
        out = coord[0] * a.coord[0] + coord[1] * a.coord[1];
        if(numel >= 3)
        {
            out += coord[2] * a.coord[2];
            if(numel >= 4)
            {
                out += coord[3] * a.coord[3];
            }
        }
    }

    return out;
}
Point Point::crossProduct(const Point a, const Point b)
{
    Point tempPoint = *new Point(3);
    tempPoint.coord[0] = a.coord[1]*b.coord[2] - a.coord[2]*b.coord[1];
    tempPoint.coord[1] = a.coord[2]*b.coord[0] - a.coord[0]*b.coord[2];
    tempPoint.coord[2] = a.coord[0]*b.coord[1] - a.coord[1]*b.coord[0];
    return tempPoint;
}

Point Point::crossProduct(const Point a)
{
    Point tempPoint = *new Point(3);
    tempPoint.coord[0] = coord[1]*a.coord[2] - coord[2]*a.coord[1];
    tempPoint.coord[1] = coord[2]*a.coord[0] - coord[0]*a.coord[2];
    tempPoint.coord[2] = coord[0]*a.coord[1] - coord[1]*a.coord[0];
    return tempPoint;
}

Point Point::normalize(Point a)
{
    float divider = 1.0f;

    if(numel == 4)
    {
        divider = a[3];
    }
    else
    {
        divider = sqrt(a.coord[0]*a.coord[0]+a.coord[1]*a.coord[1]+a.coord[2]*a.coord[2]);
    }

    a.coord[0] = a.coord[0]/divider;
    a.coord[1] = a.coord[1]/divider;
    a.coord[2] = a.coord[2]/divider;
    return a;
}

void Point::normalize()
{
    float divider = 1.0f;

    if(numel == 4)
    {
        divider = coord[3];
        coord[3] = 1.0f;
    }
    else
    {
        divider = sqrt(coord[0]*coord[0]+coord[1]*coord[1]+coord[2]*coord[2]);
    }

    coord[0] = coord[0]/divider;
    coord[1] = coord[1]/divider;
    coord[2] = coord[2]/divider;
}

Point Point::normalizeAndGet()
{
    normalize();
    return *this;
}

Point Point::negate(Point a)
{
    a.coord[0] = -a.coord[0];
    a.coord[1] = -a.coord[1];
    a.coord[2] = -a.coord[2];
    return a;
}

void Point::negate()
{
    coord[0] = -coord[0];
    coord[1] = -coord[1];
    coord[2] = -coord[2];
}

Point Point::negateAndGet()
{
    negate();
    return *this;
}

 void Point::switchElements(int e1, int e2)
 {
     float temp = coord[e1];
     coord[e1] = coord[e2];
     coord[e2] = temp;

     return;
 }

Mat Point::matMult(const Point &a)
{
     Mat res;
     if(numel == 4 && a.numel == 4)
     {
        res[ 0] = coord[0] * a.coord[0]; res[ 1] = coord[0] * a.coord[1]; res[ 2] = coord[0] * a.coord[2]; res[ 3] = coord[0] * a.coord[3];
        res[ 4] = coord[1] * a.coord[0]; res[ 5] = coord[1] * a.coord[1]; res[ 6] = coord[1] * a.coord[2]; res[ 7] = coord[1] * a.coord[3];
        res[ 8] = coord[2] * a.coord[0]; res[ 9] = coord[2] * a.coord[1]; res[10] = coord[2] * a.coord[2]; res[11] = coord[2] * a.coord[3];
        res[12] = coord[3] * a.coord[0]; res[13] = coord[3] * a.coord[1]; res[14] = coord[3] * a.coord[2]; res[15] = coord[3] * a.coord[3];
     }
     else
     {
         cout << "Unable to comply... matMult needs homogenous points.";
     }

     return res;
}

void Point::addToDrawnPoints()
{
    drawing = true;
    //getGlobal()->DPH->addPoint(this);
    return;
}


