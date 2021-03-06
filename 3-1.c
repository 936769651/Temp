#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct numHead{
	int have;
	struct numBody * next;
};
struct numBody{
	int num;
	struct numBody * next;
};
void print_end(struct numHead * head);
void delete(struct numHead * head);
void order(struct numHead * head);
int main()
{
	srand((unsigned)time(NULL));
	int create;	//创建随机整数的次数
	int create_num;	//创建的随机整数
	struct numHead head = {0,NULL};	//初始化头结点
	struct numBody * point = NULL; //指向节点的指针
	struct numBody * previous = NULL; //指向节点的指针
	for(create = 0;create < 20;create++)
	{
		create_num = rand()%100;
		point = (struct numBody *)malloc(sizeof(struct numBody)); //生成指向一块内存的指针
		//为该节点赋值
		point->num = create_num;
		point->next = NULL;

		if(0 == create)
			head.next = point;
		else
			previous->next = point;
		head.have++;
		previous = point;
	}
	print_end(&head);
	delete(&head);
	printf("After delete:\n");
	print_end(&head);
	order(&head);
	return 0;
}
void order(struct numHead * head)
{
	struct numBody * pointList[30] = {NULL};
	struct numBody * pointTemp = head->next;
	int i = 0;
	int x,y;
	int have = head->have;
	while(1)
	{
		pointList[i] = pointTemp;
		pointTemp = pointTemp->next;
		if(NULL == pointTemp)
			break;
		i++;
	}
	for(x = 0;x < have;x++)	//通过遍历对pointList指针进行排序
	{
		for(y = x+1;y < have;y++)
		{
			if(pointList[x]->num < pointList[y]->num)
			{
				pointTemp = pointList[x];
				pointList[x] = pointList[y];
				pointList[y] = pointTemp;
			}
		}
	}

	for(x = 0;x < have;x++)	//将pointList中的指针收尾相接，形成新的链表
	{
		if(x == 0)
		{
			head->next = pointList[0];
			continue;
		}
		pointList[x - 1]->next = pointList[x];
	}
	pointList[x-1]->next = NULL;
	printf("排序结果: ");
	print_end(head);
	//for(x = 0;x < have;x++)
	//	printf("%d,",pointList[x]->num);
//	putchar('\n');
}
void delete(struct numHead * head)
{
	int del_x = 0;
	int i;
	printf("Input delete x: ");
	scanf("%d%*c",&del_x);
	printf("del_x = %d\n",del_x);
	struct numBody *previous = NULL;	//上一个节点地址
	struct numBody *pointTemp = head->next;	//符合条件的节点头地址
	head->next = NULL;
	while(1)
	{
		if(pointTemp->num == del_x)	//如果该节点的num等于del_x,则将跳过
		{
			head->have--;
			pointTemp = pointTemp->next;
			if(NULL == pointTemp)
				break;
			continue;
		}
		if(NULL == head->next)
		{
			head->next = pointTemp; //如果节点头地址为空，则将地一个不等于del_x的节点地址赋值给他
			previous = pointTemp; //保存当节点地址
			pointTemp = pointTemp->next;
			continue;
		}
		previous->next = pointTemp;
		previous = pointTemp; //保存当节点地址
		pointTemp = pointTemp->next;
		if(NULL == pointTemp)
			break;
	}
	previous->next = NULL;
}

void print_end(struct numHead * head)
{
	int have = head->have;
	int i = 0;
	struct numBody * point = head->next;
	while(1)
	{
		printf("%d,",point->num);
		point = point->next;
		if(NULL == point)
			break;
	}
	putchar('\n');
}
