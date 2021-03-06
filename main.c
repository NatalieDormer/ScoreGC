#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define RANK_COUNT_MAX (5)

typedef struct _GAME_INFO {
    int     gameNo;//
    char    sex;//
    int     rankCount;//
    int     score[RANK_COUNT_MAX];
    int     playerRank[RANK_COUNT_MAX];
}GAME_INFO;

typedef struct _GAME_LIST {
    GAME_INFO info;
    int     gameTotalCount;
    int     maleGameCount;
    int     famaleGameCount;
    struct _GAME_LIST* pre;
    struct _GAME_LIST* next;
}GAME_LIST;

typedef struct _PLAYER_INFO {
    int     playerNo;//
    int     gameNo;//
    char    sex;//
    int     rank;
    int     score;//
    int     schoolNo;//
}PLAYER_INFO;

typedef struct _PLAYER_LIST {
    PLAYER_INFO info;
    int     playerTotalCount;
    struct _PLAYER_LIST* pre;
    struct _PLAYER_LIST* next;
}PLAYER_LIST;


static GAME_LIST* GameListCreate(GAME_LIST* head);
static PLAYER_LIST* PlayerListCreate(PLAYER_LIST* head);
static PLAYER_LIST* PlayerListInit_GameNo_Score(GAME_LIST* game, PLAYER_LIST* player);
static GAME_LIST* GameListInit_Score_Rank(GAME_LIST* game, PLAYER_LIST* player);

static GAME_LIST* FindGameNode(GAME_LIST* game, int gameNo);
static PLAYER_LIST* FindPlayerNode(PLAYER_LIST* player, int playerNo);
static bool EnableJoinGame(PLAYER_LIST* player, GAME_LIST* game);
static PLAYER_LIST* DeleteNode_BaseOnGameNo(int no, PLAYER_LIST* list);

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
        memset(cur, 0, sizeof(GAME_LIST));

        /* game sex */
        if(i >= 0 && i < head->maleGameCount) {
            cur->info.sex = 'm';
        }
        else if(i >= head->maleGameCount && i < head->gameTotalCount){
            cur->info.sex = 'f';
        }

        /* game no */
        printf("Input %dth GameNo(%c):", i + 1, cur->info.sex);
        scanf("%d", &(cur->info.gameNo));
        while(NULL != FindGameNode(head, cur->info.gameNo)) {
            printf("[ERROR] GameNo Exist, Please Input Another:");
            scanf("%d", &(cur->info.gameNo));
        }

        /* record count */
        printf("Input %dth  Game(%c) Record Count(3 or 5):", i + 1, cur->info.sex);
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

static PLAYER_LIST* PlayerListInit_GameNo_Score(GAME_LIST* game, PLAYER_LIST* player)
{
    if(NULL == game || NULL == player) {
        return NULL;
    }

    int i;
    PLAYER_LIST* pp = player;
    for(i = 0, pp = pp->next; i < player->playerTotalCount; i++, pp = pp->next) {
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
        while(false == EnableJoinGame(pp, game)) {
            printf("Input Player[%d]'s GameNo Again:",pp->info.playerNo);
            scanf("%d", &(pp->info.gameNo));
        }
    }
    return player;
}


static GAME_LIST* GameListInit_Score_Rank(GAME_LIST* game, PLAYER_LIST* player)
{
    if(game == NULL || player == NULL) {
        return NULL;
    }

    //get playerlist who play this game
    GAME_LIST* pg;
    for(pg = game->next; pg != NULL; pg = pg->next) {
        PLAYER_LIST* tempPlayerList = (PLAYER_LIST*)malloc(sizeof(PLAYER_LIST) * (player->playerTotalCount + 1));// +1,because first node is head
        if(NULL == tempPlayerList) {
            return NULL;
        }
        memcpy(tempPlayerList, player, sizeof(PLAYER_LIST) * (player->playerTotalCount + 1));
        tempPlayerList = DeleteNode_BaseOnGameNo(pg->info.gameNo, tempPlayerList);
        if(tempPlayerList == NULL) {
            continue;
        }
        int i;
        PLAYER_LIST* pp;
        for(i = 0, pp = tempPlayerList->next; i < pg->info.rankCount, pp != NULL; i++, pp = pp->next) {
            pg->info.playerRank[i] = pp->info.playerNo;
            pg->info.score[i] = pp->info.score;
            printf("%d:playerNo=%d,score=%d",i,pg->info.playerRank[i],pg->info.score[i]);
        }
        free(tempPlayerList);
    }
    return game;
}

static PLAYER_LIST* DeleteNode_BaseOnGameNo(int no, PLAYER_LIST* list)
{
    if(NULL == list) {
        return list;
    }
    PLAYER_LIST* p = list;
    while(NULL != p->next) {
        if(p->next->info.gameNo != no) {
            PLAYER_LIST* temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        p = p->next;
    }
    return list;
}


static bool EnableJoinGame(PLAYER_LIST* player, GAME_LIST* game)
{
    bool enable = false;
    if(NULL == player || NULL == game) {
        return enable;
    }

    GAME_LIST* pgame = FindGameNode(game, player->info.gameNo);
    if(NULL == pgame) {
        printf("[ERROR]GameNo Not Exist,");
    }
    else {
        if(pgame->info.sex == player->info.sex) {
            enable = true;
        }
        else {
            printf("[ERROR]Sex ERROR! GameNo=%d is Sex=%c Game Error,",pgame->info.gameNo, player->info.sex);
        }
    }

    return enable;
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
    playerList = PlayerListInit_GameNo_Score(gameList, playerList);
    gameList = GameListInit_Score_Rank(gameList, playerList);

    return 0;
}

