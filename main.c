#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <time.h>
#define true_Const 1
#define false_Const !1
#define HP_Const 219                                                                          // Ascii code for HP
#define Box_Const 254                                                                         // Ascii code for Combo indication
#define Number_Const ((NumberToReturn_Char_Input >= 48) && (NumberToReturn_Char_Input <= 53)) // Allowed input for choosing cards

// For array size
#define Global_INT_F_Const 5   // Faction size
#define Global_INT_A_Const 7   // Agent size
#define Global_INT_T_Const 2   // Position of specific cards size
#define Global_INT_N_Const 29  // Total size of Cards
#define Global_INT_S_Const 100 // Maximum User Cards

void remove_scrollbar();
void Position(int Xcoordinate, int Ycoordinate);
void Delay(float Time);
void HideCursor();
void printf_utf8(const char *format, ...);
void fullscreen();
const char CardPickingUserInput();
HANDLE wHND; // Handle to write to the console.
HANDLE rHND; // Handle to read from the console.

void Title_Page();
void Game_Menu();
void GameTutorial();
void Game_plot();
void Art_Speechbox();
void Script_Print_byChar(char text[Global_INT_S_Const][Global_INT_S_Const], int line);
void Script_Print_byStr(char text[Global_INT_S_Const][Global_INT_S_Const], int line, int CharPos);
void LoadEpilogue(char text[Global_INT_S_Const][Global_INT_S_Const]);
void BossArt();
void Game_Tutorial();
void ShieldArt();
void AgentArt(int PositionX);
void FactionArt(int PositionX);
void AgreementArt();
void CardsAppearance();
void GameStart();
void Game_play();
void InitializeCards(int Cards[Global_INT_F_Const][Global_INT_A_Const], int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int TemporaryCards[Global_INT_F_Const][Global_INT_A_Const]);
void LoadCards(int Faction, int Agent, int PositionX);
void Game_Shuffle(int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int DrawnCard[Global_INT_F_Const][Global_INT_T_Const], int TemporaryCards[Global_INT_F_Const][Global_INT_T_Const]);
void Game_GetRandomCard(int *Faction, int *Agent);
void Game_CurrentUserCards(int Cards[Global_INT_F_Const][Global_INT_A_Const], int UserCards[Global_INT_S_Const][Global_INT_T_Const], int *TotalCards);
void Game_PrintBonus(int indication, int PositionY);
void Game_BossHp(float HitPoints);
float Compute_ATK(int Cards[Global_INT_F_Const][Global_INT_A_Const], int UserCards[Global_INT_S_Const][Global_INT_T_Const], int *TotalCards, int Compute_ATK_INT_FactionD, int Compute_ATK_INT_AgentD);
void GameGetNumberFactionAgents(int Cards[Global_INT_F_Const][Global_INT_A_Const], int Current[Global_INT_S_Const][Global_INT_T_Const], int Agent[Global_INT_A_Const], int Faction[Global_INT_F_Const], int FactionS, int AgentS, int *TotalCards);
void GameGetCombo(int AgentNum[Global_INT_A_Const], float AgentMultip[Global_INT_A_Const], int FactionNum[Global_INT_F_Const], float FactionMultp[Global_INT_F_Const]);
void BestTwoCards(int Cards[Global_INT_F_Const][Global_INT_A_Const], int UserCards[Global_INT_S_Const][Global_INT_T_Const], int *TotalCards, int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int DrawnCard[Global_INT_F_Const][Global_INT_T_Const]);
void Game_PickingCards(int Cards[Global_INT_S_Const][Global_INT_T_Const], int CurrentCards[Global_INT_S_Const][Global_INT_T_Const], int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int DrawnCard[Global_INT_F_Const][Global_INT_T_Const], int *TotalCards);
int UserInput();
void Game_AttackTransition(float UserAtk);
void Game_BossAttack();
void Game_GetBestCombo();
void InitializeNumberFactionAgents(int Agent[Global_INT_A_Const], int Faction[Global_INT_F_Const], float AgentM[Global_INT_A_Const], float FactionM[Global_INT_F_Const]);
void Game_Over();
void YouWIN();
void Game_UserAttackAnimation(float UserAtk);
void Game_OverCountdown();
void LoadCountDown(int *Number);
void BestCardIndicator(int PositionX);

int main()
{
    remove_scrollbar();

    fullscreen();

    SetConsoleTitle("Is it wrong to pick up cards to fight Mopongga-chan?");

    HideCursor();

    srand(time(NULL));

    HideCursor();

    Title_Page();

    Delay(1.5);

    Game_Menu();
    // Game_play();
}
void Title_Page()
{
    FILE *Title;
    char line[1000];
    int PositionY = 3;

    Title = fopen("src\\art\\TitlePage.txt", "r");

    while ((fgets(line, sizeof(line), Title)) != NULL)
    {
        Position(40, PositionY);
        printf_utf8("%s", line);
        PositionY++;
    }

    fclose(Title);
}
void Game_Menu()
{
    FILE *ptr;
    char line[1000];
    int Game_Menu_INT_Opt;
    int positionY = 30;

    system("cls");
    Title_Page();
    ptr = fopen("src\\art\\PLAY.txt", "r");

    while ((fgets(line, sizeof(line), ptr) != NULL))
    {
        Position(55, positionY);
        printf_utf8("%s", line);
        positionY++;
    }
    fclose(ptr);

    ptr = fopen("src\\art\\EXIT.txt", "r");
    positionY = 30;

    while ((fgets(line, sizeof(line), ptr) != NULL))
    {
        Position(95, positionY);
        printf_utf8("%s", line);
        positionY++;
    }
    fclose(ptr);
    Game_Menu_INT_Opt = getch() - '0';

    switch (Game_Menu_INT_Opt)
    {
    case 1:
        Game_plot();
        break;
    case 2:
        printf("Exiting...");
        exit(0);
        break;
    default:
        Game_Menu();
        break;
    }
}
void GameTutorial()
{
    FILE *ptr;
    int GGameTutorial_INT_Opt;
    char line[1000];
    int positionY = 10;

    system("cls");
    ptr = fopen("src\\art\\tutorial.txt", "r");

    while ((fgets(line, sizeof(line), ptr)) != NULL)
    {
        Position(30, positionY);
        printf_utf8("%s", line);
        positionY++;
    }
    GGameTutorial_INT_Opt = getch() - '0';

    switch (GGameTutorial_INT_Opt)
    {
    case 1:
        system("cls");
        Game_Tutorial();
        break;
    case 2:
        system("cls");
        GameStart();
        Delay(1);
        Game_play();
        break;
    default:
        GameTutorial();
        break;
    }
}
void Game_plot()
{
    char ScriptEpilogue[Global_INT_S_Const][Global_INT_S_Const];
    int Game_plot_INT_Skip;

    system("cls");
    LoadEpilogue(ScriptEpilogue);
    for (int x = 0; x < 20; x += 2)
    {
        Art_Speechbox();
        if (x == 16)
            x = 18;
        switch (x)
        {
        case 0:
            BossArt();
            break;
        case 2:
            ShieldArt();
            break;
        case 4:
            for (int y = 0; y < 7; y++)
                AgentArt(y);
            break;
        case 6:
            for (int y = 0; y < 7; y++)
                AgentArt(y);
            break;
        case 8:
            for (int y = 0; y < 5; y++)
                FactionArt(y);
            break;
        case 10:
            for (int y = 0; y < 5; y++)
                AgreementArt();
            break;
        case 12:
            for (int y = 0; y < 5; y++)
                CardsAppearance();
            break;
        case 14:
            for (int y = 0; y < 5; y++)
                CardsAppearance();
            break;
        case 16:
            for (int y = 0; y < 5; y++)
                CardsAppearance();
            break;
        case 18:
            for (int y = 0; y < 5; y++)
                CardsAppearance();
            break;
        case 20:
            for (int y = 0; y < 5; y++)
                CardsAppearance();
            break;
        }
        Position(54, 39);
        Script_Print_byChar(ScriptEpilogue, x);
        Game_plot_INT_Skip = getch();

        if (Game_plot_INT_Skip == 13)
            break;
        Position(54, 40);
        Script_Print_byChar(ScriptEpilogue, x + 1);
        Game_plot_INT_Skip = getch();

        if (Game_plot_INT_Skip == 13)
            break;
        getch();
        system("cls");
    }
    GameTutorial();
}
void Game_Tutorial()
{
    FILE *Tutorial;
    char line[10000];
    char pathfile[] = "";
    int opt;

    for (int x = 0; x < 5; x = x)
    {
        system("cls");
        sprintf(pathfile, "src\\tutorial\\%d.txt", x);
        Tutorial = fopen(pathfile, "r");
        while ((fgets(line, sizeof(line), Tutorial)) != NULL)
        {
            printf_utf8("%s", line);
        }
        fclose(Tutorial);
        opt = getch() - '0';

        if (opt == 1)
        {
            if (x <= 0)
                x = 0;
            else
                x--;
        }

        else if (opt == 2)
            x++;

        else if (opt != 1 || opt != 2)
            x = x;
    }
    GameStart();
}
void GameStart()
{
    FILE *GameStart_FILE_transition;
    char GameStart_STR_line[1000];
    int GameStart_INT_positionY = 10;

    GameStart_FILE_transition = fopen("src\\art\\GameSTART.txt", "r");
    system("cls");
    while ((fgets(GameStart_STR_line, sizeof(GameStart_STR_line), GameStart_FILE_transition)) != NULL)
    {
        Position(50, GameStart_INT_positionY);
        printf_utf8("%s", GameStart_STR_line);
        GameStart_INT_positionY++;
    }
    fclose(GameStart_FILE_transition);
    Delay(1.5);
    Game_play();
}
void Game_play()
{ // main function for game
    int Cards[5][7] = {{2, -1, 2, 2, 4, 2, -1}, {2, 1, 1, 2, 5, -1, 3}, {-1, 3, 4, 4, 1, 2, 1}, {1, 1, 3, 5, 3, 3, -1}, {3, 3, 1, 4, -1, -1, 1}};
    int TemporaryCards[5][7];
    int DisCarded[5][7];
    int DrawnCards[5][2];
    int CurrentCards[100][2];
    int TotalCurrentCards = 0;
    float BossHitPoints = 150.00;

    Delay(0.01);

    InitializeCards(Cards, DisCarded, TemporaryCards);

    for (int x = 0; BossHitPoints > 0; x++)
    {

        if (TotalCurrentCards % 3 == 0)
            InitializeCards(Cards, DisCarded, TemporaryCards);

        Game_Shuffle(DisCarded, DrawnCards, TemporaryCards);

        for (int y = 0; y < 2; y++)
        {
            system("cls");

            BossArt();

            Game_BossHp(BossHitPoints);

            Game_CurrentUserCards(Cards, CurrentCards, &TotalCurrentCards);

            BestTwoCards(Cards, CurrentCards, &TotalCurrentCards, DisCarded, DrawnCards);

            Game_PickingCards(Cards, CurrentCards, DisCarded, DrawnCards, &TotalCurrentCards);
        }
        // Exchange of attacks
        ////User Attack
        system("cls");
        BossArt();

        Game_BossHp(BossHitPoints);

        Game_CurrentUserCards(Cards, CurrentCards, &TotalCurrentCards);

        Game_UserAttackAnimation(Compute_ATK(Cards, CurrentCards, &TotalCurrentCards, -1, -1));

        Delay(1.5);

        BossHitPoints -= (Compute_ATK(Cards, CurrentCards, &TotalCurrentCards, -1, -1));

        Game_BossHp(BossHitPoints);

        // InitializeCards(Cards, DisCarded, TemporaryCards);
    }
    if (BossHitPoints <= 0)
    { // player won
        system("cls");

        Game_BossHp(0);

        YouWIN();

        Delay(1.5);

        system("cls");

        Game_Over();

        Delay(1.5);

        Game_OverCountdown();
    }
}
void Game_UserAttackAnimation(float UserAtk)
{ // indication of attack
    FILE *Game_UserAttackAnimation_FILE_Sword;
    char Game_UserAttackAnimation_STR_line[200];
    int Game_UserAttackAnimation_INT_PositionY = 25;
    int Game_UserAttackAnimation_INT_PositionX = 66;

    Game_UserAttackAnimation_FILE_Sword = fopen("src\\art\\Attack.txt", "r");

    Position(78, 24);
    printf("-%.2f to Mopongga", UserAtk);
    while ((fgets(Game_UserAttackAnimation_STR_line, sizeof(Game_UserAttackAnimation_STR_line), Game_UserAttackAnimation_FILE_Sword)) != NULL)
    {
        Position(Game_UserAttackAnimation_INT_PositionX, Game_UserAttackAnimation_INT_PositionY);
        printf_utf8("%s", Game_UserAttackAnimation_STR_line);
        Game_UserAttackAnimation_INT_PositionY++;
    }
    fclose(Game_UserAttackAnimation_FILE_Sword);
}
void BestTwoCards(int Cards[Global_INT_F_Const][Global_INT_A_Const], int UserCards[Global_INT_S_Const][Global_INT_T_Const], int *TotalCards, int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int DrawnCard[Global_INT_F_Const][Global_INT_T_Const])
{
    int CardsAgentNumber[7] = {0, 0, 0, 0, 0, 0, 0};
    int CardsFactionNumber[5] = {0, 0, 0, 0, 0};
    float CardsMultiplierAgent[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float CardsMultiplierFaction[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    float AttackPwr[20];
    float AttackCombinationCardOne[20][1][3];
    float AttackCombinationCardTwo[20][1][3];
    int z = 0;
    float swapF;
    int swap;

    for (int x = 0; x < 20; x++)
        AttackPwr[x] = 0.00;

    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (x != y)
            {

                InitializeNumberFactionAgents(CardsAgentNumber, CardsFactionNumber, CardsMultiplierAgent, CardsMultiplierFaction);

                GameGetNumberFactionAgents(Cards, UserCards, CardsAgentNumber, CardsFactionNumber, -1, -1, (int *)TotalCards);

                CardsFactionNumber[DrawnCard[x][0]]++;
                CardsAgentNumber[DrawnCard[x][1]]++;

                CardsFactionNumber[DrawnCard[y][0]]++;
                CardsAgentNumber[DrawnCard[y][1]]++;

                GameGetCombo(CardsAgentNumber, CardsMultiplierAgent, CardsFactionNumber, CardsMultiplierFaction);

                if (TotalCards > 0)
                {
                    for (int i = 0; i < *TotalCards; i++)
                    {
                        if (Cards[UserCards[i][0]][UserCards[i][1]] != -1)
                        {
                            if (CardsMultiplierAgent[UserCards[i][1]] != 0 || CardsMultiplierFaction[UserCards[i][0]] != 0)
                                AttackPwr[z] += Cards[UserCards[i][0]][UserCards[i][1]] * (CardsMultiplierAgent[UserCards[i][1]] + CardsMultiplierFaction[UserCards[i][0]]);

                            else
                                AttackPwr[z] += Cards[UserCards[i][0]][UserCards[i][1]];
                        }
                    }
                }
                if (CardsMultiplierAgent[DrawnCard[x][1]] > 0 || CardsMultiplierFaction[DrawnCard[x][0]] > 0)
                    AttackPwr[z] += Cards[DrawnCard[x][0]][DrawnCard[x][1]] * (CardsMultiplierAgent[DrawnCard[x][1]] + CardsMultiplierFaction[DrawnCard[x][0]]);

                else
                    AttackPwr[z] += Cards[DrawnCard[x][0]][DrawnCard[x][1]];

                if (CardsMultiplierAgent[DrawnCard[y][1]] > 0 || CardsMultiplierFaction[DrawnCard[y][0]] > 0)
                    AttackPwr[z] += Cards[DrawnCard[y][0]][DrawnCard[y][1]] * (CardsMultiplierAgent[DrawnCard[y][1]] + CardsMultiplierFaction[DrawnCard[y][0]]);

                else
                    AttackPwr[z] += Cards[DrawnCard[y][0]][DrawnCard[y][1]];

                AttackCombinationCardOne[z][0][0] = DrawnCard[x][0];
                AttackCombinationCardOne[z][0][1] = DrawnCard[x][1];
                AttackCombinationCardOne[z][0][2] = AttackPwr[z];

                AttackCombinationCardTwo[z][0][0] = DrawnCard[y][0];
                AttackCombinationCardTwo[z][0][1] = DrawnCard[y][1];
                AttackCombinationCardTwo[z][0][2] = AttackPwr[z];

                // printf("<%.2f>", AttackPwr[z]);
                // getch();
                z++;
            }
        }
    }

    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 20; y++)
        {
            if (AttackPwr[y] < AttackPwr[y + 1])
            {
                swapF = AttackPwr[y];
                AttackPwr[y] = AttackPwr[y + 1];
                AttackPwr[y + 1] = swapF;

                swap = AttackCombinationCardOne[y][0][0];
                AttackCombinationCardOne[y][0][0] = AttackCombinationCardOne[y + 1][0][0];
                AttackCombinationCardOne[y + 1][0][0] = swap;

                swap = AttackCombinationCardOne[y][0][1];
                AttackCombinationCardOne[y][0][1] = AttackCombinationCardOne[y + 1][0][1];
                AttackCombinationCardOne[y + 1][0][1] = swap;

                swapF = AttackCombinationCardOne[y][0][2];
                AttackCombinationCardOne[y][0][2] = AttackCombinationCardOne[y + 1][0][2];
                AttackCombinationCardOne[y + 1][0][2] = swapF;
                //_______________________________
                swap = AttackCombinationCardTwo[y][0][0];
                AttackCombinationCardTwo[y][0][0] = AttackCombinationCardTwo[y + 1][0][0];
                AttackCombinationCardTwo[y + 1][0][0] = swap;

                swap = AttackCombinationCardTwo[y][0][1];
                AttackCombinationCardTwo[y][0][1] = AttackCombinationCardTwo[y + 1][0][1];
                AttackCombinationCardTwo[y + 1][0][1] = swap;

                swapF = AttackCombinationCardTwo[y][0][2];
                AttackCombinationCardTwo[y][0][2] = AttackCombinationCardTwo[y + 1][0][2];
                AttackCombinationCardTwo[y + 1][0][2] = swapF;
            }
        }
    }
    z = 0;
    for (int x = 0; x < 5; x++)
    {
        if (DisCarded[DrawnCard[x][0]][DrawnCard[x][1]] != -1)
        {
            if (!(z < 2))
                break;
            if (AttackCombinationCardOne[0][0][0] == DrawnCard[x][0] && AttackCombinationCardOne[0][0][1] == DrawnCard[x][1])
            {
                BestCardIndicator(x);
                z++;
            }
            if (AttackCombinationCardTwo[0][0][0] == DrawnCard[x][0] && AttackCombinationCardTwo[0][0][1] == DrawnCard[x][1])
            {
                BestCardIndicator(x);
                z++;
            }
        }
    }
}
void InitializeNumberFactionAgents(int Agent[Global_INT_A_Const], int Faction[Global_INT_F_Const], float AgentM[Global_INT_A_Const], float FactionM[Global_INT_F_Const])
{
    for (int x = 0; x < 5; x++)
    {
        Faction[x] = 0;
        FactionM[x] = 0.0;
    }
    for (int x = 0; x < 5; x++)
    {
        Agent[x] = 0;
        AgentM[x] = 0.0;
    }
}
void BestCardIndicator(int PositionX)
{
    FILE *ptr;
    char line[500];
    int positionY = 33;

    ptr = fopen("src\\Cards\\indicator.txt", "r");

    while ((fgets(line, sizeof(line), ptr)) != NULL)
    {
        Position((PositionX * 8) + (PositionX * 8) + 48, positionY);
        printf_utf8("%s", line);
        positionY++;
    }
    fclose(ptr);
}
float Compute_ATK(int Cards[Global_INT_F_Const][Global_INT_A_Const], int UserCards[Global_INT_S_Const][Global_INT_T_Const], int *TotalCards, int Compute_ATK_INT_FactionD, int Compute_ATK_INT_AgentD)
{ // computes the attack

    int CardsAgentNumber[7] = {0, 0, 0, 0, 0, 0, 0};
    int CardsFactionNumber[5] = {0, 0, 0, 0, 0};
    float CardsMultiplierAgent[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float CardsMultiplierFaction[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    float TotalAtk = 0;

    GameGetNumberFactionAgents(Cards, UserCards, CardsAgentNumber, CardsFactionNumber, -1, -1, (int *)TotalCards);
    GameGetCombo(CardsAgentNumber, CardsMultiplierAgent, CardsFactionNumber, CardsMultiplierFaction);

    for (int x = 0; x < *TotalCards; x++)
    {
        if (Cards[UserCards[x][0]][UserCards[x][1]] != -1)
        {
            if (CardsMultiplierAgent[UserCards[x][1]] != 0 || CardsMultiplierFaction[UserCards[x][0]] != 0)
                TotalAtk += Cards[UserCards[x][0]][UserCards[x][1]] * (CardsMultiplierAgent[UserCards[x][1]] + CardsMultiplierFaction[UserCards[x][0]]);

            else
                TotalAtk += Cards[UserCards[x][0]][UserCards[x][1]];
        }
    }
    return TotalAtk;
}
void GameGetNumberFactionAgents(int Cards[Global_INT_F_Const][Global_INT_A_Const], int Current[Global_INT_S_Const][Global_INT_T_Const], int Agent[Global_INT_A_Const], int Faction[Global_INT_F_Const], int FactionS, int AgentS, int *TotalCards)
{

    if (FactionS != -1 && AgentS != -1)
    {
        Agent[FactionS]++;
        Faction[AgentS]++;
    }
    else
    {
        for (int x = 0; x < *TotalCards; x++)
        {
            if (Cards[Current[x][0]][Current[x][1]] != -1)
            {
                Agent[Current[x][1]]++;
                Faction[Current[x][0]]++;
            }
        }
    }
}
void GameGetCombo(int AgentNum[Global_INT_A_Const], float AgentMultip[Global_INT_A_Const], int FactionNum[Global_INT_F_Const], float FactionMultp[Global_INT_F_Const])
{

    for (int x = 0; x < 5; x++)
    {
        switch (x)
        {
        case 0:
            FactionMultp[x] = (FactionNum[x] / 4) * 2.0;
            break;
        case 1:
            FactionMultp[x] = (FactionNum[x] / 3) * 1.5;
            break;
        case 2:
            FactionMultp[x] = (FactionNum[x] / 2) * 1.2;
            break;
        case 3:
            FactionMultp[x] = (FactionNum[x] / 4) * 3.0;
            break;
        case 4:
            FactionMultp[x] = (FactionNum[x] / 3) * 2.0;
            break;
        }
    }
    for (int x = 0; x < 7; x++)
    {
        switch (x)
        {
        case 0:
            AgentMultip[x] = (AgentNum[x] / 2) * 0.5;
            break;
        case 1:
            AgentMultip[x] = (AgentNum[x] / 3) * 2.0;
            break;
        case 2:
            AgentMultip[x] = (AgentNum[x] / 3) * 0.7;
            break;
        case 3:
            AgentMultip[x] = (AgentNum[x] / 3) * 0.3;
            break;
        case 4:
            AgentMultip[x] = (AgentNum[x] / 2) * 1.7;
            break;
        case 5:
            AgentMultip[x] = (AgentNum[x] / 2) * 2.0;
            break;
        case 6:
            AgentMultip[x] = (AgentNum[x] / 2) * 1.2;
            break;
        }
    }
}
void Game_PickingCards(int Cards[Global_INT_S_Const][Global_INT_T_Const], int CurrentCards[Global_INT_S_Const][Global_INT_T_Const], int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int DrawnCard[Global_INT_F_Const][Global_INT_T_Const], int *TotalCards)
{
    // function for picking cards;

    int input = -1;

    for (int x = 0; x < 5; x++)
    {
        if (DisCarded[DrawnCard[x][0]][DrawnCard[x][1]] != -1)
        {
            LoadCards(DrawnCard[x][0], DrawnCard[x][1], x);
            Position((x * 8) + (x * 8) + 54, 43);
            printf("(%d)", x + 1);
        }
    }

    input = CardPickingUserInput();

    while (input == -1 || DisCarded[DrawnCard[input][0]][DrawnCard[input][1]] == -1)
        input = CardPickingUserInput();

    CurrentCards[*TotalCards][0] = DrawnCard[input][0];
    CurrentCards[*TotalCards][1] = DrawnCard[input][1];
    DisCarded[DrawnCard[input][0]][DrawnCard[input][1]] = -1;

    *TotalCards += 1;
}
void Game_OverCountdown()
{
    // Countdown of game after the game
    char Input;

    for (int x = 9; x > 0; x--)
    {
        system("cls");

        Position(78, 29);
        printf("Play again?");

        Position(75, 31);
        printf("[1] YES    [2] NO");

        LoadCountDown(&x);

        if (kbhit())
        {
            Input = getch();

            if (Input == '1')
            {
                GameStart();
                Delay(1);
                Game_play();
                system("cls");
                break;
            }
            if (Input == '2')
            {
                Game_Menu();
                system("cls");
                break;
            }
        }
        Delay(1);
    }
    system("cls");
    Game_Menu();
}
void Game_CurrentUserCards(int Cards[Global_INT_F_Const][Global_INT_A_Const], int UserCards[Global_INT_S_Const][Global_INT_T_Const], int *TotalCards)
{
    int Faction[5] = {0, 0, 0, 0, 0};
    int Agent[7] = {0, 0, 0, 0, 0, 0, 0};
    // print the current cards and attack of user

    for (int x = 0; x < *TotalCards; x++)
    {
        switch (UserCards[x][0])
        {
        case 0:
            Faction[0]++;
            break;
        case 1:
            Faction[1]++;
            break;
        case 2:
            Faction[2]++;
            break;
        case 3:
            Faction[3]++;
            break;
        case 4:
            Faction[4]++;
            break;
        }
        switch (UserCards[x][1])
        {
        case 0:
            Agent[0]++;
            break;
        case 1:
            Agent[1]++;
            break;
        case 2:
            Agent[2]++;
            break;
        case 3:
            Agent[3]++;
            break;
        case 4:
            Agent[4]++;
            break;
        case 5:
            Agent[5]++;
            break;
        case 6:
            Agent[6]++;
            break;
        }
    }

    Position(2, 5);
    printf("Current ATK: %.2f", Compute_ATK(Cards, UserCards, (int *)TotalCards, -1, -1));
    Position(4, 6);
    printf("<FACTION>");
    Position(2, 7);
    printf("Freya......: %c", Faction[0] + '0');
    if (Faction[0] >= 4)
        Game_PrintBonus(Faction[0] / 4, 7);
    Position(2, 8);
    printf("Loki.......: %c", Faction[1] + '0');
    if (Faction[1] >= 3)
        Game_PrintBonus(Faction[1] / 3, 8);
    Position(2, 9);
    printf("Apollo.....: %c", Faction[2] + '0');
    if (Faction[2] >= 2)
        Game_PrintBonus(Faction[2] / 2, 9);
    Position(2, 10);
    printf("Hestia.....: %c", Faction[3] + '0');
    if (Faction[3] >= 4)
        Game_PrintBonus(Faction[3] / 4, 10);
    Position(2, 11);
    printf("Hermes.....: %c", Faction[4] + '0');
    if (Faction[4] >= 3)
        Game_PrintBonus(Faction[4] / 3, 11);
    Position(5, 12);
    printf("<AGENT>");
    Position(2, 13);
    printf("Archer.....: %c", Agent[0] + '0');
    if (Agent[0] >= 2)
        Game_PrintBonus(Agent[0] / 2, 13);
    Position(2, 14);
    printf("Assassin...: %c", Agent[1] + '0');
    if (Agent[1] >= 3)
        Game_PrintBonus(Agent[1] / 3, 14);
    Position(2, 15);
    printf("Warrior....: %c", Agent[2] + '0');
    if (Agent[2] >= 3)
        Game_PrintBonus(Agent[2] / 3, 15);
    Position(2, 16);
    printf("Healer.....: %c", Agent[3] + '0');
    if (Agent[3] >= 3)
        Game_PrintBonus(Agent[3] / 3, 16);
    Position(2, 17);
    printf("General....: %c", Agent[4] + '0');
    if (Agent[4] >= 2)
        Game_PrintBonus(Agent[4] / 2, 17);
    Position(2, 18);
    printf("Hero.......: %c", Agent[5] + '0');
    if (Agent[5] >= 2)
        Game_PrintBonus(Agent[5] / 2, 18);
    Position(2, 19);
    printf("Tank.......: %c", Agent[6] + '0');
    if (Agent[6] >= 2)
        Game_PrintBonus(Agent[6] / 2, 19);

    if (*TotalCards > 0)
    {
        Position(2, 33);
        printf("Last card picked:");
        LoadCards(UserCards[*TotalCards - 1][0], UserCards[*TotalCards - 1][1], -1);
    }
}
void Game_PrintBonus(int indication, int PositionY)
{
    // prints the combo of the user
    for (int x = 0; x < indication; x++)
    {
        Position((x * 1) + (x + 1) + 16, PositionY);
        printf("%c", Box_Const);
    }
}
void Game_Shuffle(int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int DrawnCard[Global_INT_F_Const][Global_INT_T_Const], int TemporaryCards[Global_INT_F_Const][Global_INT_T_Const])
{
    int Faction;
    int Agent;
    // shuffles the cards before choosing
    for (int x = 0; x < 5; x++)
    {

        Game_GetRandomCard(&Faction, &Agent);

        while (TemporaryCards[Faction][Agent] == -1)
            Game_GetRandomCard(&Faction, &Agent);

        DrawnCard[x][0] = Faction;
        DrawnCard[x][1] = Agent;

        DisCarded[Faction][Agent] = TemporaryCards[Faction][Agent];
        TemporaryCards[Faction][Agent] = -1;
    }
}
void Game_GetRandomCard(int *Faction, int *Agent)
{
    // getting random cards
    *Faction = rand() % 5;
    *Agent = rand() % 7;
}
void InitializeCards(int Cards[Global_INT_F_Const][Global_INT_A_Const], int DisCarded[Global_INT_F_Const][Global_INT_A_Const], int TemporaryCards[Global_INT_F_Const][Global_INT_A_Const])
{
    for (int x = 0; x < 5; x++)
    { // Initialize Discarded Cards and TemporaryCards
        for (int y = 0; y < 7; y++)
        {
            DisCarded[x][y] = -1;
            TemporaryCards[x][y] = Cards[x][y];
        }
    }
}
void LoadCards(int Faction, int Agent, int PositionX)
{
    // load the art of cards
    FILE *Card;
    char line[200];
    char pathfile[] = "";
    int PositionY = 35;

    sprintf(pathfile, "src\\Cards\\%d\\%d.txt", Faction, Agent);

    Card = fopen(pathfile, "r");

    while ((fgets(line, sizeof(line), Card)) != NULL)
    {
        if (PositionX == -1)
            Position(4, PositionY);
        else
            Position((PositionX * 8) + (PositionX * 8) + 50, PositionY);
        printf_utf8("%s", line);
        PositionY++;
    }
    fclose(Card);
}
void LoadEpilogue(char text[Global_INT_S_Const][Global_INT_S_Const])
{
    FILE *LoadEpilogue_FILE_Script;
    char line[100];
    int LineNum = 0;

    LoadEpilogue_FILE_Script = fopen("src\\EpilogueScript.txt", "r");

    while ((fgets(line, sizeof(line), LoadEpilogue_FILE_Script)) != NULL)
    {
        strncpy(text[LineNum], line, sizeof(line));
        LineNum++;
    }
    fclose(LoadEpilogue_FILE_Script);
}
void Script_Print_byChar(char text[Global_INT_S_Const][Global_INT_S_Const], int line)
{
    // print the script by character
    int skip, x;
    for (x = 0; !kbhit(); x++)
    {
        Delay(0.03);
        printf("%c", text[line][x]);
        if (text[line][x] == '\0')
        {
            skip = false_Const;
            break;
        }
        else
            skip = true_Const;
    }
    if (skip == true_Const)
        Script_Print_byStr(text, line, x);
}
void Script_Print_byStr(char text[Global_INT_S_Const][Global_INT_S_Const], int line, int CharPos)
{
    // print the whole script
    for (int x = CharPos; text[line][x] != '\0'; x++)
    {
        printf("%c", text[line][x]);
    }
    getch();
}
void YouWIN()
{
    FILE *YouWIN_FILE_winfile;
    char YouWIN_STR_line[500];
    int YouWIN_INT_positionY = 5;

    YouWIN_FILE_winfile = fopen("src\\art\\YouWIN.txt", "r");

    while ((fgets(YouWIN_STR_line, sizeof(YouWIN_STR_line), YouWIN_FILE_winfile)) != NULL)
    {
        Position(65, YouWIN_INT_positionY);
        printf_utf8("%s", YouWIN_STR_line);
        YouWIN_INT_positionY++;
        Delay(0.1);
    }
    fclose(YouWIN_FILE_winfile);
}
void LoadCountDown(int *Number)
{
    FILE *CountDown;
    char line[500];
    int PositionY = 15;
    char path[] = "";

    sprintf(path, "src\\Countdown\\%d.txt", *Number);

    CountDown = fopen(path, "r");

    while ((fgets(line, sizeof(line), CountDown)) != NULL)
    {
        Position(79, PositionY);
        printf_utf8("%s", line);
        PositionY++;
    }
}
void Art_Speechbox()
{
    FILE *SpeechBox;
    int YCoord = 36;

    char line[300];

    SpeechBox = fopen("src\\art\\SpeechBox.txt", "r");

    while ((fgets(line, sizeof(line), SpeechBox)) != NULL)
    {
        Position(50, YCoord);
        printf_utf8("%s", line);
        YCoord++;
    }
}
void Game_Over()
{
    FILE *EndFile;
    int YCoord = 12;

    char line[300];

    EndFile = fopen("src\\art\\gameover.txt", "r");

    while ((fgets(line, sizeof(line), EndFile)) != NULL)
    {
        Position(69, YCoord);
        printf_utf8("%s", line);
        YCoord++;
    }
}
void CardsAppearance()
{
    FILE *HandsFile;
    char line[400];
    int PositionY = 8;

    HandsFile = fopen("src\\art\\Cardslook.txt", "r");

    while ((fgets(line, sizeof(line), HandsFile)) != NULL)
    {
        Position(0, PositionY + 1);
        printf_utf8("%s", line);
        PositionY++;
    }
    fclose(HandsFile);
}
void AgreementArt()
{
    FILE *HandsFile;
    char line[400];
    int PositionY = 10;

    HandsFile = fopen("src\\art\\AgreementArt.txt", "r");

    while ((fgets(line, sizeof(line), HandsFile)) != NULL)
    {
        Position(50, PositionY + 1);
        printf_utf8("%s", line);
        PositionY++;
    }
    fclose(HandsFile);
}
void AgentArt(int PositionX)
{
    FILE *Agentfile;
    char line[100];
    char path[20] = "";
    int PositionY = 8;

    sprintf(path, "src\\Agent\\%d.txt", PositionX);

    Agentfile = fopen(path, "r");

    while ((fgets(line, sizeof(line), Agentfile)) != NULL)
    {
        Position((PositionX * 10) + (PositionX * 5) + 35, PositionY + 1);
        printf_utf8("%s", line);
        PositionY++;
    }
    fclose(Agentfile);
}
void FactionArt(int PositionX)
{
    FILE *FactionFile;
    char line[100];
    char path[20] = "";
    int PositionY = 8;

    sprintf(path, "src\\Faction\\%d.txt", PositionX);

    FactionFile = fopen(path, "r");

    while ((fgets(line, sizeof(line), FactionFile)) != NULL)
    {
        Position((PositionX * 10) + (PositionX * 5) + 52, PositionY + 1);
        printf_utf8("%s", line);
        PositionY++;
    }
    fclose(FactionFile);
}
void ShieldArt()
{
    FILE *ShieldFile;

    char line[1000];
    int YCoordinate = 8;

    ShieldFile = fopen("src\\art\\shield.txt", "r");

    while ((fgets(line, sizeof(line), ShieldFile)) != NULL)
    {
        Position(79, YCoordinate);
        printf_utf8("%s", line);
        YCoordinate++;
    }
    fclose(ShieldFile);
}
void Game_BossHp(float HitPoints)
{
    FILE *Hp;
    char line[1000];
    int Hpbar = 100;
    int Percentage;
    int HpPositionY = 0;

    Hp = fopen("src\\art\\BossHP.txt", "r");

    while ((fgets(line, sizeof(line), Hp)) != NULL)
    {
        Position(38, HpPositionY);
        printf_utf8("%s", line);
        HpPositionY++;
    }
    fclose(Hp);

    Percentage = (HitPoints / 150) * Hpbar;

    Position(73, 1);
    printf("%.2f", HitPoints);

    for (int x = 0; x < Percentage; x++)
    {
        Position(x + 40, 2);
        printf("%c", HP_Const);
    }
}
void BossArt()
{
    FILE *BossFile;

    char line[1000];
    int YCoordinate = 5;

    BossFile = fopen("src\\art\\boss_art.txt", "r");

    while ((fgets(line, sizeof(line), BossFile)) != NULL)
    {
        Position(75, YCoordinate);
        printf_utf8("%s", line);
        YCoordinate++;
    }
    fclose(BossFile);
}
const char CardPickingUserInput()
{
    char NumberToReturn_Char_Input;

    NumberToReturn_Char_Input = getch();
    NumberToReturn_Char_Input -= 1;
    if (!(Number_Const))
        return -1;

    return NumberToReturn_Char_Input - '0';
}
void printf_utf8(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int len = _vscprintf(format, args) + 1;
    char *buf = malloc(len);
    vsprintf(buf, format, args);

    // Convert to UTF16 and print
    int wbuf_size = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
    wchar_t *wbuf = malloc((wbuf_size + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, wbuf_size);

    DWORD temp;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleW(h, wbuf, wcslen(wbuf), &temp, 0);

    free(wbuf);
    free(buf);
}
void HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void Position(int Xcoordinate, int Ycoordinate)
{
    COORD coordinate;

    coordinate.X = Xcoordinate;
    coordinate.Y = Ycoordinate;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
void Delay(float time)
{

    int milli_sec = 1000 * time;
    clock_t _initial = clock();
    while (clock() < _initial + milli_sec)
        ;
}
void remove_scrollbar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
        {
            info.srWindow.Right - info.srWindow.Left + 1,
            info.srWindow.Bottom - info.srWindow.Top + 1};
    SetConsoleScreenBufferSize(handle, new_size);
}
void fullscreen()
{

    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
