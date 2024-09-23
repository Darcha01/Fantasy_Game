#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "champion.h"

Champion* createChampion(){         //creates a champion by allocating data, choosing a random number for its role, then giving it a random number for the power level
    Champion* n = (Champion*)malloc(sizeof(Champion));
    int x = rand()%4;
    int level;
    if(x == MAGE){
        n->role = MAGE;
        n->level = (rand()%(8+1-5)) + 5;
        n->next = NULL;
        return n;
    }
    else if(x == FIGHTER){
        n->role = FIGHTER;
        n->level = (rand()%(4+1-1)) + 1;
        n->next = NULL;
        return n;
    }
    else if(x == SUPPORT){
        n->role = SUPPORT;
        n->level = (rand()%(6+1-3)) + 3;
        n->next = NULL;
        return n;
    }
    else{
        n->role = TANK;
        n->level = (rand()%(8+1-1)) + 1;
        n->next = NULL;
        return n;
    }
}

Champion* addChampion(Champion* head, Champion* c){         //uses recursion to compare a new node to either an existing linked list or a null list
    Champion* temp1 = NULL;
    if(head == NULL){
        return c;
    }
    if(head->next == NULL){
        if(c->level <= head->level){
            head->next = c;
            return head;
        }
        else{
            temp1 = head;
            head = c;
            head->next = temp1;
            return head;
        }
    }
    else{
        if(c->level > head->level){
            c->next = head;
            return c;
        }
        else{
            head->next = addChampion(head->next, c);
        }
    }
    return head;
}

Champion* buildChampionList(int n){         //builds the initial list of champions
    int i;
    Champion* head = NULL;
    Champion* c = NULL;
    for(i=0; i<n; i++){
        if(i == 0){
            head = createChampion();
            continue;
        }
        c = createChampion();
        head = addChampion(head, c);
    }
    return head;
}

void printChampionList(Champion* head){         //prints out the list of champions
    Champion* temp = head;
    while (head != NULL)
    {
        switch(head->role){
            case MAGE: printf("M%d ", head->level);
            break;
            case FIGHTER: printf("F%d ", head->level);
            break;
            case SUPPORT: printf("S%d ", head->level);
            break;
            case TANK: printf("T%d ", head->level);
            break;
        }
        head = head->next;
    }
    head = temp;
}

Champion* removeChampion(Champion* head){           //removes the first champion from the list
    Champion* temp = head;
    head = head->next;
    free(temp);
    return head;
}

Champion* destroyChampionList(Champion* head){          //deallocates data for a list of champions
    if(head->next == NULL){
        free(head);
        return head;
    }
    destroyChampionList(head->next);
    free(head);
    return head;
}