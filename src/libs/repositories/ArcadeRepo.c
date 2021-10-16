/*
 * ArcadeRepo.c
 *  Created on: 15 oct. 2021
 *  Author: mdangelo
 */

#include <stdio.h>
#include <string.h>
#include "../commons/Properties.h"
#include "ArcadeRepo.h"

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

void ar_showArcadeList(ArcadeEntity* arLst, int arLn){
	char soundTp[STR_50];
	for(int i=0;i<arLn; i++){
		if(!(arLst+i)->arEmpty){
			ar_getSoundTypeDescById((arLst+i)->arSndTp,soundTp);
			printf("sonido_tipo=%s\n",soundTp);
			printf("-arc.id=%d | arc.nacionalidad=%s | arc.tipo_sonido=%s | arc.cant_jug=%d | arc.capacidad_fichas=%d \n",
					(arLst+i)->arId,(arLst+i)->arNationality,soundTp,(arLst+i)->arPlyAmt, (arLst+i)->arCoinsCap);
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

	printf("-arc.id=%d | arc.nacionalidad=%s | arc.tipo_sonido=%s | arc.cant_jug=%d | arc.capacidad_fichas=%d | arg.juego_nombre=%s\n",
			arcEnt.arId,arcEnt.arNationality,soundTp,arcEnt.arPlyAmt, arcEnt.arCoinsCap,gmDesc);
}

void ar_getSoundTypeDescById(int sndType, char* sndDesc){
	if(sndType==1)
		strcpy(sndDesc,"Stereo");
	else if(sndType==2)
		strcpy(sndDesc,"Mono");
}

void ar_sortArcadeBySalonId(ArcadeEntity* arLst, int arLn, int asc){
	int sort=TRUE;

	while(!sort){
		for(int i=0;i<arLn-1;i++){

		}
	}

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
		if(!(arLst+i)->arEmpty && (arLst+i)->arGmId == gmId) gmCnt++;
	}
	return gmCnt;
}



