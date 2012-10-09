
#ifndef BMPREADER_CPP
#define BMPREADER_CPP

#include <fstream>
#include <iostream>

#include "vectorUtils.h"
#include "bmpReader.h"

using namespace std;

bmpReader::bmpReader()
{

}

void bmpReader::read(string filename)
{
    fstream input;
    input.open(filename.c_str());

    ofstream output;
    output.open("ut.txt");

    if(input.good())
    {
        int row = 0;
        int col = 0;

        for (int i = 0; i < 18; i ++)
        {
            input.get();
        }
        int width = input.get();
        input.get();
        input.get();
        input.get();
        int height = input.get();

        for (int i = 0; i < 31; i ++)
        {
            input.get();
        }

        while(!input.eof() && col != height)
        {
            int b = input.get();
            int g = input.get();
            int r = input.get();

            Point color = Point(r, g, b);

            if (r == 255)
                output << "v";
            else if (r == 60)
                output << "g";
            else if (r == 0)
                output << "s";
            else
                output << "[" << r << "]";

            if (row == width-1)
            {
                row = 0;
                col++;
                output << endl;
            }
            else
            {
                row++;
            }
        }
    }
    output.close();
    input.close();

}

#endif
