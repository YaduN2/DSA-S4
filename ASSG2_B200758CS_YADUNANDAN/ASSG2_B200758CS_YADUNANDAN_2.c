#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node *node;
typedef struct linkedlist *linkedlist;

struct node
{
    char word[50];
    struct node *next;
};

struct linkedlist
{
    struct node *head;
};

struct node *create_node(char word[])
{
    node temp;
    temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->word, word);
    temp->next = NULL;
    return temp;
}

struct node *search_list(linkedlist LList, char word[])
{
    node temp = LList->head;
    while (temp != NULL && temp->word != word)
        temp = temp->next;
    return temp;
}

void insert_end(linkedlist LList, node X)
{
    node temp = LList->head;
    if (temp != NULL)
    {
        while (temp->next != NULL)
        {
            if (strcmp(temp->word, X->word) == 0)
            {
                free(X);
                return;
            }
            temp = temp->next;
        }
        temp->next = X;
    }
    else
    {
        LList->head = X;
    }
}

void PRINT_LIST(linkedlist LList)
{
    // printf("FUN>print_list!\n");
    node temp = LList->head;
    if (temp == NULL)
    {
        printf("null");
        return;
    }

    while (temp != NULL)
    {
        printf("%s", temp->word);
        if (temp->next != NULL)
            printf("-");
        temp = temp->next;
    }
}

int getHash(int length, int size)
{
    return (length * length) % size;
}

int main()
{
    // int size = 3;
    // char str[500] = "Write a program to create a hash table";

    int size;
    char str[500];
    scanf("%d\n", &size);
    scanf("%[^\n]s", str);
    // fgets(str, sizeof(str), stdin);

    // printf("size:%d string:%s\n", size, str);

    linkedlist *hashtable = (linkedlist *)malloc(sizeof(struct linkedlist) * size);

    for (int i = 0; i < size; i++)
    {
        hashtable[i] = (linkedlist)malloc(sizeof(linkedlist));
        hashtable[i]->head = NULL;
    }

    char *token = strtok(str, " ");
    while (token != NULL)
    {
        int index = getHash(strlen(token), size);

        insert_end(hashtable[index], create_node(token));

        token = strtok(NULL, " ");
    }
    for (int i = 0; i < size; i++)
    {
        printf("%d:", i);
        PRINT_LIST(hashtable[i]);
        printf("\n");
    }
    return 0;
}