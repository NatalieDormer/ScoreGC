#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define RANK_COUNT_MAX (5)

typedef struct _GAME_INFO {
    int     gameNo;
    bool    isMaleGame;
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
    bool    isMale;
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
static bool ListCheckRep_GameNo(GAME_LIST* src, GAME_LIST* cur);
static bool ListCheckRep_PlayerNo(PLAYER_LIST* src, PLAYER_LIST* cur);

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
    scanf("%d",&count);
    head->famaleGameCount = count;
    head->gameTotalCount = head->famaleGameCount + head->maleGameCount;

    /* info input*/
    GAME_LIST* p = head;
    head->next = NULL;
    head->pre = NULL;
    int i = 0;
    for(; i < head->maleGameCount; i++) {
        GAME_LIST* cur = (GAME_LIST*)malloc(sizeof(GAME_LIST));
        if(NULL == cur) {
            return cur;
        }
        memset(cur, 0x00, sizeof(GAME_LIST));
        cur->info.isMaleGame = true;

        printf("Input %dth Male GameNo:", i + 1);
        scanf("%d", &(cur->info.gameNo));
        while(true == ListCheckRep_GameNo(head, cur)) {
            printf("[Error! GameNo Exist, Please Input Another]:");
            scanf("%d", &(cur->info.gameNo));
        }

        printf("Input %dth Male Record Count(3 or 5):", i + 1);
        scanf("%d",&(cur->info.rankCount));
        while(!(cur->info.rankCount == 3 || cur->info.rankCount == 5)) {
            printf("[Error! Please Input 3 or 5]:");
            scanf("%d",&(cur->info.rankCount));
        }
        p->next = cur;
        cur->pre = p;
        cur->next = NULL;
        p = cur;
    }

    for(i = head->maleGameCount; i < head->gameTotalCount; i++) {
        GAME_LIST* cur = (GAME_LIST*)malloc(sizeof(GAME_LIST));
        if(NULL == cur) {
            return cur;
        }
        memset(cur, 0x00, sizeof(GAME_LIST));
        cur->info.isMaleGame = true;

        printf("Input %dth Famale Game No:", i + 1 - head->maleGameCount);
        scanf("%d", &(cur->info.gameNo));
        while(true == ListCheckRep_GameNo(head, cur)) {
            printf("[Error! GameNo. Exist, Please Input Another]:");
            scanf("%d", &(cur->info.gameNo));
        }

        printf("Input %dth Famale Record Count(3 or 5):", i + 1 - head->maleGameCount);
        scanf("%d",&(cur->info.rankCount));
        while(!(cur->info.rankCount == 3 || cur->info.rankCount == 5)) {
            printf("[Error! Please Input 3 or 5]:");
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
        printf("[Error! Please input another(>0)]:");
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

        printf("Input Player No:");
        scanf("%d", &(cur->info.playerNo));
        while(true == ListCheckRep_PlayerNo(head, cur)) {
            printf("[Error! PlayerNo. Exist, Please Input Another PlayerNo]:");
            scanf("%d", &(cur->info.playerNo));
        }

        char sex;
        printf("Input Player Sex(f,m):");
        scanf("%c", &sex);
        while(!('f' == sex || 'm' == sex)) {
            printf("[Error! Please Input 'f' or 'm']:");
            scanf("%c", &sex);
        }
        if('f' == sex) {
            cur->info.isMale = false;
        }
        else if('m' == sex) {
            cur->info.isMale = true;
        }
        else {
            ;
        }

        printf("Input Player School No:");
        scanf("%d", &(cur->info.schoolNo));
        while(cur->info.schoolNo < 0) {
            printf("[Error! Please Input SchoolNo(>=0)]:");
            scanf("%d", &(cur->info.schoolNo));
        }

        p->next = cur;
        cur->pre = p;
        cur->next = NULL;
        p = cur;
    }

    return head;
}

static bool ListCheckRep_GameNo(GAME_LIST* src, GAME_LIST* cur)
{
    bool ret = false;
    GAME_LIST* p = src;
    while(NULL != p) {
        if(p->info.gameNo == cur->info.gameNo) {
            ret = true;
            break;
        }
        p = p->next;
    }
    return ret;
}

static bool ListCheckRep_PlayerNo(PLAYER_LIST* src, PLAYER_LIST* cur)
{
    bool ret = false;
    PLAYER_LIST* p = src;
    while(NULL != p) {
        if(p->info.playerNo == cur->info.playerNo) {
            ret = true;
            break;
        }
        p = p->next;
    }
    return ret;
}









int main(void)
{
    //printf("!!!!!!!");
    gameList = GameListCreate(gameList);
    playerList = PlayerListCreate(playerList);


    return 0;
}

