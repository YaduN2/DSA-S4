#include <stdio.h>
#include <stdlib.h>
typedef struct node *node;
struct node
{
    int data;
    int degree;
    node leftChild, rightSibling, parent;
};

struct linkedlist
{
    node head;
};
typedef struct linkedlist *linkedlist;

node create_node(int x)
{
    node temp;
    temp = (node)malloc(sizeof(struct node));
    temp->data = x;
    temp->leftChild = NULL;
    temp->rightSibling = NULL;
    temp->parent = NULL;
    temp->degree = 0;
    return temp;
}

node makeHeap(node root)
{
    // root = (node )malloc(sizeof(node));
    root = NULL;
    return root;
}

node minimum(node head)
{
    node temp = head;
    node minNode = temp;
    while (temp != NULL)
    {
        if (minNode->data > temp->data)
            minNode = temp;
        temp = temp->rightSibling;
    }
    return minNode;
}

node binomialLink(node leftChild, node parent)
{
    leftChild->parent = parent;
    leftChild->rightSibling = parent->leftChild;
    parent->leftChild = leftChild;
    parent->degree++;
    return parent;
}

node binomialMerge2(node head1, node head2)
{
    node nodeHeap1 = head1;
    node nodeHeap2 = head2;
    node head3 = (node)malloc(sizeof(node));
    head3 = NULL;
    if (nodeHeap1->degree > nodeHeap2->degree)
    {
        head3 = nodeHeap2;
        nodeHeap2 = nodeHeap2->rightSibling;
        head3->rightSibling = NULL;
    }
    else
    {
        head3 = nodeHeap1;
        nodeHeap1 = nodeHeap1->rightSibling;
        head3->rightSibling = NULL;
    }

    node nodeHeap3 = head3;

    while (nodeHeap1 != NULL && nodeHeap2 != NULL)
    {
        if (nodeHeap1->degree <= nodeHeap2->degree)
        {
            nodeHeap3->rightSibling = nodeHeap1;
            nodeHeap3 = nodeHeap3->rightSibling;
            nodeHeap1 = nodeHeap1->rightSibling;
            nodeHeap3->rightSibling = NULL;
        }
        else
        {
            nodeHeap3->rightSibling = nodeHeap2;
            nodeHeap3 = nodeHeap3->rightSibling;
            nodeHeap2 = nodeHeap2->rightSibling;
            nodeHeap3->rightSibling = NULL;
        }
    }
    if (nodeHeap1 == NULL)
        nodeHeap3->rightSibling = nodeHeap2;
    else
        nodeHeap3->rightSibling = nodeHeap1;
    return head3;
}

node binomialMerge3(node head1, node head2)
{
    node nodeHeap1 = head1;
    node nodeHeap2 = head2;
    node head3 = (node)malloc(sizeof(node));
    head3 = NULL;
    if (nodeHeap1->degree > nodeHeap2->degree)
    {
        head3 = nodeHeap2;
        nodeHeap2 = nodeHeap2->rightSibling;
        head3->rightSibling = NULL;
    }
    else
    {
        head3 = nodeHeap1;
        nodeHeap1 = nodeHeap1->rightSibling;
        head3->rightSibling = NULL;
    }
    node nodeHeap3 = head3;

    while (nodeHeap2 != NULL && nodeHeap1 != NULL)
    {
        nodeHeap3 = head3;
        node selNode = NULL;
        if (nodeHeap2->degree < nodeHeap1->degree)
            selNode = nodeHeap2;
        else
            selNode = nodeHeap1;

        while (nodeHeap3->rightSibling->degree < selNode->degree && nodeHeap3->rightSibling != NULL)
            nodeHeap3 = nodeHeap3->rightSibling;

        nodeHeap1->rightSibling = nodeHeap3->rightSibling;
        nodeHeap3->rightSibling = nodeHeap1;
    }
    while (nodeHeap3->rightSibling != NULL)
        nodeHeap3 = nodeHeap3->rightSibling;

    if (nodeHeap1 == NULL)
        nodeHeap3->rightSibling = nodeHeap2;
    else
        nodeHeap3->rightSibling = nodeHeap1;
    return head3;
}

node heapMerge(node H1, node H2)
{
    node H = makeHeap(H);
    node nodeTemp1 = H1, a, b, nodeTemp2 = H2;
    if (nodeTemp1 != NULL)
    {
        if (nodeTemp2 != NULL && nodeTemp1->degree <= nodeTemp2->degree)
            H = nodeTemp1;
        else if (nodeTemp2 != NULL && nodeTemp1->degree > nodeTemp2->degree)
            /* need some modifications here;the first and the else conditions can be merged together!!!! */
            H = nodeTemp2;
        else
            H = nodeTemp1;
    }
    else
        H = nodeTemp2;
    while (nodeTemp1 != NULL && nodeTemp2 != NULL)
    {
        if (nodeTemp1->degree < nodeTemp2->degree)
        {
            nodeTemp1 = nodeTemp1->rightSibling;
        }
        else if (nodeTemp1->degree == nodeTemp2->degree)
        {
            a = nodeTemp1->rightSibling;
            nodeTemp1->rightSibling = nodeTemp2;
            nodeTemp1 = a;
        }
        else
        {
            b = nodeTemp2->rightSibling;
            nodeTemp2->rightSibling = nodeTemp1;
            nodeTemp2 = b;
        }
    }
    return H;
}

node Union(node head1, node head2)
{
    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;

    node head = makeHeap(head);
    // printf("%d", head1->data);
    // printf("%d", head2->data);
    head = heapMerge(head1, head2);

    // free(head1);
    // free(head2);

    if (head == NULL)
        return head;

    node preNode = NULL;
    node x = head;
    node nextNode = x->rightSibling;
    while (nextNode != NULL)
    {
        if ((x->degree != nextNode->degree) || (nextNode->rightSibling != NULL && nextNode->rightSibling->degree == x->degree))
        {
            preNode = x;
            x = nextNode;
        }
        else
        {
            if (x->data <= nextNode->data)
            {
                x->rightSibling = nextNode->rightSibling;
                nextNode = binomialLink(nextNode, x);
            }
            else
            {
                if (preNode == NULL)
                    head = nextNode;
                else
                    preNode->rightSibling = nextNode;
                nextNode = binomialLink(x, nextNode);
                x = nextNode;
            }
        }
        nextNode = x->rightSibling;
    }
    return head;
}

int REVERT_LIST(node root, node *Hr)
{
    if (root->rightSibling != NULL)
    {
        REVERT_LIST(root->rightSibling, Hr);
        (root->rightSibling)->rightSibling = root;
    }
    else
    {
        *Hr = root;
    }
}

node ExtractMin(node head)
{
    node t = NULL;
    node x = head;
    node Hr = NULL;
    node p;
    if (x == NULL)
        return x;

    int min = x->data;
    p = x;
    while (p->rightSibling != NULL)
    {
        if ((p->rightSibling)->data < min)
        {
            min = (p->rightSibling)->data;
            t = p;
            x = p->rightSibling;
        }
        p = p->rightSibling;
    }

    printf("%d\n", min);

    if (t == NULL && x->rightSibling == NULL)
        head = NULL;
    else if (t == NULL)
        head = x->rightSibling;
    else if (t->rightSibling == NULL)
        t = NULL;
    else
        t->rightSibling = x->rightSibling;
    if (x->leftChild != NULL)
    {
        REVERT_LIST(x->leftChild, &Hr);
        (x->leftChild)->rightSibling = NULL;
    }
    head = Union(head, Hr);
    return head;
}

node Insert(node head, node x)
{
    if (head == NULL)
    {
        head = x;
        return head;
    }
    node headTemp = makeHeap(headTemp);
    headTemp = x;
    head = Union(head, headTemp);

    return head;
}

// bfs implementation using queue for printing

struct queue_node
{
    node key;
    struct queue_node *next;
};
typedef struct queue_node *queue_node;

int queue_isEmpty(queue_node *root)
{
    return ((*root) == NULL);
}
queue_node queue_create_node(node key)
{
    queue_node new_node = (queue_node)malloc(sizeof(struct queue_node));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void queue_insert(queue_node *root, queue_node x)
{

    if (queue_isEmpty(root))
    {
        *root = x;
        return;
    }
    queue_node ptr = *root;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = x;
}

void queue_delete(queue_node *root)
{
    if (queue_isEmpty(root))
    {
        // printf("-1\n");
        return;
    }
    // printf("%d\n", (*list)->key);
    (*root) = (*root)->next;
}

void queue_Enqueue(queue_node *root, queue_node x)
{
    queue_insert(root, x);
}

void queue_Dequeue(queue_node *root)
{
    queue_delete(root);
}

void printBinHeap(node root)
{
    if (root != NULL)
    {
        // printf("%d ", root->data);
        queue_node queue = NULL;
        node temp = root;
        queue_Enqueue(&queue, queue_create_node(temp));
        if (temp == NULL)
        {
            return;
        }

        do
        {
            temp = queue->key;
            queue_Dequeue(&queue);
            while (temp != NULL)
            {
                printf("%d ", temp->data);
                if (temp->leftChild != NULL)
                {
                    queue_node x = queue_create_node(temp->leftChild);
                    queue_Enqueue(&queue, x);
                }
                temp = temp->rightSibling;
            }

            if (temp != NULL)
                temp = queue->key;

            if (temp != NULL && queue_isEmpty((&queue)) == 1)
            {
                printf("%d ", temp->data);
            }
        } while (queue_isEmpty((&queue)) == 0);
    }
}

node search(node H, int k)
{
    node x = H;
    node p = NULL;
    if (x->data == k)
    {
        p = x;
        return p;
    }
    if (x->leftChild != NULL && p == NULL)
    {
        p = search(x->leftChild, k);
    }
    if (x->rightSibling != NULL && p == NULL)
    {
        p = search(x->rightSibling, k);
    }
    return p;
}

void print_heap(node head)
{
    node temp = head;

    while (temp != NULL)
    {
        printBinHeap(temp);
        temp = temp->rightSibling;
    }
    printf("\n");
}

/*
node ExtractMin(node head)
{
    node minNode = minimum(head);
    printf("%d\n", minNode->data);
    node childNode = minNode->leftChild;

    if (minNode == head) // first node
    {
        head = minNode->rightSibling;
        minNode = NULL;
    }
    else if (minNode->rightSibling == NULL) // last node
    {
        minNode = NULL;
    }
    else
    {
        node x = head;
        while (x->rightSibling != minNode)
            x = x->rightSibling;
        x->rightSibling = minNode->rightSibling;
        minNode = NULL;
    }
    return Union(head, childNode);
} */
/*
node ExtractMin(node head)
{
    int min;
    node t = NULL;
    node x = head;
    node Hr;
    node p;
    Hr = NULL;
    if (x == NULL)
    {
        printf("\nNOTHING TO EXTRACT");
        return x;
    }
    //    int min=x->n;
    p = x;
    while (p->rightSibling != NULL)
    {
        if ((p->rightSibling)->data < min)
        {
            min = (p->rightSibling)->data;
            t = p;
            x = p->rightSibling;
        }
        p = p->rightSibling;
    }
    if (t == NULL && x->rightSibling == NULL)
        head = NULL;
    else if (t == NULL)
        head = x->rightSibling;
    else if (t->rightSibling == NULL)
        t = NULL;
    else
        t->rightSibling = x->rightSibling;
    if (x->leftChild != NULL)
    {
        x->leftChild = reverse(x->leftChild);
        (x->leftChild)->rightSibling = NULL;
    }
    head = Union(head, Hr);
    return x;
}
 */

int DecreaseKey(node H, int i, int k)
{
    int temp;
    node p;
    node y;
    node z;
    p = search(H, i);
    if (p == NULL)
    {
        printf("-1\n");
        return 0;
    }
    if (k > p->data)
    {
        printf("-1\n");
        return 0;
    }
    p->data = p->data - k;
    printf("%d\n", p->data);
    y = p;
    z = p->parent;
    while (z != NULL && y->data < z->data)
    {
        temp = y->data;
        y->data = z->data;
        z->data = temp;
        y = z;
        z = z->parent;
    }
}

int DELETE(node H, int k)
{
    node np;
    if (H == NULL)
    {
        return 0;
    }
    DecreaseKey(H, k, -9999);
    np = ExtractMin(H);
}
int main()
{
    int data;
    char choice = 'x';
    node HEAD = NULL;
    int dec, nodeKey;

    while (choice != 'e')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%d", &data);
            HEAD = Insert(HEAD, create_node(data));
            break;
        case 'p':
            printBinHeap(HEAD);
            printf("\n");
            break;
        case 'm':
            printf("%d\n", minimum(HEAD)->data);
            break;
        case 'x':
            HEAD = ExtractMin(HEAD);
            break;
        case 'r':
            scanf("%d", &dec);
            scanf("%d", &nodeKey);
            DecreaseKey(HEAD, dec, nodeKey);
            break;
        case 'd':
            scanf("%d", &nodeKey);
            DELETE(HEAD, nodeKey);
            break;
        default:
            break;
        }
    }
    return 0;
}

/* // SINGLE LINKED LIST (int rollnumber)

#include <stdio.h>
#include <stdlib.h>
struct node
{
    int rollnumber;
    struct node *next;
};
typedef struct node *node;

struct linkedlist
{
    struct node *head;
};
typedef struct linkedlist *linkedlist;

struct node *create_node(int x)
{
    node temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->rollnumber = x;
    temp->next = NULL;
    return temp;
}

void insert_front(linkedlist LList, node X)
{
    X->next = LList->head;
    LList->head = X;
}

struct node *search_list(linkedlist LList, int data)
{
    node temp = LList->head;
    while (temp != NULL && temp->rollnumber != data)
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
        printf("%d", temp->rollnumber);
        temp = temp->next;
        printf("\n");
    }
}

void main()
{
    int x;
    char choice = 'a';
    linkedlist LList;
    LList = (linkedlist)malloc(sizeof(linkedlist));
    node temp_main;
    LList->head = NULL;
    // printf("ENTER CHOICE!\n");
    while (choice != 'e')
    {
        scanf("%c", &choice);

        if (choice == 'a')
        {
            printf("CREATE NODE\n");
            scanf("%d", &x);
            temp_main = create_node(x);
            insert_end(LList, temp_main);
            // insert_front(LList, temp_main);
        }
        if (choice == 'p')
        {
            printf("PRINT LIST!\n");
            PRINT_LIST(LList);
            // printf("PRINT LIST END!\n");
        }
        if (choice == 's')
        {
            printf("SEARCH LIST!\n");
            scanf("%d", &x);
            temp_main = search_list(LList, x);
            printf("%d %d", temp_main->rollnumber, temp_main->next);
            printf("\n");
        }
        printf("ENTER CHOICE!\n");
    }
} */

/* //STRING TO BST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct Tnode *Tnode;
typedef struct Stack *Stack;

int stackEmpty(Stack S);
int stackFull(Stack S);
void PUSH(Stack S, long int k);
void POP(Stack S);
Tnode createNode(int val);
void printPreorder(Tnode root);
void getStr(char str[], char newStr[]);
int getEnd(char str[], int start, int end);
Tnode buildTree(char newStr[], int start, int end);

struct Tnode
{
    int data;
    Tnode left;
    Tnode right;
};

struct Stack
{
    long int A[10000];
    int top;
    int size;
};

int stackEmpty(Stack S)
{
    if (S->top == -1)
        return -1;
    else
        return 1;
}

int stackFull(Stack S)
{
    if (S->top == S->size - 1)
        return 1;
    else
        return 0;
}

void PUSH(Stack S, long int k)
{
    if (stackFull(S) == 1)
        return;
    else
    {
        // printf("%d\n",S->top);
        S->top = S->top + 1;
        // printf("%d\n",S->top);
        S->A[S->top] = k;
    }
}

void POP(Stack S)
{
    if (stackEmpty(S) == -1)
        // printf("-1\n");
        return;
    else
    {
        // printf("%d\n",S->top);
        // printf("%ld\n",S->A[S->top]);
        S->top = S->top - 1;
        // printf("%d\n",S->top);
    }
}

Tnode createNode(int val)
{
    Tnode root = (Tnode)malloc(sizeof(Tnode));
    root->left = NULL;
    root->right = NULL;
    root->data = val;
    return root;
}

void printPreorder(Tnode root)
{

    if (root != NULL)
    {

        printf("%d ", root->data);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void getStr(char str[], char newStr[])
{
    int i;
    int j = 0;
    for (i = 1; i < strlen(str) - 1; i++)
    {
        if (str[i] != ' ')
        {
            if (str[i] == '(' && str[i + 1] == ' ' && str[i + 2] == ')')

            {
                newStr[j] = str[i];
                newStr[j + 1] = 'X';
                newStr[j + 2] = str[i + 2];
                i = i + 2;
                j = j + 3;
            }
            else
            {
                newStr[j] = str[i];
                j++;
            }
        }
    }
    // printf("%s\n", newStr);
}

int getEnd(char str[], int start, int end)
{
    Stack S;
    int i;
    S = (Stack)malloc(sizeof(struct Stack));
    S->size = 10000;
    S->top = -1;
    if (start > end)
        return -1;
    for (i = start; i <= end; i++)
    {
        if (str[i] == '(')
            PUSH(S, str[i]);
        else if (str[i] == ')')
            if (S->A[S->top] = '(')
            {
                POP(S);
                if (stackEmpty(S) == -1)
                    return i;
            }
    }
    return -1;
}

Tnode buildTree(char newStr[], int start, int end)
{

    if (start > end)
        return NULL;

    Tnode root;
    int num = 0;
    int negative = 0;

    int k;
    if (newStr[start] == '-')
    {
        negative = 1;
        start++;
        // printf("in negative\n");
    }
    while (newStr[start] >= '0' && newStr[start] <= '9')
    {
        num *= 10;
        num = num + (newStr[start] - '0');
        start++;
    }
    start--;

    if (negative == 1)
        num = num * -1;
    // printf("%d ",num);

    if (newStr[start + 1] == 'X')
        root = NULL;
    else
        root = createNode(num);

    int i = -1;

    if (start + 1 <= end && newStr[start + 1] == '(')
        i = getEnd(newStr, start + 1, end);
    if (i != -1)
    {
        root->left = buildTree(newStr, start + 2, i - 1);
        root->right = buildTree(newStr, i + 2, end - 1);
    }
    return root;
}

int main()
{
    Tnode root = NULL;

    char op;
    long int k;

    char str[10000];
    char newStr[10000];
    scanf("%[^\n]", str);
    getStr(str, newStr);
    root = buildTree(newStr, 0, strlen(str) - 1);
    printPreorder(root);
    // checkBST(root);
} */
/*
#include <stdio.h>
#include <stdlib.h>
struct Qnode
{
    int data;
    struct Qnode *next;
};
typedef struct Qnode *Qnode;

struct QUEUE
{
    Qnode head, tail;
};
typedef struct QUEUE *QUEUE;

// change head and tail

Qnode CREATE_Qnode(int data)
{
    Qnode temp;
    temp = (Qnode)malloc(sizeof(Qnode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int QUEUEEMPTY(QUEUE Q)
{
    if (Q->head == NULL)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void ENQUEUE(QUEUE Q, int data)
{
    Qnode new_Qnode = CREATE_Qnode(data);
    if (Q->head == NULL)
    {
        Q->head = new_Qnode;
        Q->tail = new_Qnode;
    }
    else
    {
        Q->tail->next = new_Qnode;
        Q->tail = new_Qnode;
    }
}

void DEQUEUE(QUEUE Q)
{
    if (QUEUEEMPTY(Q) == -1)
    {
        printf("-1\n");
        return;
    }
    else
    {
        Qnode temp_Qnode = Q->head;
        printf("%d\n", temp_Qnode->data);
        if (Q->head == Q->tail)
        {
            Q->head = NULL;
            Q->tail = NULL;
        }
        else
        {
            Q->head = Q->head->next;
        }
        free(temp_Qnode);
    }
}

void print_queue(QUEUE Q)
{
    Qnode temp = Q->head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void)
{
    QUEUE Q;
    Q = (QUEUE)malloc(sizeof(QUEUE));
    Q->head = NULL;
    Q->tail = NULL;
    int data;
    char choice;
    scanf("%c", &choice);
    while (choice != 't')
    {
        switch (choice)
        {
        case 'i':
            // printf("START PUSH!\n");
            scanf("%d", &data);
            ENQUEUE(Q, data);
            // printf("END PUSH!\n");
            break;

        case 'd':
            DEQUEUE(Q);
            break;

        case 'p':
            print_queue(Q);
            break;

        case 'e':
            if (QUEUEEMPTY(Q) == 1)
                printf("1\n");
            else
                printf("-1\n");
            break;

        default:
            break;
        }
        scanf("%c", &choice);
    }
    return 0;
} */