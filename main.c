#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define RANK_COUNT_MAX (5)

typedef struct _GAME_INFO {
    int     gameNo;
    char    sex;
    int     rankCount;
    int     score[RANK_COUNT_MAX];
    int     playerRank[RANK_COUNT_MAX];
}GAME_INFO;

typedef struct _GAME_LIST {
    GAME_INFO info;
    int     gameTotalCount;
    int     maleGameCount;
    int     famaleGameCount;
    struct GAME_INFO* pre;
    struct GAME_LIST* next;
}GAME_LIST;

typedef struct _PLAYER_INFO {
    int     playerNo;
    int     gameNo;
    char    sex;
    int     rank;
    int     score;
    int     schoolNo;
}PLAYER_INFO;

typedef struct _PLAYER_LIST {
    PLAYER_INFO info;
    int     playerTotalCount;
    struct PLAYER_INFO* pre;
    struct PLAYER_INFO* next;
}PLAYER_LIST;


static GAME_LIST* GameListCreate(GAME_LIST* head);
static PLAYER_LIST* PlayerListCreate(PLAYER_LIST* head);
static GAME_LIST* FindGameNode(GAME_LIST* game, int gameNo);
static PLAYER_LIST* FindPlayerNode(PLAYER_LIST* player, int playerNo);

GAME_LIST* gameList = NULL;
PLAYER_LIST* playerList = NULL;






static GAME_LIST* GameListCreate(GAME_LIST* head)
{
    /* count input */
    int count;
    head = (GAME_LIST*)malloc(sizeof(GAME_LIST));
    if(head == NULL) {
        return head;
    }
    printf("Input Male Game Total Count:");
    scanf("%d", &count);
    head->maleGameCount = count;
    printf("Input Famale Game Total Count:");
    scanf("%d", &count);
    head->famaleGameCount = count;
    head->gameTotalCount = head->famaleGameCount + head->maleGameCount;

    /* info input*/
    GAME_LIST* p = head;
    head->next = NULL;
    head->pre = NULL;
    int i = 0;
    for(; i < head->gameTotalCount; i++) {
        GAME_LIST* cur = (GAME_LIST*)malloc(sizeof(GAME_LIST));
        if(NULL == cur) {
            return cur;
        }
        memset(cur, 0x00, sizeof(GAME_LIST));

        /* game sex */
        if(i >= 0 && i < head->maleGameCount) {
            cur->info.sex = 'm';
        }
        else {
            cur->info.sex = 'f';
        }

        /* game no */
        printf("Input %dth %c GameNo:", i + 1, cur->info.sex);
        scanf("%d", &(cur->info.gameNo));
        while(NULL != FindGameNode(head, cur->info.gameNo)) {
            printf("[ERROR] GameNo Exist, Please Input Another:");
            scanf("%d", &(cur->info.gameNo));
        }

        /* record count */
        printf("Input %dth %c Game Record Count(3 or 5):", i + 1, cur->info.sex);
        scanf("%d",&(cur->info.rankCount));
        while(!(cur->info.rankCount == 3 || cur->info.rankCount == 5)) {
            printf("[Error] Please Input (3 or 5):");
            scanf("%d",&(cur->info.rankCount));
        }
        p->next = cur;
        cur->pre = p;
        cur->next = NULL;
        p = cur;
    }

    return head;
}

static PLAYER_LIST* PlayerListCreate(PLAYER_LIST* head)
{
    head = (PLAYER_LIST*)malloc(sizeof(PLAYER_LIST));
    if(head == NULL) {
        return head;
    }
    head->next = NULL;
    head->pre = NULL;
    printf("Input Player Count:");
    scanf("%d", &(head->playerTotalCount));
    while(head->playerTotalCount <= 0) {
        printf("[Error] Please input another(>0):");
        scanf("%d", &(head->playerTotalCount));
    }

    PLAYER_LIST* p = head;
    int i;
    for(i = 0; i < head->playerTotalCount; i++) {
        PLAYER_LIST* cur = (PLAYER_LIST*)malloc(sizeof(PLAYER_LIST));
        if(NULL == cur) {
            return cur;
        }
        memset(cur, 0x00, sizeof(PLAYER_LIST));

        /* player no */
        printf("Input Player No:");
        scanf("%d", &(cur->info.playerNo));
        while(NULL != FindPlayerNode(head, cur->info.playerNo)) {
            printf("[Error]PlayerNo. Exist, Please Input Another PlayerNo:");
            scanf("%d", &(cur->info.playerNo));
        }

        /* player sex */
        printf("Input Player Sex(f,m):");
        scanf("%c", &(cur->info.sex));
        while(!('f' == cur->info.sex || 'm' == cur->info.sex)) {
            printf("[Error] Please Input 'f' or 'm':");
            scanf("%c", &(cur->info.sex));
        }

        /* player school */
        printf("Input Player School No:");
        scanf("%d", &(cur->info.schoolNo));
        while(cur->info.schoolNo < 0) {
            printf("[Error] Please Input SchoolNo(>=0):");
            scanf("%d", &(cur->info.schoolNo));
        }

        p->next = cur;
        cur->pre = p;
        cur->next = NULL;
        p = cur;
    }

    return head;
}

static void* PlayerList_GameNo_Score(GAME_LIST* game, PLAYER_LIST* player)
{
    if(NULL == game || NULL == player) {
        return NULL;
    }
    //player
    int i;
    PLAYER_LIST* pp = player;
    for(i = 0, pp = pp->next; i < player->playerTotalCount; i++) {
        /* player's score */
        printf("Input Player[%d]'s Score:", pp->info.playerNo);
        scanf("%d", &(pp->info.score));
        while(pp->info.score < 0) {
            printf("[ERROR]Score < 0, Please Input Score >= 0:");
            scanf("%d", &(pp->info.score));
        }

        /* player's gameNo */
        printf("Input Player[%d]'s GameNo:", pp->info.playerNo);
        scanf("%d", &(pp->info.gameNo));






    }
}


static GAME_LIST* FindGameNode(GAME_LIST* game, int gameNo)
{
    GAME_LIST* p = game;
    while(p != NULL) {
        if(p->info.gameNo == gameNo) {
            return p;
        }
        p = p->next;
    }
    return p;
}

static PLAYER_LIST* FindPlayerNode(PLAYER_LIST* player, int playerNo)
{
    PLAYER_LIST* p = player;
    while(p != NULL) {
        if(p->info.playerNo == playerNo) {
            return p;
        }
        p = p->next;
    }
    return p;
}









int main(void)
{
    gameList = GameListCreate(gameList);
    playerList = PlayerListCreate(playerList);
   // PlayerList_GameNo_Score(gameList, playerList);

    return 0;
}

