#ifndef __DLIST_H
#define __DLIST_H

/* This file is from Linux Kernel (include/linux/list.h)
* and modified by simply removing hardware prefetching of list items.
* Here by copyright, credits attributed to wherever they belong.
* Kulesh Shanmugasundaram (kulesh [squiggly] isis.poly.edu)
*/

/*
* Simple doubly linked list implementation.
*
* Some of the internal functions (“__xxx”) are useful when
* manipulating whole lists rather than single entries, as
* sometimes we already know the next/prev entries and we can
* generate better code by using them directly rather than
* using the generic single-entry routines.
*/
/**
 * container_of - cast a member of a structure out to the containing structure
 *
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)			//偏移量宏定义

#define container_of(ptr, type, member) ({			\					//将结构的成员强制转换为包含结构
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member) );})

/*
 * 这些是非 NULL 指针，在正常情况下会导致页面错误，用于验证没有人使用未初始化的列表条目。
 */
#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200)


struct list_head														//小结构体定义
{
	struct list_head *prev;
	struct list_head *next;
};


#define LIST_HEAD_INIT(name) { &(name), &(name) }						//如下

#define LIST_HEAD(name) \												//宏定义LIST_HEAD(name)为 struct list_head name={ &name, &name }
struct list_head name = LIST_HEAD_INIT(name)


// 宏定义语法规定只能有一条语句
// 如果需要多条语句，那就必须将多条语句放入一个do{}while(0)中使之成为一条复合语句
#define INIT_LIST_HEAD(ptr) \											//新节点初始化
    do { \
    (ptr)->next = (ptr); \
    (ptr)->prev = (ptr); \
} while (0)


static inline void __list_add											//在两个已知的连续节点之间插入一个新节点
			   (struct list_head *new,
				struct list_head *prev,
				struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}


static inline void list_add(struct list_head *new, struct list_head *head)			//在一个已知节点之后插入一个新节点（头插）
{
	__list_add(new, head, head->next);
}



static inline void list_add_tail(struct list_head *new, struct list_head *head)		//在一个已知节点之前插入一个新节点（尾插）
{
	__list_add(new, head->prev, head);
}


static inline void __list_del(struct list_head *prev, struct list_head *next)		//通过使上一个/下一个条目相互指向来删除中间条目。
{
	next->prev = prev;
	prev->next = next;
}


/**
* list_del – deletes entry from list.									//通过使此条目的上一个和下一个条目相互指向来删除此条目。
* @entry: 指向要删除节点的指针
* Note: list_empty on entry does not return true after this, the entry is in an undefined state.
*/
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = (void *) 0;
	entry->prev = (void *) 0;
}


/**
* list_del_init – deletes entry from list and reinitialize it.		//删除此节点并初始化它
* @entry: 指向要删除节点的指针
*/
static inline void list_del_init(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}


/**
* list_move – delete from one list and add as another’s head		//将节点从一个列表中删除并添加为另一个列表的头节点之后
* @list: the entry to move
* @head: the head that will precede our entry
*/
static inline void list_move(struct list_head *list,
				struct list_head *head)
{
	__list_del(list->prev, list->next);
	list_add(list, head);
}


/**
* list_move_tail – delete from one list and add as another’s tail		//从一个列表中删除并添加为另一个列表的尾节点
* @list: the entry to move
* @head: the head that will follow our entry
*/
static inline void list_move_tail(struct list_head *list,
					struct list_head *head)
{
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
}


/**
* list_empty – tests whether a list is empty							//测试列表是否为空
* @head: the list to test.
*/
static inline int list_empty(struct list_head *head)
{
	return head->next == head;
}



/**
* __list_splice – join two lists
* @list: the new list to add.
* @head: the place to add it in the first list.
*/
//将list前节点与head之后节点拼接，将list后节点与head节点拼接（list被移除）
static inline void __list_splice(struct list_head *list,struct list_head *head)
{
	struct list_head *first = list->next;//指向list后一节点的指针
	struct list_head *last = list->prev;//指向list前一节点的指针
	struct list_head *at = head->next;//指向需延长的节点后一节点的指针

	first->prev = head;//list后一节点的prev指向head
	head->next = first;//目标节点的后一节点指向list的后一节点

	last->next = at;//list前一节点的next指向head的后一节点
	at->prev = last;//head的后一节点的prev指向list的前一节点
}


static inline void list_splice(struct list_head *list, struct list_head *head)		//若链表不为空则按上述拼接
{
if (!list_empty(list))
__list_splice(list, head);
}


static inline void list_splice_init(struct list_head *list,struct list_head *head)	//若list链表不为空则按上述拼接并初始化list
{
	if (!list_empty(list)) 
	{
		__list_splice(list, head);
		INIT_LIST_HEAD(list);
	}
}


/**
* list_entry – get the struct for this entry					//由小结构体地址获取大结构体地址（因为小结构体里的指针是指向前后结构体的小结构体，不能直接获取data数据）
* @ptr:    小结构体地址指针
* @type:   大结构体类型
* @member: 小结构体名
*/
#define list_entry(ptr, type, member) \
((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))


#define list_for_each(pos, head) \								//后序遍历
for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_prev(pos, head) \							//前序遍历
for (pos = (head)->prev; pos != (head); pos = pos->prev)


/**
* list_for_each_safe    -    循环访问列表，防止删除列表条目
* @pos:    &struct list_head用作循环计数器。
* @n:        另一个 &struct list_head用作临时存储
* @head:    the head for your list.
*/
#define list_for_each_safe(pos, n, head) \						//后序遍历（使用中间变量n记录pos）
for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

/*前序遍历安全模式*/
#define list_for_each_prev_safe(pos, n, head) \					//前序遍历（使用中间变量n记录pos）
for (pos = (head)->prev, n = pos->prev; pos != (head); \
pos = n, n = pos->prev)



#define list_for_each_entry(pos, head, member)              \			//后序遍历给定类型的列表
for (pos = list_entry((head)->next, typeof(*pos), member);	\
	&pos->member != (head);									\
	pos = list_entry(pos->member.next, typeof(*pos), member))




#define list_for_each_entry_safe(pos, n, head, member)            \		//后序遍历给定类型的列表，使用中间变量n，防止删除列表条目
for (pos = list_entry((head)->next, typeof(*pos), member), n = list_entry(pos->member.next, typeof(*pos), member);    \
	 &pos->member != (head);                     \
	 pos = n, n = list_entry(n->member.next, typeof(*n), member))

#endif
