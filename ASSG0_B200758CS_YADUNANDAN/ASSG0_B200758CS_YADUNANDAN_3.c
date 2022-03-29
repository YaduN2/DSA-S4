#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct linkedlist
{
    struct node *head;
    int length;
};

typedef struct node *node;
typedef struct linkedlist *linkedlist;

struct node *create_node(int x);
void insert_end(linkedlist LList, node X);
int kLast(linkedlist LList, int k);

struct node *create_node(int x)
{
    node temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = x;
    temp->next = NULL;
    return temp;
}

void insert_end(linkedlist LList, node X)
{
    node temp = LList->head;
    if (temp != NULL)
    {
        while (temp->next != NULL)
        {
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
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int kLast(linkedlist LList, int k)
{
    int loc = LList->length - k + 1;
    if (loc <= 0)
        return -1;
    else
    {
        node temp = LList->head;
        while (loc > 1)
        {
            temp = temp->next;
            loc--;
        }
        return temp->data;
    }
}

void main()
{
    int num;
    char ent;

    int data;
    char choice = 'a';
    linkedlist LList;
    LList = (linkedlist)malloc(sizeof(linkedlist));
    node temp_main;
    LList->head = NULL;
    LList->length = 0;
    while (ent != '\n')
    {
        scanf("%d%c", &num, &ent);
        insert_end(LList, create_node(num));
        LList->length++;
    }

    int k;
    scanf("%d", &k);
    printf("%d", kLast(LList, k));
}