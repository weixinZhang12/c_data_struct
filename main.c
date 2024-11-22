#include <stdio.h>
#include <stdlib.h>
typedef struct LinkNode
{
    int value;
    struct LinkNode *next;
} LinkNode;
typedef struct
{
    struct LinkNode *head;
} Linklist;
// 添加元素
Linklist *new_list()
{
    Linklist *list = malloc(sizeof(Linklist));
    list->head = NULL;
    return list;
}
void push(Linklist *list, int value)
{
    LinkNode *new_node = malloc(sizeof(LinkNode));
    // 内存分配失败
    if (!new_node)
    {
        printf("内存分配失败");
        return;
    }

    new_node->next = NULL;
    new_node->value = value;
    // 如果头节点为空，那么直接添加到头部节点
    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    // 否则查找空缺的位置，然后添加
    // 找到下一个节点为NULL的节点，然后在他的后面添加节点
    {
        LinkNode *current_node = list->head;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}
void free_list(Linklist *list)
{
    LinkNode *left = list->head;
    LinkNode *right = list->head;
    // 当月右侧的指针为NULL的时候，左侧指针刚好为最后一个节点
    while (right != NULL)
    {
        left = right;
        right = right->next;
        free(left);
    }
    // 头部指针切换为NUll
    list->head = NULL;
    free(list);
}
int pop(Linklist *list)
{
    LinkNode *right = list->head;
    LinkNode *left = list->head;
    // 头部节点为空时返回NUll
    if (list->head == NULL)
    {
        return NULL;
    }
    // 找到最后一个元素
    while (right->next != NULL)
    {
        left = right;
        right = right->next;
    }
    int temp = right->value;
    left->next = NULL;
    // 当头节点和左指针为同一个地址的时候，证明链表只有一个节点，此时可以将头节点的值设置为NULL
    if (list->head == right)
    {
        free(list->head);
        list->head = NULL;
        return temp;
    }

    free(right);
    right = NULL;
    return temp;
}
// 打印链表
void print_list(Linklist *list)
{
    LinkNode *curent_node = list->head;
    if (curent_node == NULL)
    {
        printf("None\n");
        return;
    }

    while (curent_node != NULL)
    {
        printf("%d ->", curent_node->value);
        curent_node = curent_node->next;
    }
}
void insertAtHead(Linklist *list, int value)
{
    LinkNode *new_node = malloc(sizeof(LinkNode));
    new_node->next = list->head;
    list->head = new_node;
}
int main(int argc, char const *argv[])
{
    Linklist *list = new_list();
    push(list, 12);
    push(list, 11);
    int a = pop(list);
    int b = pop(list);
    insertAtHead(list, 1);
    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", pop(list));
    print_list(list);

    return 0;
}
