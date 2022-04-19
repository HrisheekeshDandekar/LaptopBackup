#include <stdio.h>

int main()
{
    char key[26] = "Relatively_Big_string.bmp";
    char incript_this[81] = "Hrisheekesh is GreatHrisheekesh is GreatHrisheekesh is GreatHrisheekesh is Great";
    char incripted[64];
    char decripted[64];
    
    int mulby = 1;
    
    
    //encrypt
    for (int i = 0; i < sizeof(incript_this); i++)
    {
        incripted[i] = incript_this[i] ^ (key[i % sizeof(key)] * mulby);
        mulby++;
        mulby % 4;
        if (mulby == 0)
        {
            mulby = 1;
        }
    }

    printf("\nEncrypted %s\n", incripted);

    //decrypt
    mulby = 1;
    for (int i = 0; i < sizeof(incript_this); i++)
    {
        decripted[i] = incripted[i] ^ (key[i % sizeof(key)] * mulby);
        mulby++;
        mulby % 4;
        if (mulby == 0)
        {
            mulby = 1;
        }
    }

    printf("\nDecrypted %s\n", decripted);
    return 0;
}