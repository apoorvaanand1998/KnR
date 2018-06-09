#include <stdio.h>

int main()
{
    float fahr, cel;
    int low, high, step;
    
    low = 0;
    high = 300;
    step = 20;
    
    cel = low;
    
    printf("\t\tCelsius to Fahrenheit\n\n");
        
    while (cel <= high) {
        fahr = (cel * 9.0/5.0) + 32.0;
        printf("\t\t\t%3.0f %6.1f\n", cel, fahr);
        cel += step;
    }
    return 0;
}
