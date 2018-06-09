#include <stdio.h>

int main()
{
    float fahr, cel;
    int low, high, step;
    
    low = 0;
    high = 300;
    step = 20;
    
    fahr = low;
    
    printf("\t\tFahrenheit to Celsius\n\n");
    
    while (fahr <= high) {
        cel = (5.0 / 9.0) * (fahr - 32.0);
        printf("\t\t\t%3.0f %6.1f\n", fahr, cel);
        fahr += step;
    }
    return 0;
}

    
