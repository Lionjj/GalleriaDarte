#include <stdio.h>
#include <stdlib.h>
#include "stringcontrol.h"
#include "datainput.h"

int getInt(int representation)
{
    int val, i = 0;
    char str[11], *ptr = NULL;
    do
    {
        if (i > 0)
        {
            printf("\n\t-ATTENZIONE: il valore che hai inserito non e' numerico!\n\t-");
        }
        gets(str);
        val = strtoul(str, &ptr, representation);
        i = 1;
    } while (!sisdigit(str));
    return val;
}

unsigned int getUInt(int representation)
{
    unsigned int val, i = 0;
    char str[11], *ptr = NULL;

    do
    {
        if (i > 0)
        {
            printf("\n\t-ATTENZIONE: il valore che hai inserito non e' numerico!\n\t-");
        }
        gets(str);
        val = strtoul(str, &ptr, representation);
        i = 1;
    } while (!sisdigit(str));

    return val;
}

int intCompare(const void *p1, const void *p2)
{
    int int_a = *((int *)p1);
    int int_b = *((int *)p2);

    if (int_a == int_b)
    {
        return 0;
    }
    else if (int_a < int_b)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}