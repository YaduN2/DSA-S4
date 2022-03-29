#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Binary Search Tree with all operations
typedef struct node *node;
typedef struct TREE *TREE;
struct node *CREATENODE(int age, char firstName[], char lastName[]);
node search_node(node root, char firstName[], char lastName[]);
void print_preorder(node node);
node insertBST(TREE T, node new_node);
node SEARCH(TREE T, int age);
void PREORDER(TREE T);

int INSERT(int age, char first[], char last[]);

struct node
{
    int age;
    char firstName[20];
    char lastName[20];
    node left, right, p;
};

struct TREE
{
    node root;
};

struct node *CREATENODE(int age, char firstName[], char lastName[])
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->age = age;
    strcpy(temp->firstName, firstName);
    strcpy(temp->lastName, lastName);
    temp->left = temp->right = NULL;
    temp->p = NULL;
    return temp;
}

node search_node(node root, char firstName[], char lastName[])
{
    if (root == NULL)
        return NULL;
    else if (strcmp(root->firstName, firstName) == 0 && strcmp(root->lastName, lastName) == 0)
        return root;
    search_node(root->left, firstName, lastName);
    search_node(root->right, firstName, lastName);
}

void print_preorder(node node)
{
    if (node == NULL)
        return;
    printf("%d ", node->age);
    print_preorder(node->left);
    print_preorder(node->right);
}

node insertBST(TREE T, node new_node)
{
    node current = T->root, parent = NULL;
    while (current != NULL)
    {
        parent = current;
        if (new_node->age <= current->age)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    new_node->p = parent;
    if (parent == NULL)
        T->root = new_node;
    else if (new_node->age <= parent->age)
        parent->left = new_node;
    else
        parent->right = new_node;
    return T->root;
}

void PREORDER(TREE T)
{
    print_preorder(T->root);
    printf("\n");
}

int getSum(char last[])
{
    int sum = 0;
    for (int i = 0; i < strlen(last); i++)
        sum = sum + last[i];
    return sum;
}

int INSERT(int age, char first[], char last[])
{
    return getSum(last) % 128;
}

typedef struct Snode *Snode;
typedef struct STACK *STACK;

struct Snode
{
    node person;
    struct Snode *next;
};

struct STACK
{
    Snode top;
};

Snode CREATE_Snode(node person)
{
    Snode temp;
    temp = (Snode)malloc(sizeof(Snode));
    temp->person = person;
    temp->next = NULL;
    return temp;
}

int STACK_EMPTY(STACK S)
{
    if (S->top == NULL)
    {
        printf("-1\n"); // is empty
        return -1;
    }
    else
    {
        printf("1\n"); // not empty
        return 1;
    }
}

void PUSH(STACK S, node person)
{
    Snode new_Snode = CREATE_Snode(person);
    if (S->top == NULL)
    {
        S->top = new_Snode;
    }
    else
    {
        new_Snode->next = S->top;
        S->top = new_Snode;
    }
}

void POP(STACK S)
{
    Snode select_Snode = S->top;
    printf("%s %s %d\n", S->top->person->firstName, S->top->person->lastName, S->top->person->age);
    S->top = S->top->next;
    free(select_Snode);
}

void printRelatives(node root, node person)
{
    STACK S = (STACK)malloc(sizeof(STACK));
    S->top = NULL;
    while (person != root->p)
    {
        PUSH(S, person);
        person = person->p;
    }

    while (S->top != NULL)
        POP(S);
}

int main()
{
    int size = 128;
    TREE *hashtable = (TREE *)malloc(sizeof(struct TREE) * size);

    char firstName[20];
    char lastName[20];
    int age;

    for (int i = 0; i < size; i++)
    {
        hashtable[i] = (TREE)malloc(sizeof(TREE));
        hashtable[i]->root = NULL;
    }
    int index;
    char choice = 'x';
    while (choice != 't')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%s", firstName);
            scanf("%s", lastName);
            scanf("%d", &age);

            index = INSERT(age, firstName, lastName);
            insertBST(hashtable[index], CREATENODE(age, firstName, lastName));
            break;

        case 'p':
            scanf("%s", firstName);
            scanf("%s", lastName);
            index = INSERT(age, firstName, lastName);
            node temp = search_node(hashtable[index]->root, firstName, lastName);

            if (temp == NULL)
                printf("-1\n");
            else
                printRelatives(hashtable[index]->root, temp);

            break;

        case 'y':
            printf("PreOrder:\n");
            for (int i = 0; i < size; i++)
            {
                printf("%d:", i);
                if (hashtable[i]->root == NULL)
                    printf("NULL\n");
                else
                    PREORDER(hashtable[i]);
            }
            printf("\n!!END!!\n");
            break;

        default:
            break;
        }
    }

    return 0;
}
