#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct id *id;

struct id
{
    int taken;
    char roll[5];
    char name[20];
};

int hash(int a, int b, int c)
{
    return (((a + b + c) % 26) % 10);
}

int getIndex(char name[])
{
    int index;
    if (strlen(name) >= 9)
    {
        index = hash(name[0], name[1], name[2]) * 100 + hash(name[0], name[2], name[4]) * 10 + hash(name[0], name[4], name[8]) * 1;
    }
    else if (strlen(name) >= 5 && strlen(name) < 9)
    {
        index = (hash(name[0], name[1], name[2])) * 100 + (hash(name[0], name[2], name[4])) * 10 + (hash(name[0], name[4], 0)) * 1;
    }
    else if (strlen(name) >= 3 && strlen(name) < 5)
    {
        index = (hash(name[0], name[1], name[2])) * 100 + (hash(name[0], name[2], 0)) * 10 + (hash(name[0], 0, 0)) * 1;
    }
    else if (strlen(name) >= 2 && strlen(name) < 3)
    {
        index = (hash(name[0], name[1], 0)) * 100 + (hash(name[0], 0, 0)) * 10 + (hash(name[0], 0, 0)) * 1;
    }
    else if (strlen(name) >= 1 && strlen(name) < 2)
    {
        index = (hash(name[0], 0, 0)) * 100 + (hash(name[0], 0, 0)) * 10 + (hash(name[0], 0, 0)) * 1;
    }
    // printf("index:%d", index);
    return index;
}

int extIndex(char roll[])
{
    return ((roll[3] - '0') * 1) + ((roll[2] - '0') * 10) + ((roll[1] - '0') * 100);
}

void INSERTDATA(id *hashTable, char name[])
{
    char roll[5];
    int index = getIndex(name);
    int cal = index;
    // printf("index:%d\n", index);
    roll[0] = name[0];
    roll[3] = (cal % 10) + '0';
    cal = cal / 10;
    roll[2] = (cal % 10) + '0';
    cal = cal / 10;
    roll[1] = (cal % 10) + '0';
    roll[4] = '\0';

    // printf("rollNum:%s\n", roll);
    hashTable[index]->taken = 1;
    strcpy(hashTable[index]->roll, roll);
    strcpy(hashTable[index]->name, name);
    // printf("roll:%s length:%d\n", hashTable[index].roll, strlen(hashTable[index].roll));
}

void print(id *hashTable)
{
    for (int i = 0; i < 1000; i++)
    {
        if (hashTable[i]->taken == 1)
        {
            printf("%d: %s %s\n", i, hashTable[i]->name, hashTable[i]->roll);
        }
        else
        {
            printf("%d: null\n", i);
        }
    }
}

void SEARCH(id *hashTable, char roll[])
{
    int index = extIndex(roll);
    // printf("\nindex:%d\n", index);
    if (hashTable[index]->taken == 1)
        printf("%s\n", hashTable[index]->name);
    else
        printf("NOT FOUND\n");
}

void DELETE(id *hashTable, char roll[])
{
    int index = extIndex(roll);
    hashTable[index]->taken = -1;
}

int main()
{
    int size = 1000;
    id *hashTable = (id *)malloc(sizeof(id) * size);
    for (int i = 0; i < size; i++)
    {
        hashTable[i] = (id)malloc(sizeof(id));
        hashTable[i]->taken = -1;
    }

    char choice = 'z';
    char name[20];
    char roll[5];

    while (choice != 't')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%s", name);
            INSERTDATA(hashTable, name);
            break;
        case 'p':
            print(hashTable);
            break;
        case 's':
            scanf("%s", roll);
            SEARCH(hashTable, roll);
            break;
        case 'd':
            scanf("%s", roll);
            DELETE(hashTable, roll);
            break;

        default:
            break;
        }
    }
    return 1;
}