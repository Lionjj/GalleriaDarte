#include <stdbool.h>
#include <ctype.h>
#include "stringcontrol.h"
#include <string.h>
#include <stdlib.h>

bool sisaspha(char str[])
{
    bool proposition;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        proposition = (bool) isalpha(str[i]);
        i++;
    }

    return proposition;
}

bool sisalnum(char str[])
{
    bool proposition;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        proposition = (bool) isalnum(str[i]);
        i++;
    }

    return proposition;
}

bool shaveanumber(char str[])
{
    bool proposition = false;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        if(isdigit(str[i]))
        {
            proposition = true;
            break;
        }else i++;
    }
    return proposition;
}

bool shaveaspecial(char str[])
{
    bool proposition = false;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        // inserie la funzione per verificre se il singolo carattere è un carattere speciale
        if((str[i]))
        {
            proposition = true;
            break;
        }else i++;
    }
    return proposition;
}

bool verifyemail(char str[])
{
    bool proposition = false;
    char* ptr = NULL;

    for (int i = 0; i < strlen(str); ++i)
    {
        if(str[i] == '@')
        {
            proposition = true;
            break;
        }
    }

    free(ptr);
    return proposition;
}