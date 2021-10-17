/*
 * GameRep.c
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../commons/Properties.h"
#include "GameRepo.h"

void gr_initGameListHardCd(GameEntity* gmLst, int gmLn, int from, int until){
	for(int i=from;i<until; i++){
		(gmLst+i)->gmId = -111;
		(gmLst+i)->gmEmpty = TRUE;
	}
}

void gr_getGameById(GameEntity* gmLst, int gmLn, int gmId, GameEntity* gmEntAux){
	int cont=TRUE;
	for(int i=0; i<gmLn && cont; i++) {
		if(!(gmLst+i)->gmEmpty && ((gmLst+i)->gmId == gmId)){
			*gmEntAux = *(gmLst+i);
			cont = FALSE;
		}
	}
}

void gr_showAGame(GameEntity gmEnt){
	printf("-juego.id=%d | juego.nombre=%s-\n", gmEnt.gmId, gmEnt.gmDesc);
}

void gr_showAllGames(GameEntity* gmLst, int gmLn){
	int success = TRUE;
	if(gmLst == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else{
		for(int i=0; i<gmLn; i++){
			if(!(gmLst+i)->gmEmpty)
				printf("-juego.id=%d | juego.nombre=%s-\n", (gmLst+i)->gmId, (gmLst+i)->gmDesc);
		}
	}
}

int gr_getGameIdByName(GameEntity* gmLst, int gmLn, char* gmName){
	int gmId=-1;
	for(int i=0; i<gmLn && gmId==-1; i++){
		if(!(gmLst+i)->gmEmpty){
			gmId = (strcmp((gmLst+i)->gmDesc, gmName)==0)?(gmLst+i)->gmId:-1;
		}
	}
	return gmId;
}

void gr_getGameNameById(GameEntity* gmLst, int gmLn, int gmId, char* gmName){
	int cont=FALSE;

	for(int i=0; i<gmLn && !cont; i++){
		if(!(gmLst+i)->gmEmpty){
			cont = (gmLst+i)->gmId == gmId;
			if(cont){
				strcpy(gmName, (gmLst+i)->gmDesc);
			}
		}
	}
}
