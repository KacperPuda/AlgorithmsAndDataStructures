#include <iostream>
#define PIERSZYG '1'
#define DRUGIG '2'
#define PUSTE '0'
#define WYGTRUE -1
#define WYGFALSE 1
#define PLANSZAPELNA 0
#define XPOS 0
#define YPOS 1
using namespace std;





struct Game {
    int M=0;
    int N=0;
    int K=0;
    int ile1 = 0;
    int ile2 = 0;
    int naj = 0;
    char P= PUSTE;
    char P2 = PUSTE;
    char** tab=nullptr;
    int s[8][2];
};

void wypisz(Game game) {
    for (int i = 0; i < game.N; i++) {
        for (int j = 0; j < game.M; j++) printf("%c " , game.tab[i][j]);
        printf("\n");
    }
}

bool graSkonczona(Game game, int ii, int jj) {
    char obecny = game.tab[ii][jj];
    for (int i = 4; i < 8; i++) {
        int ip, jp, dl=0;
        if (ii + game.s[i][XPOS] >= game.N || (game.N - ii < game.K && game.s[i][XPOS] != 0)) return false;
        if (jj + game.s[i][YPOS] >= game.M || jj + game.s[i][YPOS] < 0 || (game.s[i][YPOS] > 0 && game.M - jj < game.K)) continue;
        if (game.tab[ii + game.s[i][XPOS]][jj + game.s[i][YPOS]] != obecny) continue;
        if (ii - game.s[i][XPOS] >= 0 && jj - game.s[i][YPOS] >= 0) if (game.tab[ii - game.s[i][XPOS]][jj - game.s[i][YPOS]] == obecny) continue;
        ip = ii;
        jp = jj;
        while (game.tab[ip][jp] == obecny) {
            dl++;
            ip += game.s[i][XPOS];
            jp += game.s[i][YPOS];
            if (dl >= game.K) return true;
            if (jp < 0 || ip >= game.N || jp >= game.M) break;
        }
    }
    return false;
}

char sprawdzenie(Game game,char p) {
    for (int i = 0; i < game.N; i++) {
        for (int j = 0; j < game.M; j++) {
            if (game.tab[i][j] != PUSTE && game.tab[i][j]!=p) {
                if (graSkonczona(game, i, j)) {
                    return game.tab[i][j];
                }
            }
        }
    }
    return PUSTE;
}

void generujPosuniecia(Game game, int ktore,int &ii,int &jj) {
    int l=0;
    for (int i = 0; i < game.N; i++) {
        for (int j = 0; j < game.M; j++) {
            if (game.tab[i][j] == PUSTE) {
                if (ktore == l) {
                    ii = i;
                    jj = j;
                    game.tab[i][j] = game.P;
                    return;
                }
                l++;
           }
        }
    }
}

void czyWygrana(Game &game, int ii, int jj) {
    char obecny = game.tab[ii][jj],przeciwny;
    if (obecny == PIERSZYG) przeciwny = DRUGIG;
    else przeciwny = PIERSZYG;
    game.naj = 0;
    for (int i = 0; i < 4; i++) {
        int ip, jp, dl = 0,zRzedu=0;
        ip = ii;
        jp = jj;
        bool byloPuste = false;
        while (ip + game.s[i][XPOS] >= 0 && jp + game.s[i][1] >= 0 && jp + game.s[i][1] < game.M && game.tab[ip][jp] == obecny) {
            ip += game.s[i][XPOS];
            jp += game.s[i][YPOS];
        }
        while (ip < game.N && jp >= 0 && jp < game.M) {
            if (game.tab[ip][jp] == obecny) {
                if(dl<game.K)dl++;
                zRzedu++;
            }
            else if (game.tab[ip][jp] == PUSTE){
                dl = zRzedu + 1;
                if (byloPuste && zRzedu == game.K - 1) dl = zRzedu + 2;
                zRzedu = 0;
                byloPuste = true;
            }
            else if (game.tab[ip][jp] == przeciwny) {
                dl = 0;
                zRzedu = 0;
                byloPuste = false;
            }
            if (dl > game.naj) game.naj = dl;
            ip -= game.s[i][XPOS];
            jp -= game.s[i][YPOS];
        }
    }

}

int minmax(Game game, bool player, int mozliwosci) {
    int mm, ii = 0, jj = 0;
    int najN = 0, najP = 0;

    for (int i = 0; i < game.N; i++) {
        for (int j = 0; j < game.M; j++) {
            if (game.tab[i][j] != PUSTE) {
                czyWygrana(game, i, j);
                if (game.tab[i][j] == game.P) {
                    if (najN < game.naj) najN = game.naj;
                }
                else {
                    if (najP < game.naj && !player) najP = game.naj;
                }
            }
        }
    }
    if (player) {
        if (najN >= game.K) return WYGTRUE;
        if (najP > game.K) return WYGFALSE;
        int min = 1;
        for (int i = 0; i < mozliwosci; i++) {
            generujPosuniecia(game, i, ii, jj);
            if (mozliwosci-1 == 0) mm= PLANSZAPELNA;
            else mm =minmax(game, false, mozliwosci - 1);
            if (min > mm) min = mm;
            game.tab[ii][jj] = PUSTE;
            if (min == -1) return min;
        }
        return min;
    }
    else {
        if (najP >= game.K)  return WYGFALSE;
        if (najN > game.K)  return WYGTRUE;
        int max = -1;
        for (int i = 0; i < mozliwosci; i++) {
            swap(game.P, game.P2);
            generujPosuniecia(game, i, ii, jj);
            swap(game.P, game.P2);
            if (mozliwosci-1 == 0) mm = PLANSZAPELNA;
            else mm = minmax(game, true, mozliwosci - 1);
            if (max < mm) max = mm;
            game.tab[ii][jj] = PUSTE;
            if (max == 1) return max;
        }
        return max;
    }
}

void usun(Game &game) {
    for (int i = 0; i < game.N; i++) delete[] game.tab[i];
    delete[] game.tab;
}

void generujWszystkie(Game game,int mozliwosci) {
    printf("%i \n", mozliwosci);
    for (int i = 0; i < mozliwosci; i++) {
        int ii = 0, jj = 0;
        generujPosuniecia(game, i, ii, jj);
        wypisz(game);
        game.tab[ii][jj] = PUSTE;
    }
}

void sprawdzenieCut(Game game,int mozliwosci,bool & wygenerowano) {
    for (int i = 0; i < mozliwosci; i++) {
        int ii = 0, jj = 0;
        generujPosuniecia(game, i, ii, jj);
        char kto = sprawdzenie(game, game.P2);
        if (kto == game.P) {
            wygenerowano = true;
            printf("1 \n");
            wypisz(game);
            game.tab[ii][jj] = PUSTE;
            return;
        }
        game.tab[ii][jj] = PUSTE;
    }
}

void rozstrzyganie(Game game,int mozliwosci) {
    char kto = sprawdzenie(game, PUSTE);
    if (kto == PIERSZYG) printf("FIRST_PLAYER_WINS \n");
    else if (kto == DRUGIG) printf("SECOND_PLAYER_WINS \n");
    if (kto != PUSTE) {
        return;
    }
    if (mozliwosci == PLANSZAPELNA) {
        printf("BOTH_PLAYERS_TIE \n");
        return;
    }
    int co;
    co = minmax(game, true, mozliwosci);
    if (co == 0)  printf("BOTH_PLAYERS_TIE \n");
    else if (game.P == PIERSZYG) {
        if (co == -1)  printf("FIRST_PLAYER_WINS \n");
        else printf("SECOND_PLAYER_WINS \n");
    }
    else {
        if (co == -1)  printf("SECOND_PLAYER_WINS \n");
        else printf("FIRST_PLAYER_WINS \n");
    }
}

void komendy(Game game, int mozliwosci, char komenda[]) {
    bool wygenerowano = true;
    if (strcmp("SOLVE_GAME_STATE", komenda) != 0) {
        char kto = sprawdzenie(game, PUSTE);
        if ((game.ile1 >= game.K || game.ile2 >= game.K) && (mozliwosci == PLANSZAPELNA || kto != PUSTE)) {
            printf("0 \n");
            usun(game);
            return;
        }
    }
    if (strcmp("GEN_ALL_POS_MOV_CUT_IF_GAME_OVER", komenda) == 0) {
        wygenerowano = false;
        sprawdzenieCut(game, mozliwosci, wygenerowano);
    }
    if (strcmp("GEN_ALL_POS_MOV", komenda) == 0 || !wygenerowano) generujWszystkie(game,mozliwosci);
    else if (strcmp("SOLVE_GAME_STATE", komenda) == 0) {
        rozstrzyganie(game,mozliwosci);
    }

    usun(game);
}

void generujPlansze(Game game,char komenda[]) {
    cin >> game.N >> game.M >> game.K >> game.P;
    if (game.P == PIERSZYG)game.P2 = DRUGIG;
    else game.P2 = PIERSZYG;
    int mozliwosci = 0;
    game.tab = new char* [game.N];

    for (int i = 0; i < game.N; i++) game.tab[i] = new char[game.M];
    for (int i = 0; i < game.N; i++) {
        for (int j = 0; j < game.M; j++) {
            cin >> game.tab[i][j];
            if (game.tab[i][j] == PUSTE) mozliwosci++;
            if (game.tab[i][j] == game.P) game.ile1++;
            if (game.tab[i][j] == game.P2) game.ile2++;
        }
    }
    komendy(game, mozliwosci, komenda);
}

void generujSasiadow(Game &game) {
    int z = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (j == 0 && i == 0) continue;
            game.s[z][XPOS] = i;
            game.s[z][YPOS] = j;
            z++;
        }
    }
}

int main()
{
    Game game;
    generujSasiadow(game);
    char komenda[33];
    while (cin >> komenda) {
        generujPlansze(game,komenda);
    }
    return 0;
}
