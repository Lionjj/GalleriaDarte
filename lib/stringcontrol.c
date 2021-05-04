#include <stdbool.h>
#include <ctype.h>
#include "stringcontrol.h"

bool sisaspha(char str[])
{
    bool proportion;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        proportion = (bool) isalpha(str[i]);
        i++;
    }

    return proportion;
}

bool sisalnum(char str[])
{
    bool proportion;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        proportion = (bool) isalnum(str[i]);
        i++;
    }

    return proportion;
}

bool shaveanumber(char str[])
{
    bool proportion = false;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        if(isdigit(str[i]))
        {
            proportion = true;
            break;
        }else i++;
    }
    return proportion;
}

bool shaveaspecial(char str[])
{
    bool proportion = false;
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        // inserie la funzione per verificre se il singolo carattere è un carattere speciale
        if((str[i]))
        {
            proportion = true;
            break;
        }else i++;
    }
    return proportion;
}