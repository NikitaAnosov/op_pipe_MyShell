#include "codecA.h"

//covert all lower case chars to upper case or all upper case to lower case.
// example: input= aaBB
//          output= AAbb
void _codecA(char* ch)
{
    char* save_ch = ch;
    while (*save_ch)// string ends with '\0'
    {
        //if upper to lower
        if (*save_ch >= 'A' && *save_ch <='Z')
        {
            *save_ch += 32;
        }
        //else
        else if (*save_ch >= 'a' && *save_ch <='z')
        {
            *save_ch -= 32;
        }
        save_ch++;
    }
    
}
