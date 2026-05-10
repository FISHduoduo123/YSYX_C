#include "list.h"
#include "dbg.h"

List *List_create()
{
    List *list = calloc(1, sizeof(List));
    check_mem(list);

    // 初始化空链表容器
    list->count = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
    
    error:
        return NULL;
}

// 销毁链表，释放所有节点的内存
void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

// 清空链表，释放所有节点的值的内存，但保留链表结构
void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

// 销毁链表，先清空链表中的值的内存，再销毁链表结构
void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}


void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    
    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    // 如果删除的是唯一的节点
    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } 
    // 如果删除的是第一个节点
    else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } 
    // 如果删除的是最后一个节点
    else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } 
    // 如果删除的是中间的节点
    else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

// 插入指定节点后
void List_insert_after(List *list, ListNode *node, void *value)
{
    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    // 检查节点是否为链表中节点
    LIST_FOREACH(list, first, next, cur) {
        check(cur == node, "node is not in the list.");
    }
    
    if(node == list->last) {
        List_push(list, value);
    } else {
        ListNode *new_node = calloc(1, sizeof(ListNode));
        check_mem(new_node);

        new_node->value = value;
        new_node->next = node->next;
        new_node->prev = node;
        node->next->prev = new_node;
        node->next = new_node;

        list->count++;
    }   

    error:
        return NULL;
};