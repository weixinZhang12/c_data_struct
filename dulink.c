#include <stdio.h>
#include <stdlib.h>
// 前后指针为同一个的节点代表头节点，

typedef struct DulNode
{
    int value;
    struct DulNode *prior;
    struct DulNode *next;

} DulNode;

typedef struct DulLink
{
    DulNode *head;
} DulLink;

// 创建链表
DulLink *new_link()
{
    DulLink *list = malloc(sizeof(DulLink));
    list->head = NULL;
}

// 新建双向链表节点
DulNode *new_dulNode()
{
    DulNode *list = malloc(sizeof(DulNode));
    list->value = 0;
    list->prior = list;
    list->next = list;
    return list;
}

// 向链表末尾添加元素
void push(DulLink *list, int value)
{
    DulNode *new_node = new_dulNode();
    new_node->value = value;
    DulNode *current_node = list->head;
    if (list->head == NULL)
    {
        list->head = new_node;
        return;
    }

    // 当前节点的下一个节点为头节点的时候，证明是最后一个元素，
    while (current_node->next != list->head)
    {
        current_node = current_node->next;
    }

    current_node->next = new_node;
    new_node->next = list->head;
    new_node->prior = current_node;
    current_node->prior = new_node;
}

void print_dullink(DulLink *list)
{
    DulNode *current_node = list->head;
    if (current_node == NULL)
    {
        printf("None\n");
        return;
    }

    // 打印直到最后一个节点
    while (current_node->next != list->head)
    {
        printf("%d<-->", current_node->value);
        current_node = current_node->next;
    }
    printf("%d<-->\n", current_node->value);
}

void free_list(DulLink *list)
{
    DulNode *left = NULL;
    DulNode *right = list->head;
    if (right == NULL)
    {
        return;
    }

    while (right != list->head)
    {
        left = right;
        free(left);
        left = NULL;
        right = right->next;
    }
    list->head = NULL;
}

int main(int argc, char const *argv[])
{
    DulLink *list = new_link();
    push(list, 1);
    push(list, 2);
    push(list, 3);
    print_dullink(list);
    free_list(list);
    print_dullink(list);

    return 0;
}
