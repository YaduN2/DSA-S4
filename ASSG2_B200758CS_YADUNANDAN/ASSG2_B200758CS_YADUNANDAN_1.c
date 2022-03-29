#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct EMPLOYEE
{
    int id;
};
typedef struct EMPLOYEE *EMPLOYEE;

EMPLOYEE HashTable(int tableSize)
{
    EMPLOYEE hashTable = (EMPLOYEE)malloc(sizeof(EMPLOYEE) * tableSize);
    for (int i = 0; i < tableSize; i++)
        hashTable[i].id = -1;
    return hashTable;
}

int getHash(int data, int size)
{
    return data % size;
}

int getHashQuad(int data, int size, int C1, int C2, int curIndex)
{
    return (((data % size) + (C1 * curIndex) + (C2 * curIndex * curIndex)) % size);
}

int getPrime(int size)
{
    if (size & 1)
        size -= 2;
    else
        size--;
    int i, j;
    for (i = size; i >= 2; i -= 2)
    {
        if (i % 2 == 0)
            continue;
        for (j = 3; j <= sqrt(i); j += 2)
        {
            if (i % j == 0)
                break;
        }
        if (j > sqrt(i))
            return i;
    }
    return 2;
}

int getHashDoub(int data, int size, int prime, int i)
{
    return ((data % size) + i * (prime - (data % prime))) % size;
}

bool INSERT(EMPLOYEE hashTable, int id, int tableSize, int C1, int C2, int prime, char method)
{
    if (hashTable == NULL)
        return false;

    int index = getHash(id, tableSize);

    if (hashTable[index].id == -1)
    {
        hashTable[index].id = id;
    }
    else
    {
        if (method == 'a')
        {
            for (int i = 0; i < tableSize; i++)
            {
                int quad = getHashQuad(id, tableSize, C1, C2, i);
                if (hashTable[quad].id == -1)
                {
                    hashTable[quad].id = id;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < tableSize; i++)
            {
                int doub = getHashDoub(id, tableSize, prime, i);
                if (hashTable[doub].id == -1)
                {
                    hashTable[doub].id = id;
                    break;
                }
            }
        }
    }
    return true;
}

int SEARCH(EMPLOYEE hashTable, int id, int tableSize, int C1, int C2, int prime, int method)
{
    int index = -1;
    int I = getHash(id, tableSize);
    if (hashTable[I].id == id)
    {
        index = I;
    }
    else
    {
        if (method == 'a')
        {
            for (int i = 0; i < tableSize; i++)
            {
                int I = getHashQuad(id, tableSize, C1, C2, i);
                if (hashTable[I].id == id)
                {
                    index = I;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < tableSize; i++)
            {
                int I = getHashDoub(id, tableSize, prime, i);
                if (hashTable[I].id == id)
                {
                    index = I;
                    break;
                }
            }
        }
    }
    return index;
}

int DELETE(EMPLOYEE hashTable, int id, int index)
{
    hashTable[index].id = -1;
}

void printTable(EMPLOYEE hashTable, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (hashTable[i].id == -1)
            printf("%d ()\n", i);
        else
            printf("%d (%d)\n", i, hashTable[i]);
    }
}

int main()
{
    char method;
    scanf("%c", &method);

    int tableSize;
    scanf("%d", &tableSize);
    // tableSize = 7;

    int C1 = 0, C2 = 0;
    int prime = 1;

    if (method == 'a')
    {
        scanf("%d", &C1);
        scanf("%d", &C2);
    }
    else
    {
        prime = getPrime(tableSize);
    }

    EMPLOYEE hashTable = HashTable(tableSize);

    int id;
    char choice = 'x';

    while (choice != 't')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%d", &id);
            INSERT(hashTable, id, tableSize, C1, C2, prime, method);
            break;
        case 's':
            scanf("%d", &id);
            int sRes = SEARCH(hashTable, id, tableSize, C1, C2, prime, method);
            if (sRes == -1)
                printf("-1\n");
            else
                printf("1\n");
            break;

        case 'd':
            scanf("%d", &id);
            int index = SEARCH(hashTable, id, tableSize, C1, C2, prime, method);
            if (index != -1)
                DELETE(hashTable, id, index);
            break;

        case 'p':
            printTable(hashTable, tableSize);
            break;
        default:
            break;
        }
    }
    return 0;
}