#include <stdio.h>

int MyFunc(int parameter1, char parameter2)
{
    int local1 = 9;
    char local2 = 'z';
    return 0;
}
int main(int argc, char *argv[])
{ 
    float local1 = 15.0; 
    MyFunc(7, '9');
    printf("Hallo!");
    return 17;
}
