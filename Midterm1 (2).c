// Jonathan Carbonneau
// I pledge my honor that I have abided by the Stevens Honor System.

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 64

void little2big(int *arr, int len)
{
    char *array = (char *)arr;
    for (size_t i = 0; i < len; i++)
    {
        int num = (*(int *)(array + (i * sizeof(int))));
        (*(int *)(array + (i * sizeof(int)))) = ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000);
    }
}

int main(int argc, char *argv[])
{

    FILE *file = fopen(argv[1], "r");
    char line[500];
    if (!file)
    {
        printf("\n Argument one: unable to open : %s ", argv[1]);
        return -1;
    }
    int size = 0;
    while (fgets(line, sizeof(line), file))
    {
        size++;
    }

    int *old_array = (int *)malloc(size * sizeof(int));
    char *array = (char *)old_array;
    rewind(file);
    int index = 0;
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d", ((int *)(array + (index * sizeof(int)))));
        index++;
    }
    fclose(file);

    little2big(old_array, size);

    FILE *fp = fopen(argv[2], "w");
    if (!fp)
    {
        printf("\n Argument two: unable to open : %s ", argv[2]);
        return -1;
    }

    for (size_t i = 0; i < size; i++)
    {
        fprintf(fp, "%d\n", (*(int *)(array + (i * sizeof(int)))));
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
