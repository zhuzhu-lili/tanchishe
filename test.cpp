#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define U 1
#define D 2
#define L 3
#define R 4 //蛇的状态，U：上 ；D：下；L:左 R：右
typedef struct SNAKE{//蛇身的一个节点
	int x;
	int y;
	struct SNAKE*next;
}
	snake;//全局变量//
	int score=0,add=10;//总得分与每次吃食物的得分
	int status,sleeptime=200;//每次运行的时间间隔
	snake*head,*food;//蛇头指针，食物指针
	snake*q;//遍历蛇的时候用的指针
	int endgamestatus=0;//游戏介绍的情况，1；撞到墙；2：咬到自己；3：主动退出游戏；
//声明全部函数//
	void Pos();
	void creatMap();
	void initsnake();
	int biteself();
	void createdfood();
	void cantcrosswall();
	void snakemove();
	void pause();
	void gamecircle();
	void welcometogame();
	void endgame();
	void gamestart();

void Pos(int x,int y)//设置光标位置
{
	COORD pos;
	HANDLE hOutput;
	pos.X=x;
	pos.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,pos);
}

void creatMap()//创建地图
{
	int i;
	for(i=0; i<58; i+=2) { //打印上下边框
		Pos(i,0);
		printf("■");
		Pos(i,26);
		printf("■");
}
	for(i=1; i<26; i++) { //打印左右边框
		Pos(0,i);
		printf("■");
		Pos(56,i);
		printf("■");
}
}
	for(i=0; i<58; i+=2) { //打印上下边框
		Pos(i,0);
		printf("■");
		Pos(i,26);
		printf("■");
}
	for(i=1; i<26; i++) { //打印左右边框
		Pos(0,i);
		printf("■");
		Pos(56,i);
		printf("■");
}
}

void initsnake()//初始化蛇身
{
	snake *tail;
	int i;
	tail=(snake*)malloc(sizeof(snake));//从蛇尾开始，头插法，以x,y设定开始的位置//
	tail->x=24;
	tail->y=5;
	tail->next=NULL;
	for(i=1; i<=4; i++) {
		head=(snake*)malloc(sizeof(snake));
		head->next=tail;
		head->x=24+2*i;
		head->y=5;
		tail=head;
}
	while(tail!=NULL) { //从头到为，输出蛇身
		Pos(tail->x,tail->y);
		printf("■");
		tail=tail->next;
}
}

int biteself()//判断是否咬到了自己
{
	snake *self;
	self=head->next;
	while(self!=NULL) {
	if(self->x==head->x && self->y==head->y) {
	return 1;
}
	self=self->next;
}
	return 0;
}

void createfood()//随机出现食物
{
	snake *food_1;
	srand((unsigned)time(NULL));
	food_1=(snake*)malloc(sizeof(snake));
	while((food_1->x%2)!=0) { //保证其为偶数，使得食物能与蛇头对其
		food_1->x=rand()%52+2;
}
	food_1->y=rand()%24+1;
	q=head;
	while(q->next==NULL) {
		if(q->x==food_1->x && q->y==food_1->y) { //判断蛇身是否与食物重合
		free(food_1);
		createfood();
}
	q=q->next;
}
	Pos(food_1->x,food_1->y);
	food=food_1;
	printf("■");
}

void cantcrosswall()//不能穿墙
{
	if(head->x==0 || head->x==56 ||head->y==0 || head->y==26) {
	endgamestatus=1;
	endgame();
}
}

void snakemove()//蛇前进,上U,下D,左L,右R
{
	snake * nexthead;
	cantcrosswall();
	nexthead=(snake*)malloc(sizeof(snake));
	if(status==U) {
	nexthead->x=head->x;
	nexthead->y=head->y-1;
	if(nexthead->x==food->x && nexthead->y==food->y) { //如果下一个有食物//
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q!=NULL) {
	Pos(q->x,q->y);
	printf("■");
	q=q->next;
}
score=score+add;
createfood();
} else { //如果没有食物//
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q->next->next!=NULL) {
	Pos(q->x,q->y);
	printf("■");
	q=q->next;
}
	Pos(q->next->x,q->next->y);
	printf(" ");
	free(q->next);
	q->next=NULL;
}
}
	if(status==D) {
	nexthead->x=head->x;
	nexthead->y=head->y+1;
	if(nexthead->x==food->x && nexthead->y==food->y) { //有食物
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q!=NULL) {
	Pos(q->x,q->y);
	printf("■");
	q=q->next;
}
	score=score+add;
	createfood();
} else { //没有食物
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q->next->next!=NULL) {
	Pos(q->x,q->y);
	printf("■");
	q=q->next;
}
	Pos(q->next->x,q->next->y);
	printf(" ");
		free(q->next);
	q->next=NULL;
}
}
	if(status==L) {
	nexthead->x=head->x-2;
	nexthead->y=head->y;
		if(nexthead->x==food->x && nexthead->y==food->y) { //有食物
			nexthead->next=head;
			head=nexthead;
			q=head;
			Pos(q->x,q->y);
			printf("■");
			q=q->next;
}
score=score+add;
createfood();
} else { //没有食物
		nexthead->next=head;
		head=nexthead;
		q=head;
		while(q->next->next!=NULL) {
		Pos(q->x,q->y);
		printf("■");
		q=q->next;
}
		Pos(q->next->x,q->next->y);
		printf(" ");
		free(q->next);
		q->next=NULL;
}
}
if(status==R) {
	nexthead->x=head->x+2;
	nexthead->y=head->y;
if(nexthead->x==food->x && nexthead->y==food->y) { //有食物
	nexthead->next=head;
	head=nexthead;
	q=head;
while(q!=NULL) {
	Pos(q->x,q->y);
	printf("■");
	q=q->next;
}
	score=score+add;
	createfood();
} else { //没有食物
	nexthead->next=head;
	head=nexthead;
	q=head;
while(q->next->next!=NULL) {
	Pos(q->x,q->y);
	printf("■");
	q=q->next;
}
	Pos(q->next->x,q->next->y);
	printf(" ");
	free(q->next);
	q->next=NULL;
}


