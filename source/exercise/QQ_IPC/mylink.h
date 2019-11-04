#ifndef _MYLINK_H_
#define _MYLINK_H_

typedef struct node *mylink;
struct node {
	char item[20];  //记录客户端名字
    int fifo_fd;    //该客户端使用的私有管道文件描述符(写端)
	mylink next;	//struct node *next;
};

void mylink_init(mylink *head);
mylink make_node(char *name, int fd);
void mylink_insert(mylink *head, mylink p);
mylink mylink_search(mylink *head, char *keyname);
void mylink_delete(mylink *head, mylink p);
void free_node(mylink p);
void mylink_destory(mylink *head);
void mylink_travel(mylink *head, void (*vist)(mylink));

#endif
