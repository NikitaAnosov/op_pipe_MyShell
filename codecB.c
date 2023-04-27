#include "codecB.h"

// convert all chars to the 3-rd next char
void _codecB_next3chars(char *ch)
{
    char *save_ch = ch;
    while (*save_ch) // string ends with '\0'
    {
        *save_ch += 3;
        save_ch++;
    }
}
////convert all chars to the 3-rd prev char
void _codecB_prev3chars(char *ch)
{
    char *save_ch = ch;
    while (*save_ch) // string ends with '\0'
    {
        *save_ch -= 3;
        save_ch++;
    }
}