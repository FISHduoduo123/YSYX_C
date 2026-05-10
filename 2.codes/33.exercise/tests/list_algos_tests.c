#include "minunit.h"
#include "../src/lcthw/list.h"
#include "../src/lcthw/list_algos.h"
#include <assert.h>
#include <string.h>
#include <time.h>

#define NUM_VALUES 10000
char *values[NUM_VALUES] ;


// 创建1000个测试元素
List *create_words()
{
    int i = 0;
    List *words = List_create();
    // 生成1000个随机字符串
    for(i = 0; i < NUM_VALUES; i++) {
        values[i] = malloc(sizeof(char) * 16);
        // 生成随机字符串，格式为 "word" + 随机数
        sprintf(values[i], "word%d", rand() % 10000);
        List_push(words, values[i]);
    }

    return words;
}

// 检查链表是否已排序
int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }
    // 已排序
    return 1;
}

char *test_bubble_sort()
{
    List *words = create_words();

    // should work on a list that needs sorting
    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();

    // should work on a list that needs sorting
    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort.");
    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);
    return NULL;
}

char *test_merge_sort_bottom_up()
{
    List *words = create_words();

    // should work on a list that needs sorting
    List *res = List_merge_sort_bottom_up(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort_bottom_up(words, (List_compare)strcmp);
    mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");
    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    // 测量冒泡排序的时间
    clock_t start = clock();
    mu_run_test(test_bubble_sort);
    clock_t end = clock();
    debug("Bubble sort time: %.9f", ((double)(end - start)) / CLOCKS_PER_SEC);

    // 测量归并排序的时间
    start = clock();
    mu_run_test(test_merge_sort);
    end = clock();
    debug("Merge sort time: %.9f", ((double)(end - start)) / CLOCKS_PER_SEC);

    // 测量自底而上的归并排序的时间
    start = clock();
    mu_run_test(test_merge_sort_bottom_up);
    end = clock();
    debug("Merge sort bottom up time: %.9f", ((double)(end - start)) / CLOCKS_PER_SEC);

    return NULL;
}

RUN_TESTS(all_tests);