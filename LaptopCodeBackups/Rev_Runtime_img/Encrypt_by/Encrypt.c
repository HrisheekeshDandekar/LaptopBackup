#include <stdio.h>

int main(int argc, char** argv)
{
    int arr[] = {
        1, 1, 8, 5, 7, 6, 9, 2, 2, 5
    };

    int decrypt[10];

    FILE* fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("Not opened\n");
        return 1;
    }

    fseek(fp, -20, SEEK_END);

    fread(decrypt, sizeof(char), 10, fp);
    int add_by = 1;
    for (int i = 0; i < 10; i++)
    {
        if (arr[i] == 0)
        {
            arr[i] = add_by;
        }
        add_by++;
    }

    for (int i = 0; i < 10; i++)
    {
        arr[i] = arr[i] ^ decrypt[i];
        printf("%d ,", arr[i]);
    }
    return 0;
}