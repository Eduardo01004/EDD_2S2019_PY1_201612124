#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
using namespace std;

class Nodomatriz
{
    public:
    Nodomatriz();
    ~Nodomatriz();
    int x;
    int y;
    string color;
    Nodomatriz *siguiente;
    Nodomatriz *anterior;
    Nodomatriz *abajo;
    Nodomatriz *arriba;
};

#endif // NODOMATRIZ_H
