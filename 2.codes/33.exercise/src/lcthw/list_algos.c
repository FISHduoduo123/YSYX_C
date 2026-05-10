#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

// 替换两个节点的值
inline void ListNode_swap(ListNode *a, ListNode *b)
{
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

// 冒泡排序算法
int List_bubble_sort(List *list, List_compare cmp)
{
    int sorted = 1;

    if(List_count(list) <= 1) {
        return 0;  // already sorted
    }

    do {
        sorted = 1;
        // 遍历列表，比较相邻节点的值，并根据比较结果交换节点的值
        LIST_FOREACH(list, first, next, cur) {
            if(cur->next) {
                // 如果当前节点的值大于下一个节点的值，则交换它们的值，并标记为未排序
                if(cmp(cur->value, cur->next->value) > 0) {
                    ListNode_swap(cur, cur->next);
                    sorted = 0;
                }
            }
        }
    } while(!sorted); // 如果在一次遍历中没有发生交换，说明列表已经排序完成，退出循环

    return 0;
}

// 合并两个已排序的列表
inline List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *val = NULL;

    while(List_count(left) > 0 || List_count(right) > 0) {
        // 比较左右两个列表的第一个元素，根据比较结果将较小的元素添加到结果列表中，并从原列表中移除该元素
        if(List_count(left) > 0 && List_count(right) > 0) {
            if(cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } 
        // 如果左列表还有元素，则将其添加到结果列表中
        else if(List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } 
        // 如果右列表还有元素，则将其添加到结果列表中
        else if(List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }
    // 销毁原列表，释放内存
    List_destroy(left);
    List_destroy(right);
    return result;
}

// 归并排序算法
List *List_merge_sort(List *list, List_compare cmp)
{
    // 如果列表为空或只有一个元素，返回原列表
    if(List_count(list) <= 1) {
        return list;
    }

    // 将列表分成两半
    List *left = List_create();
    List *right = List_create();
    // 计算中间位置
    int middle = List_count(list) / 2;

    // 遍历列表，将节点的值分配到左右两个列表中
    LIST_FOREACH(list, first, next, cur) {
        if(middle > 0) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }
        middle--;
    }

    // 递归地对左右两个列表进行归并排序
    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    // 如果排序后的列表与原始列表不同，则销毁原始列表
    if(sort_left != left) List_destroy(left);
    if(sort_right != right) List_destroy(right);

    // 返回合并后的结果列表
    return List_merge(sort_left, sort_right, cmp);
}

// 自下而上的归并排序算法
List *List_merge_sort_bottom_up(List *list, List_compare cmp)
{
    if (List_count(list) <= 1) {
        return list;
    }

    // 拆分为单节点链表
    int size = List_count(list);
    List **prev = calloc(size, sizeof(List*));
    for (int i = 0; i < size; i++) {
        prev[i] = List_create();
    }
    int idx = 0;
    LIST_FOREACH(list, first, next, cur) {
        List_push(prev[idx], cur->value);
        idx++;
    }
    int size_prev = size;

    //合并直到只剩一个链表
    while (size_prev > 1) {
        int new_size = (size_prev % 2) ? size_prev/2 + 1 : size_prev/2;
        List **curr = calloc(new_size, sizeof(List*));

        int i = 0;  // 索引 prev
        int j = 0;  // 索引 curr

        // 两两合并
        for (; j < new_size - (size_prev % 2); j++) {
            curr[j] = List_merge(prev[i], prev[i+1], cmp);
            prev[i] = NULL;      
            prev[i+1] = NULL;   
            i += 2;
        }
        // 奇数时剩余的一个链表
        if (size_prev % 2) {
            curr[j] = prev[i];
            prev[i] = NULL;      
        }
        // 销毁 prev 中所有剩余的链表
        for (int k = 0; k < size_prev; k++) {
            if (prev[k] != NULL) {
                List_clear_destroy(prev[k]);
            }
        }
        free(prev);

        prev = curr;
        size_prev = new_size;
    }

    List *sorted = prev[0];
    free(prev);
    return sorted;
}

// 接收一个值，将其插入到正确的位置，使链表有序
// 输入必须为有序链表
List *List_insert_sorted(List *list, void *value, List_compare compare)
{
    check(list != NULL, "List cannot be NULL.");
    
    ListNode *curr = list->first;
    // 如果链表为空，则直接将值插入到链表中
    if(curr == NULL) {
        List_push(list, value);
        return list;
    }
    // 遍历列表，找到第一个比value大的节点，并将value插入到该节点之前
    LIST_FOREACH(list, first, next, cur) {
        // 如果value小于当前节点的值
        if(compare(value, cur->value) < 0) {
            // 如果当前节点是链表的第一个节点，则将value插入到链表头部
            if (cur == list->first) {   
                List_unshift(list, value); // 将value插入到链表头部
                return list;
            }
            // 否则插入到当前节点之前
            else List_insert_after(list, cur->prev, value); 
            return list;
        }
        else if (compare(value, cur->value) == 0) {
            // 如果value等于当前节点的值，则将value插入到当前节点之后
            List_insert_after(list, cur, value);
            return list;
        }
    }

    // 如果没有找到比value更大的节点，则将value插入到链表末尾
    List_push(list, value);
    return list;

    error:
        return NULL;
};