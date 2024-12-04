#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define U 1
#define D 2
#define L 3
#define R 4 //�ߵ�״̬��U���� ��D���£�L:�� R����

typedef struct SNAKE { //�����һ���ڵ�
    int x;
    int y;
    struct SNAKE* next;
} snake;

// ȫ�ֱ��� //
int score = 0, add = 10; // �ܵ÷���ÿ�γ�ʳ��ĵ÷�
int status, sleeptime = 200; // ÿ�����е�ʱ����
snake* head, * food; // ��ͷָ�룬ʳ��ָ��
snake* q; // �����ߵ�ʱ���õ�ָ��
int endgamestatus = 0; // ��Ϸ���ܵ������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��

// ����ȫ������ //
void Pos(int x, int y); // ���ù��λ��
void creatMap(); // ������ͼ
void initsnake(); // ��ʼ������
int biteself(); // �ж��Ƿ�ҧ�����Լ�
void createfood(); // �������ʳ��
void cantcrosswall(); // ���ܴ�ǽ
void snakemove(); // ��ǰ��, ��U, ��D, ��L, ��R
void pause(); // ��ͣ
void gamecircle(); // ������Ϸ
void welcometogame(); // ��ʼ����
void endgame(); // ������Ϸ
void gamestart(); // ��Ϸ��ʼ��

void Pos(int x, int y) {
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void creatMap() {
    int i;
    for (i = 0; i <= 56; i += 2) { // ��ӡ���±߿�
        Pos(i, 0);
        printf("��");
        Pos(i, 26);
        printf("��");
    }
    for (i = 0; i <= 26; i++) { // ��ӡ���ұ߿�
        Pos(0, i);
        printf("��");
        Pos(56, i);
        printf("��");
    }
}

void initsnake() {
    snake* tail;
    int i;
    tail = (snake*)malloc(sizeof(snake)); // ����β��ʼ��ͷ�巨����x,y�趨��ʼ��λ��//
    tail->x = 24;
    tail->y = 5;
    tail->next = NULL;
    for (i = 1; i <= 4; i++) {
        head = (snake*)malloc(sizeof(snake));
        head->next = tail;
        head->x = 24 + 2 * i;
        head->y = 5;
        tail = head;
    }
    while (tail != NULL) { // ��ͷ��β���������
        Pos(tail->x, tail->y);
        printf("��");
        tail = tail->next;
    }
}

int biteself() {
    snake* self = head->next;
    while (self != NULL) {
        if (self->x == head->x && self->y == head->y) {
            return 1;
        }
        self = self->next;
    }
    return 0;
}

void createfood() {
    free(food); // �ͷ�֮ǰ��food�ڴ�
    food = (snake*)malloc(sizeof(snake));

    srand(time(NULL));

    do {
        food->x = rand() % 28 * 2 + 2; // ȷ��ʳ�ﲻ������ڱ߽�
        food->y = rand() % 13 + 1;
    } while (checkSnakePosition(food->x, food->y)); // ȷ��ʳ�ﲻ��������

    Pos(food->x, food->y);
    printf("��");
}

int checkSnakePosition(int x, int y) {
    snake* temp = head;
    while (temp != NULL) {
        if (temp->x == x && temp->y == y) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void cantcrosswall() {
    if (head->x <= 0 || head->x >= 56 || head->y <= 0 || head->y >= 26) {
        endgamestatus = 1;
        endgame();
    }
}

void snakemove() {
    snake* nexthead;
    cantcrosswall();
    nexthead = (snake*)malloc(sizeof(snake));
    nexthead->next = head;

    switch (status) {
        case U:
            nexthead->x = head->x;
            nexthead->y = head->y - 1;
            break;
        case D:
            nexthead->x = head->x;
            nexthead->y = head->y + 1;
            break;
        case L:
            nexthead->x = head->x - 2;
            nexthead->y = head->y;
            break;
        case R:
            nexthead->x = head->x + 2;
            nexthead->y = head->y;
            break;
    }

    if (nexthead->x == food->x && nexthead->y == food->y) { // �����һ����ʳ��
        nexthead->next = head;
        head = nexthead;
        q = head;
        while (q != NULL) {
            Pos(q->x, q->y);
            printf("��");
            q = q->next;
        }
        score += add;
        createfood();
    } else { // ���û��ʳ��
        nexthead->next = head;
        head = nexthead;
        q = head;
        while (q->next->next != NULL) {
            Pos(q->x, q->y);
            printf("��");
            q = q->next;
        }
        Pos(q->next->x, q->next->y);
        printf(" ");
        free(q->next);
        q->next = NULL;
    }

    if (biteself() == 1) { // �ж��Ƿ��ҧ���Լ�
        endgamestatus = 2;
        endgame();
    }
}

void pause() {
    while (1) {
        Sleep(300);
        if (GetAsyncKeyState(VK_SPACE)) {
            break;
        }
    }
}

void gamecircle() {
    Pos(64, 15);
    printf("���ܴ�ǽ������ҧ���Լ�\n");
    Pos(64, 16);
    printf("�á�.��.��.���ֱ�����ߵ��ƶ�.");
    Pos(64, 17);
    printf("F1 Ϊ���٣�F2 Ϊ����\n");
    Pos(64, 18);
    printf("ESC ���˳���Ϸ.space����ͣ��Ϸ.");
    Pos(64, 20);

    status = R;
    while (1) {
        Pos(64, 10);
        printf("�÷֣�%d ", score);
        Pos(64, 11);
        printf("ÿ��ʳ��÷֣�%d��", add);

        if (GetAsyncKeyState(VK_UP) && status != D) {
            status = U;
        } else if (GetAsyncKeyState(VK_DOWN) && status != U) {
            status = D;
        } else if (GetAsyncKeyState(VK_LEFT) && status != R) {
            status = L;
        } else if (GetAsyncKeyState(VK_RIGHT) && status != L) {
            status = R;
        } else if (GetAsyncKeyState(VK_SPACE)) {
            pause();
        } else if (GetAsyncKeyState(VK_ESCAPE)) {
            endgamestatus = 3;
            break;
        } else if (GetAsyncKeyState(VK_F1)) {
            if (sleeptime >= 50) {
                sleeptime -= 30;
                add += 2;
                if (sleeptime == 320) {
                    add = 2; // ��ֹ����1֮���ټӻ����д�
                }
            }
        } else if (GetAsyncKeyState(VK_F2)) {
            if (sleeptime < 350) {
                sleeptime += 30;
                add -= 2;
                if (sleeptime == 350) {
                    add = 1; // ��֤��ͷ�Ϊ1
                }
            }
        }

        Sleep(sleeptime);
        snakemove();
    }
}

void welcometogame() {
    Pos(40, 12);
    printf("��ӭ����̰ʳ����Ϸ��");
    Pos(40, 25);
    system("pause");
    system("cls");
    Pos(25, 12);
    printf("�á�.��.��.���ֱ�����ߵ��ƶ��� F1 Ϊ���٣�F2 Ϊ����\n");
    Pos(25, 13);
    printf("���ٽ��ܵõ����ߵķ�����\n");
    system("pause");
    system("cls");
}

void endgame() {
    system("cls");
    Pos(24, 12);
    if (endgamestatus == 1) {
        printf("�Բ�����ײ��ǽ�ˡ���Ϸ����.");
    } else if (endgamestatus == 2) {
        printf("�Բ�����ҧ���Լ��ˡ���Ϸ����.");
    } else if (endgamestatus == 3) {
        printf("�����Ѿ���������Ϸ��");
    }
    Pos(24, 13);
    printf("���ĵ÷���%d\n", score);
    exit(0);
}

void gamestart() {
    system("mode con cols=100 lines=30");
    welcometogame();
    creatMap();
    initsnake();
    createfood();
}

int main() {
    gamestart();
    gamecircle();
    endgame();
    return 0;
}




