/*
 * ArcadeRepo.c
 *  Created on: 15 oct. 2021
 *  Author: mdangelo
 */

#include <stdio.h>
#include <string.h>
#include "../commons/Properties.h"
#include "ArcadeRepo.h"

#define NO_ARCADE "-NO habia arcades asignados para ese salon-\n"

void ar_initArcadeListHardCd(ArcadeEntity* arLst, int from, int until){
	for(int i=from;i<until; i++){
		(arLst+i)->arId = -111;
		(arLst+i)->arEmpty = TRUE;
	}
}


int ar_initArcadeList(ArcadeEntity* arLst, int arLn){
	int success = TRUE;
	if(arLst == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		for(int i=0;i<arLn; i++){
			(arLst+i)->arId = -111;
			(arLst+i)->arEmpty = TRUE;
		}
	}
	return success;
}

//--Abms---
int ar_getFreeArcadeIndx(ArcadeEntity* arList, int arLn){
	int i;
	for(i=0;i<arLn && !(arList+i)->arEmpty; i++);
	return ((arList+i)->arEmpty)?i:-1;
}

int ar_thereAreArcades(ArcadeEntity* arList, int arLn){
	int cont=TRUE;
	for(int i=0;i<arLn && cont; i++){
		if(!(arList+i)->arEmpty) cont=FALSE;
	}
	return !cont;
}

int ar_saveArcade(ArcadeEntity* arList, int arLn, ArcadeEntity arcEnt, int arIdx){
	int success = TRUE;
	int i=arIdx; //indice libre

	if(arList == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		*(arList+i) = arcEnt;
	}

	return success;
}
int ar_updateArcade(ArcadeEntity* arList, int arLn, ArcadeEntity arcEnt){
	int success = TRUE;
	int i;

	if(arList == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		i = ar_getIndxFromArcId(arList, arLn, arcEnt.arId);
		*(arList+i) = arcEnt;
	}

	return success;
}
int ar_deleteArcadeByIndx(ArcadeEntity* arList, int arLn,int arIdx){
	int success = TRUE;
	int i;

	if(arList == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		(arList+arIdx)->arEmpty = TRUE;
		(arList+arIdx)->arSlId = -111;
		(arList+arIdx)->arGmId = -111;
	}

	return success;
}
int ar_deleteArcadesBySaloonId(ArcadeEntity* arList,int arLn,int slId){
	int success = TRUE;
	int hit=0;

	if(arList == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		for(int i=0; i<arLn; i++){
			if(!(arList+i)->arEmpty){
				if((arList+i)->arSlId == slId){
					hit++;
					(arList+i)->arEmpty = TRUE;
					(arList+i)->arGmId = -111;
					(arList+i)->arSlId = -111;
				}
			}
		}
		if(hit>0){  //el salon tenia arcades asociados
			printf("-fueron eliminados %d arcades que pertenecian al salond id=%d-\n", hit, slId);
		}else{
			//el salon no tenia ningun arcade
			success = FALSE;
			printf(NO_ARCADE);
		}
	}
	return success;
}

void ar_showArcadeList(ArcadeEntity* arLst, int arLn){
	char soundTp[STR_50];
	for(int i=0;i<arLn; i++){
		if(!(arLst+i)->arEmpty){
			ar_getSoundTypeDescById((arLst+i)->arSndTp,soundTp);
			printf("-arc.id=%d | arc.nacionalidad=%s | arc.tipo_sonido=%s | arc.cant_jug=%d | arc.capacidad_fichas=%d | arc.salon_id=%d | arc.game_id=%d\n",
					(arLst+i)->arId,(arLst+i)->arNationality,soundTp,(arLst+i)->arPlyAmt, (arLst+i)->arCoinsCap, (arLst+i)->arSlId, (arLst+i)->arGmId);
		}
	}
}
void ar_showAnArcade(ArcadeEntity arcEnt){
	char soundTp[STR_50];
	ar_getSoundTypeDescById(arcEnt.arSndTp,soundTp);

	printf("-arc.id=%d | arc.nacionalidad=%s | arc.tipo_sonido=%s | arc.cant_jug=%d | arc.capacidad_fichas=%d \n",
			arcEnt.arId,arcEnt.arNationality,soundTp,arcEnt.arPlyAmt, arcEnt.arCoinsCap);
}
void ar_showAnArcadeWithHisGame(ArcadeEntity arcEnt, char* gmDesc){
	char soundTp[STR_50];
	ar_getSoundTypeDescById(arcEnt.arSndTp,soundTp);

	printf("-arc.id=%d | arc.nacionalidad=%s | arc.tipo_sonido=%s | arc.cant_jug=%d | arc.capacidad_fichas=%d | arc.salon_id=%d | arg.juego_nombre=%s\n",
			arcEnt.arId,arcEnt.arNationality,soundTp,arcEnt.arPlyAmt, arcEnt.arCoinsCap, arcEnt.arSlId,gmDesc);
}

void ar_getSoundTypeDescById(int sndType, char* sndDesc){
	if(sndType==1)
		strcpy(sndDesc,"Stereo");
	else if(sndType==2)
		strcpy(sndDesc,"Mono");
}

void ar_sortArcadeBySalonIdAsc(ArcadeEntity* arLst, int arLn){
	ArcadeEntity arcEnt;
	int disordered=TRUE;

	while(disordered){
		disordered = FALSE;
		for(int i=0;i<arLn-1;i++){
			if(!(arLst+i)->arEmpty && !(arLst+(i+1))->arEmpty){
				if((arLst+i)->arSlId > (arLst+(i+1))->arSlId){
					arcEnt = *(arLst+i);
					*(arLst+i) = *(arLst+(i+1));
					*(arLst+(i+1)) = arcEnt;

					disordered = FALSE;
				}
			}
		}
	}

}

int ar_getIndxFromArcId(ArcadeEntity* arLst, int arLn, int arcId){
	int isValid=FALSE;
	int idx = -1;

	for(int i=0;i<arLn && !isValid;i++){
		if(!(arLst+i)->arEmpty){
			if((arLst+i)->arId == arcId){
				isValid=TRUE;
				idx = i;
			}
		}
	}
	return idx;
}

//---Informes---
int ar_getArcadeAmountBySlId(ArcadeEntity* arLst, int arLn, int slId){
	int arNm=0;
	for(int i=0;i<arLn;i++){
		if(!(arLst+i)->arEmpty){
			if((arLst+i)->arSlId == slId) arNm++;
		}
	}
	return arNm;
}

void ar_getArcadeBySaloonId(ArcadeEntity* arLst, int arLn, int slId, ArcadeEntity* arcEnt){
	int cont = TRUE;
	for(int i=0;i<arLn && cont;i++){
		if(!(arLst+i)->arEmpty){
			if ((arLst+i)->arSlId == slId){
				*arcEnt = *(arLst+i);
				cont = FALSE;
			}
		}
	}
}

void ar_getArcadeById(ArcadeEntity* arLst, int arLn, int arcId, ArcadeEntity* arcEnt){
	int cont = TRUE;
	for(int i=0;i<arLn && cont;i++){
		if(!(arLst+i)->arEmpty){
			if ((arLst+i)->arSlId == arcId){
				*arcEnt = *(arLst+i);
				cont = FALSE;
			}
		}
	}
}

int ar_getArcadeCoinsCapacityBySaloonId(ArcadeEntity* arLst, int arLn, int slId){
	int coins=0;
	for(int i=0;i<arLn;i++){
		if(!(arLst+i)->arEmpty){
			if((arLst+i)->arSlId == slId) coins += (arLst+i)->arCoinsCap;
		}
	}
	return coins;
}

int ar_getGameAmountInArcadeList(ArcadeEntity* arLst, int arLn, int gmId){
	int gmCnt=0;
	for(int i=0;i<arLn;i++){
		if(!(arLst+i)->arEmpty){
			if((arLst+i)->arGmId == gmId) gmCnt++;
		}
	}
	return gmCnt;
}

int ar_isGameInArcadeList(ArcadeEntity* arLst, int arLn, int gmId){
	int tot=0;
	int hit=0;
	for(int i=0;i<arLn ;i++){
		if(!(arLst+i)->arEmpty){
			tot++;
			if((arLst+i)->arGmId == gmId){
				hit++;
			}
		}
	}
	return (hit==tot);
}



