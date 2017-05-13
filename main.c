#include <stdio.h>
#include <stdbool.h>

#define RANK_COUNT_MAX (5)

typedef struct _GAME_INFO {
    int     gameNo;
    bool    isMaleGame;
    int     rankCount;
    int     score[RANK_COUNT_MAX];
    int     playerRank[RANK_COUNT_MAX];
}GAME_INFO;

typedef struct _GAME_LIST {
    struct GAME_INFO* pre;
    struct GAME_LIST* next;
    int     gameTotalCount;
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
    struct PLAYER_INFO* pre;
    struct PLAYER_INFO* next;
    int     playerTotalCount;
}PLAYER_LIST;


static GAME_LIST* GameListCreate(GAME_LIST* p);
static PLAYER_LIST* PlayerListCreate(PLAYER_LIST* p);

GAME_LIST* gameList = NULL;
PLAYER_LIST* playerList = NULL;

static GAME_LIST* GameListCreate(GAME_LIST* p)
{

    return gameList;
}

static PLAYER_LIST* PlayerListCreate(PLAYER_LIST* p)
{
    ;
    return playerList;
}

int main(void)
{
    gameList = GameListCreate(gameList);
    playerList = PlayerListCreate(playerList);

    return 0;
}

