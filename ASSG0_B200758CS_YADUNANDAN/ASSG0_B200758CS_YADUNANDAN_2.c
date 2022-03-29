// #include <stdio.h>
// #include <stdlib.h>
// struct QUEUE
// {
//     int *data;
//     int front, rear;
//     int size;
// };
// void ENQUEUE(struct QUEUE *Q, int value);
// int DEQUEUE(struct QUEUE *Q);
// int ISFULL(struct QUEUE Q);
// int ISEMPTY(struct QUEUE Q);
// int ISEMPTY(struct QUEUE Q)
// {
//     if (Q.rear == -1)
//         return 1;
//     else
//         return -1;
// }
// int ISFULL(struct QUEUE Q)
// {
//     if (Q.rear == Q.size - 1)
//         return 1;
//     else
//         return -1;
// }
// void ENQUEUE(struct QUEUE *Q, int value)
// {
//     if (ISEMPTY(*Q) == 1)
//     {
//         Q->front = 0;
//         Q->rear = 0;
//         Q->data[Q->rear] = value;
//     }
//     else
//         Q->data[++Q->rear] = value;
// }
// int DEQUEUE(struct QUEUE *Q)
// {
//     int del = Q->data[Q->front];
//     if (Q->front == Q->rear) // last element
//     {
//         Q->front++;
//         return del;
//     }
//     Q->front++;
//     return del;
// }
// int main()
// {
//     struct QUEUE Q;
//     scanf("%d", &Q.size);
//     Q.data = (int *)malloc(sizeof(int) * Q.size);
//     Q.front = -1;
//     Q.rear = -1;
//     char choice = 'x';
//     int data, deleted;
//     while (choice != 't')
//     {
//         scanf("%c", &choice);
//         switch (choice)
//         {
//         case 'i':
//             scanf("%d", &data);
//             if (ISFULL(Q) == 1)
//                 printf("1\n");
//             else
//                 ENQUEUE(&Q, data);
//             printf("front= %d\n", Q.front);
//             printf("rear = %d\n", Q.rear);
//             break;
//         case 'd':
//             if (ISEMPTY(Q) == 1 || Q.front > Q.rear)
//             {
//                 deleted = 1;
//             }
//             else
//             {
//                 deleted = DEQUEUE(&Q);
//             }
//             printf("%d\n", deleted);
//             printf("front= %d\n", Q.front);
//             printf("rear = %d\n", Q.rear);
//             break;
//         case 'e':
//             if (ISEMPTY(Q) == 1 || Q.front > Q.rear)
//                 printf("1\n");
//             else
//                 printf("-1\n");
//             break;
//         case 'f':
//             printf("%d\n", ISFULL(Q));
//             break;
//         case 'p':
//             for (int i = Q.front; i < Q.rear; i++)
//             {
//                 printf("%d ", Q.data[i]);
//             }
//             break;
//         default:
//             break;
//         }
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
struct QUEUE
{
    int *data;
    int front, rear;
    int size;
};

void ENQUEUE(struct QUEUE *Q, int value);
int DEQUEUE(struct QUEUE *Q);
int ISFULL(struct QUEUE Q);
int ISEMPTY(struct QUEUE Q);

int ISEMPTY(struct QUEUE Q)
{
    if (Q.rear == -1)
        return 1;
    else
        return -1;
}

int ISFULL(struct QUEUE Q)
{
    if (Q.rear == Q.size - 1)
        return 1;
    else
        return -1;
}

void ENQUEUE(struct QUEUE *Q, int value)
{
    if (ISEMPTY(*Q) == 1)
    {
        Q->front = 0;
        Q->rear = 0;
        Q->data[Q->rear] = value;
    }
    else
        Q->data[++Q->rear] = value;
}

int DEQUEUE(struct QUEUE *Q)
{
    int del = Q->data[Q->front];
    if (Q->front == Q->rear) // last element
    {
        Q->front = -1;
        Q->rear = -1;
        return del;
    }
    Q->front++;
    return del;
}

int main()
{
    struct QUEUE Q;

    scanf("%d", &Q.size);
    Q.data = (int *)malloc(sizeof(int) * Q.size);
    Q.front = -1;
    Q.rear = -1;

    char choice = 'x';
    int data, deleted;
    while (choice != 't')
    {
        scanf("%c", &choice);
        switch (choice)
        {
        case 'i':
            scanf("%d", &data);
            if (ISFULL(Q) == 1)
                printf("1\n");
            else
                ENQUEUE(&Q, data);
            break;
        case 'd':

            if (ISEMPTY(Q) == 1)
            {
                deleted = 1;
            }
            else
            {
                deleted = DEQUEUE(&Q);
            }
            printf("%d\n", deleted);
            break;

        case 'e':
            printf("%d\n", ISEMPTY(Q));
            break;

        case 'f':
            printf("%d\n", ISFULL(Q));
            break;
        default:
            break;
        }
    }
    return 0;
}
