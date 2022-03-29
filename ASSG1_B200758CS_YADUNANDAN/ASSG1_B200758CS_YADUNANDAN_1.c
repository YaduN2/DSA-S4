#include <stdio.h>
#include <stdlib.h>

typedef struct Tnode *Tnode;
typedef struct TREE *TREE;
typedef struct Qnode *Qnode;
typedef struct QUEUE *QUEUE;

Tnode CREATENODE(int data);
Tnode INSERT(TREE T, Tnode newNode);

// QUEUE IMPLEMENTATION!!
struct Qnode
{
    Tnode Qdata;
    Qnode next;
};

struct QUEUE
{
    Qnode front, rear;
};

Qnode CREATE_NODE(Tnode data)
{
    Qnode newNode = (Qnode)malloc(sizeof(struct Qnode));
    newNode->Qdata = data;
    newNode->next = NULL;
    return newNode;
}

int QUEUEEMPTY(QUEUE Q)
{
    if (Q->front == NULL)
        return 1;
    else
        return -1;
}

void ENQUEUE(QUEUE Q, Tnode data)
{
    Qnode new_node = CREATE_NODE(data);
    if (Q->front == NULL)
    {
        Q->front = new_node;
        Q->rear = new_node;
    }
    else
    {
        Q->rear->next = new_node;
        Q->rear = new_node;
    }
}

void DEQUEUE(QUEUE Q)
{
    if (QUEUEEMPTY(Q) == 1)
    {
        // printf("-1\n");
        return;
    }
    else
    {
        Qnode temp_node = Q->front;
        // printf("%d\n", temp_node->data);
        if (Q->front == Q->rear)
        {
            Q->front = NULL;
            Q->rear = NULL;
        }
        else
        {
            Q->front = Q->front->next;
        }
        free(temp_node);
    }
}

// void print_queue(QUEUE Q)
// {
//     Qnode temp = Q->front;
//     while (temp != NULL)
//     {
//         printf("%d ", temp->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }

// QUEUE END!!

struct Tnode
{
    int data;
    Tnode right;
    Tnode left;
    Tnode p;
};

struct TREE
{
    Tnode root;
};

Tnode CREATENODE(int data)
{
    Tnode newNode = (Tnode)malloc(sizeof(struct Tnode));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->p = NULL;
    // printf("Node created!\n");

    return newNode;
}

// change front and rear

Tnode INSERT(TREE T, Tnode newNode)
{
    // printf("before first if\n");

    if (T->root == NULL)
    {
        T->root = newNode;
        return T->root;
    }
    // printf("after first if\n");
    QUEUE Q = (QUEUE)malloc(sizeof(QUEUE));
    Q->front = NULL;
    Q->rear = NULL;
    ENQUEUE(Q, T->root);
    while (QUEUEEMPTY(Q) != 1)
    {
        Tnode currNode = Q->front->Qdata;
        DEQUEUE(Q);

        if (currNode->left == NULL)
        {
            currNode->left = newNode;
            currNode->left->p = currNode;
            return T->root;
        }
        else
        {
            ENQUEUE(Q, currNode->left);
        }

        if (currNode->right == NULL)
        {
            currNode->right = newNode;
            currNode->right->p = currNode;
            return T->root;
        }
        else
        {
            ENQUEUE(Q, currNode->right);
        }
    }
}

void print_preorder(Tnode node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    print_preorder(node->left);
    print_preorder(node->right);
}

void PRINT(Tnode node)
{
    if (node == NULL)
    {
        printf("( ) ");
        return;
    }
    else
    {
        printf("( ");
        printf("%d ", node->data);
    }
    PRINT(node->left);
    PRINT(node->right);
    printf(") ");
}

int main()
{
    TREE T = (TREE)malloc(sizeof(TREE));
    T->root = NULL;
    char choice = 'x';
    int data;
    while (choice != 'e')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%d", &data);
            Tnode newNode = CREATENODE(data);
            // printf("INSERT\n");
            T->root = INSERT(T, newNode);
            break;

        case 'x':
            print_preorder(T->root);
            break;

        case 'p':
            PRINT(T->root);
            break;

        default:
            break;
        }
    }
    return 0;
}