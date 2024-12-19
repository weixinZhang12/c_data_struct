#include <iostream>
using namespace std;
class LinkNode
{
public:
    int value = 0;
    LinkNode *next = nullptr;
    LinkNode(int value)
    {
        this->value = value;
    }
    LinkNode()
    {
    }
    ~LinkNode()
    {
        // delete this->next;
    }
};
class LinkList
{
public:
    LinkNode *head = nullptr;
    unsigned int length = 0;
    LinkList()
    {
    }
    // 添加元素
    void push(int value)
    {
        LinkNode *new_node = new LinkNode(value);
        LinkNode *current_node = this->head;
        //			添加到头节点
        if (this->head == nullptr)
        {
            this->head = new_node;
            this->length += 1;
            return;
        }
        //			除了头节点之外的节点添加
        while (current_node->next != nullptr)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
        this->length += 1;
    }
    int pop_back()
    {
        LinkNode *right = this->head;
        LinkNode *left = nullptr;

        //			如果头节点为空直接跳过
        if (right == nullptr)
        {
            return -1;
        }
        // 当只有头节点有节点的时候需要删除需要将头节点置空
        if (right->next == nullptr)
        {
            int temp = right->value;
            delete right;
            right = nullptr;
            this->head = nullptr;
            return temp;
        }
        while (right->next != nullptr)
        {
            left = right;
            right = right->next;
        }
        int temp = right->value;
        delete right;
        right = nullptr;
        left->next = nullptr;
        return temp;
    }
    void delete_node_by_value(int value)
    {
        LinkNode *current = this->head;
        LinkNode *temp = nullptr;
        // current不能为nullptr
        while (current != nullptr && current->value != value)
        {
            temp = current;
            current = current->next;
        }
        if (current == nullptr)
        {
            cout << "没有找到符合条件的元素" << endl;
            return;
        }
        temp->next = current->next;
        delete current;
        current = nullptr;
    }
    // 打印链表元素
    void print_list()
    {
        LinkNode *current_node = this->head;
        while (current_node != nullptr)
        {
            cout << current_node->value << " ";
            current_node = current_node->next;
        }
    }

    bool is_empty()
    {
        return this->length == 0;
    }
    ~LinkList()
    {
        LinkNode *current = this->head;
        while (current != nullptr)
        {
            LinkNode *temp = current;
            current = current->next;
            delete temp;
        }
        this->head = nullptr; // 确保指针为 nullptr
    }
};
int main(int argc, char const *argv[])
{
    LinkList *list = new LinkList();
    list->push(12);
    list->push(13);
    list->push(1234);
    list->delete_node_by_value(13);
    list->print_list();

    delete list;
    // list=nullptr;
    // cout << list->pop_back() << endl;
    // cout << list->pop_back() << endl;
    // cout << list->pop_back() << endl;
    // cout << list->pop_back() << endl;

    return 0;
}
