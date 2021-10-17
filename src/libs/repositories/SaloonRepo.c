/*
 * SaloonRepo.c
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#include <stdio.h>
#include "../commons/Properties.h"
#include "SaloonRepo.h"

#define  NO_SALOON_SPACE "-No hay mas espacio en la lista de salones-\n"
#define NO_SALOON_ID "-No existe salon con ese id-\n"
#define SALOON_DELETE_SUCCESS "-salon eliminado con exito-\n"

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

int sr_saveSaloon(SaloonEntity* slLst, int slLn, SaloonEntity slEnt, int frIdx){
	int success = TRUE;
	int i=frIdx; //indice libre

	if(slLst == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		if(i>=0){
			*(slLst+i) = slEnt;
		}else{
			printf(NO_SALOON_SPACE);
			success = FALSE;
		}
	}
	return success;
}

int sr_deleteSaloonById(SaloonEntity* slLst, int slLn, int slId){
	int success = TRUE;
	int idx;

	if(slLst == NULL){
		printf(NULL_POINTER);
		success = FALSE;
	}else {
		idx = sr_getSaloonIndxById(slLst,slLn,slId);
		if(idx>=0){
			(slLst+idx)->slEmpty = TRUE;
			(slLst+idx)->slId = -111;
			//TODO deberia correr a la izq (si hay) los restantes elementos ocupados
			printf(SALOON_DELETE_SUCCESS);
		}else{
			printf(NO_SALOON_ID);
			success = FALSE;
		}
	}
	return success;
}

int sr_getFreeSalonIndx(SaloonEntity* slLst, int slLn){
	int i;
	for(i=0;i<slLn && !(slLst+i)->slEmpty; i++);
	return ((slLst+i)->slEmpty)?i:-1;
}

int sr_thereAreSaloons(SaloonEntity* slLst, int slLn){
	int i;
	int noSlns = TRUE;

	for(i=0;i<slLn && noSlns; i++){
		if(!(slLst+i)->slEmpty) noSlns=FALSE;
	}

	return !noSlns;
}

int sr_isAValidSaloonId(SaloonEntity* slLst, int slLn, int slId){
	int isValid = FALSE;

	for(int i=0;i<slLn && !isValid; i++){
		if(!(slLst+i)->slEmpty){
			isValid = (slLst+i)->slId == slId;
		}
	}

	return isValid;
}

void sr_showASaloon(SaloonEntity slEnt){
	char slTypeStr[STR_50];
	sr_getSaloonDescByType(slEnt.slType,slTypeStr);
	printf("-salon.id=%d | salon.nombre=%s | salon.domicilio=%s | salon.tipo=%s\n",slEnt.slId,slEnt.slName,slEnt.slAddress,slTypeStr);
}

void sr_showAllSaloon(SaloonEntity* slLst,int sLn){
	char slTypeStr[STR_50];
	for(int i=0;i<sLn;i++){
		if(!(slLst+i)->slEmpty){
			sr_getSaloonDescByType((slLst+i)->slType,slTypeStr);
			printf("-salon.id=%d | salon.nombre=%s | salon.domicilio=%s | salon.tipo=%s\n",(slLst+i)->slId,(slLst+i)->slName,
							(slLst+i)->slAddress,slTypeStr);
		}
	}
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

int sr_getSaloonIndxById(SaloonEntity* slLst,int sLn,int slId){
	int cont = TRUE;
	int idx=-1;
	for(int i=0;i<sLn && cont;i++){
		if(!(slLst+i)->slEmpty && (slLst+i)->slId==slId){
			idx = i;
			cont = FALSE;
		}
	}
	return idx;
}

void sr_getSaloonDescByType(int slType,char* slTypeStr){
	if(slType==1)
		strcpy(slTypeStr,"Shoping");
	else if(slType==2)
		strcpy(slTypeStr,"Local");
}

void sr_getSaloonNameById(SaloonEntity* slLst,int sLn,int slId,char* slName){
	int cont = FALSE;
	int idx=-1;
	for(int i=0;i<sLn && !cont;i++){
		if(!(slLst+i)->slEmpty){
			cont = (slLst+i)->slId==slId;
			if(cont){
				strcpy(slName,(slLst+i)->slName);
			}
		}
	}
}
