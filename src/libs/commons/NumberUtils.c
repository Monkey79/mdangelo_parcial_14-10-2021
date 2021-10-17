/*
 * NumberUtils.c
 *  Created on: 12 oct. 2021
 *  Author: mdangelo
 */

#include <stdio.h>
#include "NumberUtils.h"

int nmb_validateIntByRank(int value,int from,int until){
	return (value>=from && value<=until);
}

float nmb_getFloatInput(char* strMssg){
	float fNm = 0;
	printf("%s\n", strMssg);
	__fpurge(stdin);
	scanf("%f",&fNm);
	return fNm;
}

int nmb_getIntInput(char* strMssg){
	int iNm = 0;

	do{
		printf("%s\n", strMssg);
		__fpurge(stdin);
		scanf("%d",&iNm);
	}while(iNm<0);

	return iNm;
}
int nmb_getInputByRank(char* strMssg,int from, int until){
	int iNm = 0;
	do{
		printf("%s\n", strMssg);
		__fpurge(stdin);
		scanf("%d",&iNm);
	}while(iNm!=from && iNm!=until);

	return iNm;
}


