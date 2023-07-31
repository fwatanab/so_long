#include <stdio.h>
#include <stdbool.h>

/* グラフのサイズ */
#define GRAPH_SIZE 11

/* エッジの最大数 */
#define MAX_EDGE 4

/* 管理するデータの上限個数 */
#define MAX_NUM GRAPH_SIZE

#define QUEUE_SIZE (GRAPH_SIZE + 1)

/* 各ノードの位置情報 */
typedef struct POS {
    int i; /* ノードの位置 */
    int b_i; /* １つ前に辿ったノードの位置 */
} POS_T;

/* キュー構造体 */
typedef struct QUEUE {
    /* データの最後尾 */
    int tail;
    /* データの先頭 */
    int head;
    /* キューされているデータ */
    POS_T data[QUEUE_SIZE];
} QUEUE_T;

QUEUE_T queue;
POS_T trace[GRAPH_SIZE];
POS_T route[GRAPH_SIZE];

int graph[GRAPH_SIZE][MAX_EDGE];
int searched[GRAPH_SIZE];

/* グラフを作成する関数 */
void initGraph(void) {

    graph[0][0] = 1; graph[0][1] = 2; graph[0][2] = -1; graph[0][3] = -1;
    graph[1][0] = 3; graph[1][1] = 0; graph[1][2] = -1; graph[1][3] = -1;
    graph[2][0] = 0; graph[2][1] = 4; graph[2][2] = -1; graph[2][3] = -1;
    graph[3][0] = 1; graph[3][1] = 5; graph[3][2] = -1; graph[3][3] = -1;
    graph[4][0] = 2; graph[4][1] = 6; graph[4][2] = -1; graph[4][3] = -1;
    graph[5][0] = 3; graph[5][1] = -1; graph[5][2] = -1; graph[5][3] = -1;
    graph[6][0] = 7; graph[6][1] = 4; graph[6][2] = 8; graph[6][3] = -1;
    graph[7][0] = 9; graph[7][1] = 6; graph[7][2] = -1; graph[7][3] = -1;
    graph[8][0] = 6; graph[8][1] = -1; graph[8][2] = -1; graph[8][3] = -1;
    graph[9][0] = 7; graph[9][1] = 10; graph[9][2] = -1; graph[9][3] = -1;
    graph[10][0] = 9; graph[10][1] = -1; graph[10][2] = -1; graph[10][3] = -1;

}

/* キューを初期化する関数 */
void initQueue(QUEUE_T *queue){

    /* キューを空に設定 */
    queue->head = 0;
    queue->tail = -1;
}

/* ENQUEUEする関数 */
void enqueue(QUEUE_T *queue, POS_T *input){

    /* キューが満杯なら何もせず関数終了 */
    if((queue->tail + 2) % QUEUE_SIZE == queue->head){
        printf("キューが満杯でENQUEUEできません\n");
        return;
    }

    /* データをデータの最後尾の１つ後ろに格納 */
    queue->data[(queue->tail + 1) % QUEUE_SIZE] = *input;

    /* データの最後尾を１つ後ろに移動 */
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;
}

/* DEQUEUEする関数 */
POS_T *dequeue(QUEUE_T *queue){
    POS_T *ret;

    /* キューが空なら何もせずに関数終了 */
    if((queue->tail + 1) % QUEUE_SIZE == queue->head){
        printf("キューが空です\n");
        return NULL;
    }

    /* データの先頭からデータを取得 */
    ret = &(queue->data[queue->head]);

    /* データの先頭を１つ後ろにずらす */
    queue->head = (queue->head + 1) % QUEUE_SIZE;

    /* 取得したデータを返却 */
    return ret;
}


/* ゴールまでの経路を出力する関数 */
void printRoute(int num_trace) {

    int n;
    int count = 0;

    /* ゴールからスタートまでの経路をrouteに格納 */

    /* 最後に通過したノードの情報のtrace上の位置 */
    n = num_trace - 1;
    while (true) {

        POS_T pos = trace[n]; /* 通過したノードの情報を取得 */
        route[count] = pos; /* 通過したノードを覚えておく */
        count++;

        if (pos.b_i == -1) {
            /* 通過したノードスタートなら終了 */
            break;
        }


        for (int m = n - 1; m >= 0; m--) {
            /* posの前に通過したノードの情報が格納されているtrace上の位置を探索 */
            if (trace[m].i == pos.b_i) {
                /* posの前に通過した位置はtrace[m]に格納されている */
                n = m;
                break;
            }
        }
    }

    /* ゴールからスタートまでの経路を逆順に表示 */
    for (int m = count - 1; m >= 0; m --) {
        printf("%d,", route[m].i);
    }
    printf("\n\n");
}

/* スタートからゴールを探索する関数*/
bool search(int s_i, int g_i) {

    POS_T pos;
    int num_trace;
    bool ret;

    pos.i = s_i;
    pos.b_i = -1;

    enqueue(&queue, &pos); /* キューにノードの情報を格納*/

    num_trace = 0;

    while (true) {
        int i;

        /* キューから次の探索候補のノードを取得*/
        POS_T *next = dequeue(&queue);
        if (next == NULL) {
            /* 次の探索候補がない場合は探索失敗 */
            ret = false;
            break;
        }
        /* 探索するノードの座標を取得 */
        i = next->i;

        /* 探索するノードを探索済のノードとして覚えておく */
        trace[num_trace] = *next;
        num_trace++;

        if (i == g_i) {
            /* 探索対象が見つかったので探索成功 */
            printf("ゴールに到着\n");
            printRoute(num_trace);
            ret = true;
            break;
        }

        /* 探索済みのノードに印をつける */
        searched[i] = 1;

        for (int e = 0; e < MAX_EDGE; e++) {
            if (graph[i][e] != -1) {
                if (searched[graph[i][e]] != 1) {
                    pos.i = graph[i][e];
                    pos.b_i = i;
                    enqueue(&queue, &pos);
                }
            }
        }
    }

    return ret;
}

int main(void) {

    initQueue(&queue);

    initGraph();

    /* スタートの位置を0、ゴールの位置を10として開始 */
    if (search(0, 10)) {
        printf("ゴールが見つかりました！\n");
    } else {
        printf("ゴールが見つかりません！\n");
    }

    return 0;
}
