/*
 * SaloonRepo.c
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#include <stdio.h>
#include "../commons/Properties.h"
#include "SaloonRepo.h"

void sr_initSaloonListHardCd(SaloonEntity* slLst,int from, int until){
	for(int i=from;i<until; i++){
		(slLst+i)->slId = -111;
		(slLst+i)->slEmpty = TRUE;
	}
}

int sr_initSaloonList(SaloonEntity* slLst, int slLn){
	int success = TRUE;
	if(slLst == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		for(int i=0;i<slLn; i++){
			(slLst+i)->slId = -111;
			(slLst+i)->slEmpty = TRUE;
		}
	}
	return success;
}

void sr_showASaloon(SaloonEntity slEnt){
	char slTypeStr[STR_50];
	sr_getSaloonDescByType(slEnt.slType,slTypeStr);
	printf("-salon.id=%d | salon.nombre=%s | salon.domicilio=%s | salon.tipo=%s\n",slEnt.slId,slEnt.slName,slEnt.slAddress,slTypeStr);
}

void sr_getSaloonById(SaloonEntity* slLst,int sLn,int slId,SaloonEntity* slEntAux){
	int cont = TRUE;
	for(int i=0;i<sLn && cont;i++){
		if(!(slLst+i)->slEmpty && (slLst+i)->slId==slId){
			*slEntAux = *(slLst+i);
			cont = FALSE;
		}
	}
}

void sr_getSaloonDescByType(int slType,char* slTypeStr){
	if(slType==1)
		strcpy(slTypeStr,"Shoping");
	else if(slType==2)
		strcpy(slTypeStr,"Local");
}
