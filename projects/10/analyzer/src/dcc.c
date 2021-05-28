/**
*       Source code for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <compengine/analyzer.h>

int main(int argc, char* argv[])
{
    compile(argv[1]);
    return 0;
}
