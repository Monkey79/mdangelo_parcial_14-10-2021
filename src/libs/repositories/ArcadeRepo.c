/*
 * ArcadeRepo.c
 *  Created on: 15 oct. 2021
 *  Author: mdangelo
 */

#include <stdio.h>
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

//---Informes---
int ar_getArcadeNmBySlId(ArcadeEntity* arLst, int arLn, int slId){
	int arNm=0;
	for(int i=0;i<arLn;i++){
		if(!(arLst+i)->arEmpty){
			if((arLst+i)->arSlId == slId) arNm++;
		}
	}
	return arNm;
}


