#include <stdio.h>

void func1(char);
char func2(char);

void func1(char c1){
     char byte_1 = func2(c1);
    return;
}
char func2(char c1) {
    char byte_0 = c1 << 2;
    return byte_0;
} 
int main(void)
{ 
    char loc = 0x23;
    func1(loc);
    return 17;
}
