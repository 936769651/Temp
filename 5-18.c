#include<stdio.h>
void strmove(char input[],int i);
int main()
{	
	int i;
	int have_wW = 0;
	char input[100];
	printf("输入: ");
	fgets(input,sizeof(input) - 1,stdin);	//scanf读取到空白即结束,所以使用fgets
	for(i = 0;input[i];i++)		//通过遍历统计有多少wW
	{
		if('w' == input[i] || 'W' == input[i])
			have_wW++;
	}
	printf("一共有%d个w\n",have_wW);
	for(i = 0;input[i];i++)
	{
		if('w' == input[i] || 'W' == input[i])
		{
			printf("分别在位置 ");
			printf("%d,",i);
			if('w' == input[i])	//如果是w，则替换为W
				input[i] = 'W';
			else			//如果是W,则将之后的每个字符前移一位
				for(int temp = i;input[temp];temp++)
					input[temp] = input[temp + 1];
			
		}
		
	}
	printf("\n%s\n",input);
}
void strmove(char input[],int i)
{
}
