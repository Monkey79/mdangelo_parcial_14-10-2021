/*
 * GameRep.c
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#include <stdio.h>
#include <string.h>
#include "../commons/Properties.h"
#include "GameRepo.h"


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

int gr_getGameIdByName(GameEntity* gmLst, int gmLn, char* gmName){
	int gmId=-1;
	for(int i=0; i<gmLn && gmId==-1; i++){
		if(!(gmLst+i)->gmEmpty){
			gmId = (strcmp((gmLst+i)->gmDesc, gmName)==0)?(gmLst+i)->gmId:-1;
		}
	}
	return gmId;
}
