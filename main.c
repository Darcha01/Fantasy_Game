#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "champion.c"

int main(int argc, char *argv[]){
    srand(time(NULL));
    Champion* P1head = NULL;
    Champion* P2head = NULL;
    Champion* newChamp = NULL;
    Champion* temp = NULL;
    int i, userChampNum, roundCount;    //*IMPORTANT: TO START, ENTER "./main *number greater than 0*" INTO COMMAND LINE AND HIT ENTER. Ex: "./main 5"

    if(argc < 2){           //checks if there are at least 2 arguments
        printf("ERROR NO ARGS");
        return 1;
    }
    if(atoi(argv[1]) <= 0){         //checks if the second arg is greater than zero
        printf("ERROR ARG IS NOT GREATER THAN ZERO");
        return 1;
    }

    userChampNum = atoi(argv[1]);

    P1head = buildChampionList(userChampNum);       //build p1 and p2 linked lists with the amount of champions taken from the command line
    P2head = buildChampionList(userChampNum);

    printf("============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n");

    roundCount = 1;
    while(P1head != NULL && P2head != NULL){        //iterates through until at least one of the players has no more champions
        printf("\n----- ROUND %d -----\n", roundCount);
        printf("Player 1: ");
        printChampionList(P1head);
        printf("\nPlayer 2: ");
        printChampionList(P2head);
        printf("\n");

        if(P1head->role == 0 && P2head->role == 0){         //mage v mage
            printf("Player 1 is a MAGE and Player 2 is a MAGE\n");
            if(P1head->level > P2head->level){      //p1 mage wins
                printf("Player 2 (MAGE) loses one champion.\nPlayer 1 (MAGE) wins and gains one new champion.\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
                P2head = removeChampion(P2head);
            }
            else if (P1head->level < P2head->level){        //p2 mage wins
                printf("Player 1 (MAGE) loses one champion.\nPlayer 2 (MAGE) wins and gains one new champion.\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
                P1head = removeChampion(P1head);
            }
            else{
                printf("TIE - no contest.\n");          //both players tie
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
            }
        }
        else if((P1head->role == 0 && P2head->role == 1) || (P1head->role == 1 && P2head->role == 0)){          //mage vs fighter
            if(P1head->level > P2head->level && P1head->role == 0){         //p1 mage wins
                printf("Player 1 is a MAGE and Player 2 is a FIGHTER\n");
                printf("Player 2 (FIGHTER) loses.\nPlayer 1 (MAGE) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
            }
            else if(P1head->level > P2head->level && P1head->role == 1){            //p1 fighter wins
                printf("Player 1 is a FIGHTER and Player 2 is a MAGE\n");
                printf("Player 2 (MAGE) loses one champion.\nPlayer 1 (FIGHTER) wins\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                removeChampion(P2head);
            }
            else if(P1head->level < P2head->level && P2head->role == 0){            //p2 mage wins
                printf("Player 1 is a FIGHTER and Player 2 is a MAGE\n");
                printf("Player 1 (FIGHTER) loses.\nPlayer 2 (MAGE) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
            }
            else if(P1head->level < P2head->level && P2head->role == 1){            //p2 fighter wins
                printf("Player 1 is a MAGE and Player 2 is a FIGHTER\n");
                printf("Player 1 (MAGE) loses one champion.\nPlayer 2 (FIGHTER) wins\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                removeChampion(P2head);
            }
            else{
                if(P1head->role == 0){          //tie for both scenarios
                    printf("Player 1 is a MAGE and Player 2 is a FIGHTER\n");
                    printf("TIE - no contest.\n");
                    P1head = removeChampion(P1head);
                    P2head = removeChampion(P2head);
                }
                else{
                    printf("Player 1 is a FIGHTER and Player 2 is a MAGE\n");
                    printf("TIE - no contest.\n");
                    P1head = removeChampion(P1head);
                    P2head = removeChampion(P2head);
                }
            }
        }
        else if((P1head->role == 0 && P2head->role == 2) || (P1head->role == 2 && P2head->role == 0)){      //mage v support
            if(P1head->level > P2head->level && P1head->role == 0){         //p1 mage wins
                printf("Player 1 is a MAGE and Player 2 is a SUPPORT\n");
                printf("Player 2 (SUPPORT) loses two champions.\nPlayer 1 (MAGE) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
                if(P2head == NULL && P2head->next == NULL){         //these null checks that you see throughout are there so that the program doesn't break when a player
                    continue;                                       //loses more champions than they have
                }
                else if(P2head != NULL && P2head->next == NULL){
                    P2head = removeChampion(P2head);
                    continue;
                }
                else{
                    P2head = removeChampion(P2head);
                    P2head = removeChampion(P2head);
                }
            }
            else if(P1head->level > P2head->level && P1head->role == 2){            //p1 support wins
                printf("Player 1 is a SUPPORT and Player 2 is a MAGE\n");
                printf("Player 2 (MAGE) loses one champion.\nPlayer 1 (SUPPORT) wins two champions\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
                if(P2head != NULL){
                    removeChampion(P2head);
                }
            }
            else if(P1head->level < P2head->level && P2head->role == 0){            //p2 mage wins
                printf("Player 1 is a SUPPORT and Player 2 is a MAGE\n");
                printf("Player 1 (SUPPORT) loses two champions.\nPlayer 2 (MAGE) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
                if(P1head == NULL && P1head->next == NULL){
                    continue;
                }
                else if(P1head != NULL && P1head->next == NULL){
                    P1head = removeChampion(P1head);
                    continue;
                }
                else{
                    P1head = removeChampion(P1head);
                    P1head = removeChampion(P1head);
                }
                
            }
            else if(P1head->level < P2head->level && P2head->role == 2){            //p2 support wins
                printf("Player 1 is a MAGE and Player 2 is a SUPPORT\n");
                printf("Player 1 (MAGE) loses one champion.\nPlayer 2 (SUPPORT) wins two champions\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
                if(P1head != NULL){
                    removeChampion(P2head);
                }
            }
            else{
                if(P1head->role == 0){          //tie for both scenarios
                    printf("Player 1 is a MAGE and Player 2 is a SUPPORT\n");
                    printf("TIE - no contest.\n");
                    P1head = removeChampion(P1head);
                    P2head = removeChampion(P2head);
                }
                else{
                    printf("Player 1 is a SUPPORT and Player 2 is a MAGE\n");
                    printf("TIE - no contest.\n");
                    P1head = removeChampion(P1head);
                    P2head = removeChampion(P2head);
                }
            }
        }
        else if((P1head->role == 0 && P2head->role == 3) || (P1head->role == 3 && P2head->role == 0)){          //mage v tank
            if(P1head->role == 0){          //p1 mage wins
                printf("Player 1 is a MAGE and Player 2 is a TANK\n");
                printf("Player 2 (TANK) loses one champion.\nPlayer 1 (MAGE) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
                if(P2head != NULL){
                    P2head = removeChampion(P2head);
                }
            }
            else{           //p2 mage wins
                printf("Player 1 is a TANK and Player 2 is a MAGE\n");
                printf("Player 1 (TANK) loses one champion.\nPlayer 2 (MAGE) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
                if(P1head != NULL){
                    P1head = removeChampion(P1head);
                }
            }
        }
        else if(P1head->role == 1 && P2head->role == 1){            //fighter v fighter
            printf("Player 1 is a FIGHTER and Player 2 is a FIGHTER\n");
            printf("Both players gain one champion.\n");
            P1head = removeChampion(P1head);
            P2head = removeChampion(P2head);
            newChamp = createChampion(newChamp);
            P2head = addChampion(P2head, newChamp);
            newChamp = createChampion(newChamp);
            P1head = addChampion(P1head, newChamp);
        }
        else if((P1head->role == 1 && P2head->role == 2) || (P1head->role == 2 && P2head->role == 1)){          //fighter v support
            if(P1head->level > P2head->level && P1head->role == 1){         //p1 fighter wins
                printf("Player 1 is a FIGHTER and Player 2 is a SUPPORT\n");
                printf("Player 2 (SUPPORT) loses one champion.\nPlayer 1 (FIGHTER) wins\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                if(P2head != NULL){
                    P2head = removeChampion(P2head);
                }
            }
            else if(P1head->level > P2head->level && P1head->role == 2){         //p1 support wins
                printf("Player 1 is a SUPPORT and Player 2 is a FIGHTER\n");
                printf("Player 2 (FIGHTER) loses.\nPlayer 1 (SUPPORT) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
            }
            else if(P1head->level < P2head->level && P2head->role == 1){         //p2 fighter wins
                printf("Player 1 is a SUPPORT and Player 2 is a FIGHTER\n");
                printf("Player 1 (SUPPORT) loses one champion.\nPlayer 2 (FIGHTER) wins\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                if(P1head != NULL){
                    P1head = removeChampion(P1head);
                }
            }
            else if(P1head->level < P2head->level && P2head->role == 2){         //p2 support wins
                printf("Player 1 is a FIGHTER and Player 2 is a SUPPORT\n");
                printf("Player 1 (FIGHTER) loses.\nPlayer 2 (SUPPORT) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
            }
            else{
                if(P1head->role == 1){          //tie for both scenarios
                    printf("Player 1 is a FIGHTER and Player 2 is a SUPPORT\n");
                    printf("TIE - no contest.\n");
                    P1head = removeChampion(P1head);
                    P2head = removeChampion(P2head);
                }
                else{
                    printf("Player 1 is a SUPPORT and Player 2 is a FIGHTER\n");
                    printf("TIE - no contest.\n");
                    P1head = removeChampion(P1head);
                    P2head = removeChampion(P2head);
                }
            }
        }
        else if((P1head->role == 1 && P2head->role == 3) || (P1head->role == 3 && P2head->role == 1)){          //fighter vs tank
            if(P1head->role == 1){          //p1 fighter wins
                printf("Player 1 is a FIGHTER and Player 2 is a TANK\n");
                printf("Player 2 (TANK) loses.\nPlayer 1 (FIGHTER) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
            }
            else{           //p2 fighter wins
                printf("Player 1 is a TANK and Player 2 is a FIGHTER\n");
                printf("Player 1 (TANK) loses.\nPlayer 2 (FIGHTER) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
            }
        }
        else if(P1head->role == 2 && P2head->role == 2){            //support vs support
            printf("Player 1 is a SUPPORT and Player 2 is a SUPPORT\n");
            printf("Both players lose one champion.\n");
            P1head = removeChampion(P1head);
            P2head = removeChampion(P2head);
            if(P1head != NULL){
                P1head = removeChampion(P1head);
            }
            if(P2head != NULL){
                P2head = removeChampion(P2head);
            }
        }
        else if((P1head->role == 2 && P2head->role == 3) || (P1head->role == 3 && P2head->role == 2)){          //support vs tank
            if(P1head->role == 3){          //p1 tank wins
                printf("Player 1 is a TANK and Player 2 is a SUPPORT\n");
                printf("Player 2 (SUPPORT) loses.\nPlayer 1 (TANK) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P1head = addChampion(P1head, newChamp);
            }
            else{           //p2 tank wins
                printf("Player 1 is a SUPPORT and Player 2 is a TANK\n");
                printf("Player 1 (SUPPORT) loses.\nPlayer 2 (TANK) wins and gains one champion\n");
                P1head = removeChampion(P1head);
                P2head = removeChampion(P2head);
                newChamp = createChampion(newChamp);
                P2head = addChampion(P2head, newChamp);
            }
            
            
        }
        else{           //tank vs tank
            printf("Player 1 is a TANK and Player 2 is a TANK\n");
            printf("Nothing happens - no penalty. no reward.\n");
            P1head = removeChampion(P1head);
            P2head = removeChampion(P2head);
        }
        roundCount++;
    }

    printf("\n============ GAME OVER =============\n\n");
    printf("Player 1 ending champion list: ");          //game ends and prints out the remaining list of champions from both players
    temp = P1head;
    while(P1head != NULL){
        switch (P1head->role)
        {
        case 0:
            printf("M%d ", P1head->level);
            break;
        case 1:
            printf("F%d ", P1head->level);
            break;
        case 2:
            printf("S%d ", P1head->level);
            break;
        case 3:
            printf("T%d ", P1head->level);
        }
        P1head = P1head->next;
    }
    P1head = temp;

    temp = P2head;
    printf("\nPlayer 2 ending champion list: ");
    while(P2head != NULL){
        switch (P2head->role)
        {
        case 0:
            printf("M%d ", P2head->level);
            break;
        case 1:
            printf("F%d ", P2head->level);
            break;
        case 2:
            printf("S%d ", P2head->level);
            break;
        case 3:
            printf("T%d ", P2head->level);
        }
        P2head = P2head->next;
    }
    P2head = temp;

    if(P1head != NULL && P2head == NULL){           //cases for whoever won
        printf("\n\nPlayer 2 ran out of champions. Player 1 wins!\n");
    }
    else if(P1head == NULL && P2head != NULL){
        printf("\n\nPlayer 1 ran out of champions. Player 2 wins!\n");
    }
    else{
        printf("\n\nTIE -- both players ran out of champions.\n");
    }
    

    P1head = destroyChampionList(P1head);           //the lists that allocate data are freed
    P2head = destroyChampionList(P2head);
    newChamp = destroyChampionList(newChamp);
    temp = destroyChampionList(temp);

    return 0;
}