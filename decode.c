#include <stdio.h>
#include <string.h>
#include "codecA.h"
#include "codecB.h"
// same like encode
//Usage : encode/decode <codec> <message>
int main(int argc, char* argv[]) 
{
    if(argc < 3) //check if user write correctly
    {
        printf("error:\n\tUsage: encode/decode <codec> <message>\n");
        return 1;
    }
        if (strcmp(argv[1], "codecA") == 0)
        {
            _codecA(argv[2]);//send the string
        }
        else if (strcmp(argv[1], "codecB") == 0)
        {
            _codecB_prev3chars(argv[2]);//send the string
        }
        else{
            printf("error:\n\twrite only codecA / codecB");
            return 2;
        }
    printf("%s\n", argv[2]);
    return 0;
}