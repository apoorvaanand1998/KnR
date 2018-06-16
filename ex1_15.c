#include <stdio.h>

float c_to_f(int c);

int main() 
{
        int i;
        
        for (i = 0; i <= 400; i += 20) {
                printf("The value of %d celsius in fahrenheit is %.2f\n", i, c_to_f(i));
        }
        return 0;
}

float c_to_f(int c) 
{
    float f;
    
    f = (9.0/5.0 * c) + 32;
    
    return f;
}
    
    
