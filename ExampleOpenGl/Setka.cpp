#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

int Setka()
{


    double a = 10016.6311911, t = 0.0000005, h = 0.25, Gamma = 0;
    double z[5] = {0, 0.25, 0.5, 0.75, 0}, schema[10][5];
    memset(schema, 0, sizeof(schema));

    Gamma = a * t / h;
    cout << "Gamma: " << Gamma << endl;

    double buf[5] = {0, 151.99, 156, 147.99, 0};

    for(int i = 0; i < 5; i++)
    {
       schema[0][i] = buf[i];
    }

    for(int i = 0; i < 10; i++)
    {
       for(int j = 0; j < 5; j++)
       {
           cout << "s[" << i << "][" << j <<"]= " << setprecision(7) << schema[i][j] << "\t";
       }
       cout << endl;
    }

    // DEFINED FOR ALL SCHEMA

    for(int i = 1; i < 10; i++)
    {
       for(int j = 1; j < 4; j++)
       {
           schema[i][j] = ( (1 - (2*Gamma) ) * schema[i - 1][j] ) + ( Gamma *(schema[i - 1][j + 1] + schema[i - 1][j - 1]) - (i*0.06));
       }
    }

    cout << endl <<"--------------------------------------------------------" << endl << endl;

    for(int i = 0; i < 10; i++)
    {
       for(int j = 0; j < 5; j++)
       {
           cout.setf(ios::right);
           cout.width(5);
           cout << "s[" << i << "][" << j <<"]= " << schema[i][j] << " ";
       }
       cout << endl;
    }

    return 0;
}
