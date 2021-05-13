/*
链表功能描述：这套链表适用于相机音视频发送处理
*/

#ifndef __UTIL_LIST_H
#define __UTIL_LIST_H

#include <stddef.h>

struct list_head {
        struct list_head *prev, *next;
};

#define INIT_LIST_HEAD(name_ptr)        do {    (name_ptr)->next = (name_ptr); \
                                                (name_ptr)->prev = (name_ptr); \
                                        }while (0)

#define OFFSET(type, member)            (char *)&(((type *)0x0)->member)
#define container_of(ptr, type, member) ({                                      \
                        (type *)((char * )ptr - OFFSET(type, member)); });

#define list_for_each(pos, head)        for (pos = head->next; pos != head; pos = pos->next)
#define list_for_each_prev(pos, head)   for (pos = head->prev; pos != head; pos = pos->prev)
#define list_entry(ptr, type, member)   container_of(ptr, type, member)


//head -> tail node -> new
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
        head->prev->next = new; //tail node point to new
        new->prev = head->prev;	//new node point to tail node
        new->next = head;		//new point to head
        head->prev = new;		//head point to new
}

//head -> tail node -> new
static inline void list_add_tail1(struct list_head *new, struct list_head *head)
{
        new->next = head;		//new point to head
        new->prev = head->prev; //new point to tail node
        head->prev->next = new; //tail node point to new
        head->prev = new;  		//head point to new
}

//head -> new -> first node
static inline void list_add(struct list_head *new, struct list_head *head)
{
        new->next = head->next;
        new->prev = head;
        head->next->prev = new;
        head->next = new;
}

static inline void list_del(struct list_head *p)
{
        p->prev->next = p->next;
        p->next->prev = p->prev;
}

#endif

