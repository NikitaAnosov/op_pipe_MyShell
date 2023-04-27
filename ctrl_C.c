#include <stdio.h>
#include <unistd.h> 

int main() {
    int count = 1;
    while (1) { // infinite loop
        printf("Print %d\n", count);
        count++;
        sleep(2); // wait for 2 seconds
    }
    return 0;
}