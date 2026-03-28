#include <stdio.h> //快慢指標
#include <stdlib.h>
#include <time.h>
#define list_len 10000
struct list_node
{
    int val;
    struct list_node *next;
};
struct list_node *middle_node(struct list_node *head)
{
    struct list_node *slow, *fast;
    slow = fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct list_node *create_random_list(int len, struct list_node **pool_ori_head)
{
    struct list_node *pool = malloc(len * sizeof(struct list_node)); // 記憶體池
    int *inx = malloc(len * sizeof(int));                            // 供打亂的索引
    for (int i = 0; i < len; i++)
        inx[i] = i;
    if (!pool || !inx)
    {
        fprintf(stderr, "記憶體分配失敗\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) // 賦值以供測試
        pool[i].val = i;
    for (int i = len - 1; i > 0; i--) // 使用Fisher-Yates Shuffle來打亂索引
    {
        int ran = (rand() % (i + 1));
        int temp = inx[i];
        inx[i] = inx[ran];
        inx[ran] = temp;
    }
    for (int i = 0; i < len - 1; i++) // 依隨機過的索引串接記憶體
    {
        pool[inx[i]].next = &pool[inx[i + 1]];
    }
    pool[inx[len - 1]].next = NULL;
    struct list_node *head = &pool[inx[0]];
    free(inx);
    *pool_ori_head = pool;
    return head;
}
int main()
{
    srand(time(NULL));
    struct list_node *pool_ori_head = NULL;
    struct list_node *head = create_random_list(list_len, &pool_ori_head);
    struct list_node *middle = middle_node(head);
    if (middle)
        printf("Middle Value: %d\n", middle->val);
    free(pool_ori_head);
    return 0;
}