#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define U 1
#define D 2
#define L 3
#define R 4 //�ߵ�״̬��U���� ��D���£�L:�� R����
typedef struct SNAKE{//�����һ���ڵ�
	int x;
	int y;
	struct SNAKE*next;
}
	snake;//ȫ�ֱ���//
	int score=0,add=10;//�ܵ÷���ÿ�γ�ʳ��ĵ÷�
	int status,sleeptime=200;//ÿ�����е�ʱ����
	snake*head,*food;//��ͷָ�룬ʳ��ָ��
	snake*q;//�����ߵ�ʱ���õ�ָ��
	int endgamestatus=0;//��Ϸ���ܵ������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��
//����ȫ������//
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

void Pos(int x,int y)//���ù��λ��
{
	COORD pos;
	HANDLE hOutput;
	pos.X=x;
	pos.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,pos);
}

void creatMap()//������ͼ
{
	int i;
	for(i=0; i<58; i+=2) { //��ӡ���±߿�
		Pos(i,0);
		printf("��");
		Pos(i,26);
		printf("��");
}
	for(i=1; i<26; i++) { //��ӡ���ұ߿�
		Pos(0,i);
		printf("��");
		Pos(56,i);
		printf("��");
}
}
	for(i=0; i<58; i+=2) { //��ӡ���±߿�
		Pos(i,0);
		printf("��");
		Pos(i,26);
		printf("��");
}
	for(i=1; i<26; i++) { //��ӡ���ұ߿�
		Pos(0,i);
		printf("��");
		Pos(56,i);
		printf("��");
}
}

void initsnake()//��ʼ������
{
	snake *tail;
	int i;
	tail=(snake*)malloc(sizeof(snake));//����β��ʼ��ͷ�巨����x,y�趨��ʼ��λ��//
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
	while(tail!=NULL) { //��ͷ��Ϊ���������
		Pos(tail->x,tail->y);
		printf("��");
		tail=tail->next;
}
}

int biteself()//�ж��Ƿ�ҧ�����Լ�
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

void createfood()//�������ʳ��
{
	snake *food_1;
	srand((unsigned)time(NULL));
	food_1=(snake*)malloc(sizeof(snake));
	while((food_1->x%2)!=0) { //��֤��Ϊż����ʹ��ʳ��������ͷ����
		food_1->x=rand()%52+2;
}
	food_1->y=rand()%24+1;
	q=head;
	while(q->next==NULL) {
		if(q->x==food_1->x && q->y==food_1->y) { //�ж������Ƿ���ʳ���غ�
		free(food_1);
		createfood();
}
	q=q->next;
}
	Pos(food_1->x,food_1->y);
	food=food_1;
	printf("��");
}

void cantcrosswall()//���ܴ�ǽ
{
	if(head->x==0 || head->x==56 ||head->y==0 || head->y==26) {
	endgamestatus=1;
	endgame();
}
}

void snakemove()//��ǰ��,��U,��D,��L,��R
{
	snake * nexthead;
	cantcrosswall();
	nexthead=(snake*)malloc(sizeof(snake));
	if(status==U) {
	nexthead->x=head->x;
	nexthead->y=head->y-1;
	if(nexthead->x==food->x && nexthead->y==food->y) { //�����һ����ʳ��//
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q!=NULL) {
	Pos(q->x,q->y);
	printf("��");
	q=q->next;
}
score=score+add;
createfood();
} else { //���û��ʳ��//
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q->next->next!=NULL) {
	Pos(q->x,q->y);
	printf("��");
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
	if(nexthead->x==food->x && nexthead->y==food->y) { //��ʳ��
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q!=NULL) {
	Pos(q->x,q->y);
	printf("��");
	q=q->next;
}
	score=score+add;
	createfood();
} else { //û��ʳ��
	nexthead->next=head;
	head=nexthead;
	q=head;
	while(q->next->next!=NULL) {
	Pos(q->x,q->y);
	printf("��");
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
		if(nexthead->x==food->x && nexthead->y==food->y) { //��ʳ��
			nexthead->next=head;
			head=nexthead;
			q=head;
			Pos(q->x,q->y);
			printf("��");
			q=q->next;
}
score=score+add;
createfood();
} else { //û��ʳ��
		nexthead->next=head;
		head=nexthead;
		q=head;
		while(q->next->next!=NULL) {
		Pos(q->x,q->y);
		printf("��");
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
if(nexthead->x==food->x && nexthead->y==food->y) { //��ʳ��
	nexthead->next=head;
	head=nexthead;
	q=head;
while(q!=NULL) {
	Pos(q->x,q->y);
	printf("��");
	q=q->next;
}
	score=score+add;
	createfood();
} else { //û��ʳ��
	nexthead->next=head;
	head=nexthead;
	q=head;
while(q->next->next!=NULL) {
	Pos(q->x,q->y);
	printf("��");
	q=q->next;
}
	Pos(q->next->x,q->next->y);
	printf(" ");
	free(q->next);
	q->next=NULL;
}


