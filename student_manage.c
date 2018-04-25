#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#define NAME 20

struct Student{
	int id;
	char name[NAME];
	float math;
	float english;
	float total;
	struct Student * next;
};
struct Student * get_secore();
void printf_end();
void free_student();
void add_student();	//添加一个学生
void add_students();
void find_name();
void del_student_by_id();
void order();
void getN();
int get_choose();

struct Student * Head;
int main()
{
	int choose;
	printf("输入学生信息格式 1 name 60 85\n");
	Head = get_secore();
	printf("学生信息初始化结束");
	printf_end();
	while(1)
	{
		choose = get_choose();
		if(6 == choose)
			break;
		switch (choose)
		{
			case 1:add_students();printf_end();break;
			case 2:add_student();printf_end();break;
			case 3:find_name();break;
			case 4:del_student_by_id();printf_end();break;
			case 5:order();printf_end();break;
			default:printf("没有这个选项\n");
		}
	}
	free_student();
	getchar();
	return 0;
}

void order()
{
	struct Student * pointList[100] = {NULL};
	struct Student * point = Head;
	int i = 0;
	int x,y;
	while(1)
	{
		pointList[i] = point;
		point = point->next;
		i++;
		if(NULL == point)
			break;
	}
	//此时i为学生数
	for(x = 0;x < i;x++)	//通过遍历对pointList指针进行排序
	{
		for(y = x+1;y < i;y++)
		{
			if(pointList[x]->total < pointList[y]->total)
			{
				point = pointList[x];
				pointList[x] = pointList[y];
				pointList[y] = point;
			}
		}
	}
	for(x = 0;x < i-1;x++)	//将pointList中的指针收尾相接，形成新的链表
	{
		pointList[x]->next = pointList[x+1];
	}
	pointList[x]->next = NULL;
	Head = pointList[0];//将列表的第一个地址给Head
}
void del_student_by_id()
{
	int id;
	struct Student * current;
	struct Student * previous;
	struct Student * next;
	printf("输入学号：");
	scanf("%d",&id);
	getN();
	//如果输入的id是第一个学生
	if(Head->id == id)
	{
		current = Head;	//将第一个地址保存
		Head = Head->next;	//将头地址改成下一个
		free(current);	//清空第一个地址
		return;
	}
	//否则
	previous = Head;
	while(true)
	{
			
		current = previous->next;
		if(current->id == id)
		{
			previous->next = current->next;
			printf("存在，删除成功\n");
			break;
		}
		previous = current;
	}
	
}
void find_name()
{
	char name[NAME];
	const struct Student * point = Head;
	bool have = false;
	printf("输入学生名称: ");
	scanf("%s",name);
	getN();

	while(1)
	{
		if(0 == strcmp(point->name,name))	//如果与查找的名字符合
		{
			printf("%d %20s %4.1f %4.1f %4.1f\n",point->id,point->name,point->math,point->english,point->total);
			have = true;
		}
		point = point->next;	//假设有重名的学生,继续便利
		if(NULL == point)
			break;
	}
	if(!have)
		printf("查无此人\n");
}
void add_student()	//添加一个学生
{
	int id;
	char name[NAME];
	float math,english;
	struct Student * point = Head;
	struct Student * last;
	struct Student * temp;
	while(1)	//通过遍历得到最后一个节点
	{
		if(NULL == point->next)
			break;
		point = point->next;
	}
	last = point;
	printf("输入学号 名字 数学 英语成绩:");
	scanf("%d %s %f %f",&id,name,&math,&english);
	getN();
	temp = (struct Student *)malloc(sizeof(struct Student));
	temp->id = id;
	strcpy(temp->name,name);
	temp->math = math;
	temp->english = english;
	temp->total = math + english;
	temp->next = NULL;

	last->next = temp; //将新的节点加入到链表结尾
}
int get_choose()
{
	int choose = 6;
	printf("1导入学生，输入0结束\n");
	printf("2追加一个学生\n");
	printf("3查询学生姓名\n");
	printf("4根据学号进行删除\n");
	printf("5排序输出\n");
	printf("6退出\n");
	printf("请输入你的选择: ");
	scanf("%d",&choose);
	getN();
	return choose;
}
void add_students()
{
	struct Student * last;
	struct Student * point = Head;
	struct Student * temp_head;
	while(1)
	{
		if(NULL == point->next)
			break;
		point = point->next;
	}
	last = point;
	temp_head = get_secore();
	last->next = temp_head;
}
struct Student * get_secore()
{
	int id;
	char name[NAME];
	float math,english;
	struct Student * temp;
	struct Student * head;
	struct Student * prev = NULL;
	while(1)
	{
		printf("输入学号 名字 数学 英语成绩 :");
		scanf("%d",&id);
		if(0 == id)
		{
			getN();
			break;
		}
		scanf("%s %f %f",name,&math,&english);
		getN();
		temp = (struct Student *)malloc(sizeof(struct Student));
		temp->id = id;
		strcpy(temp->name,name);
		temp->math = math;
		temp->english = english;
		temp->total = math + english;
		temp->next = NULL;
		if(NULL == prev)
		{
			head = temp;
			prev = temp;
		}else{
			prev->next = temp;
			prev = temp;
		}
	}
	return head;
}
void printf_end()
{
	struct Student * point = Head;
	printf("当前存储的学生资料\n");
	while(1)
	{
		printf("%d %20s %4.1f %4.1f %4.1f\n",point->id,point->name,point->math,point->english,point->total);
		point = point->next;
		if(NULL == point)
			break;
	}
}
void getN()	//获取多余的字符，直到读取到换行符
{
	while(getchar() != '\n')
		continue;
}
void free_student()
{
	struct Student * temp = Head;
	struct Student * cur;
	while(1)
	{
		cur = temp;
		temp = temp->next;
		if(NULL == temp)
			break;
		free(cur);
	}
	printf("清理成功\n");
}
