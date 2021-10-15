/*
 * StringUtils.c
 * Created on: 12 oct. 2021
 * Author: mdangelo
 */

#include <stdio.h>
#include <ctype.h>
#include "Properties.h"
#include "StringUtils.h"

void str_showStringMatrix(char* strValues[], int rows){
	for(int i=0; i<rows; i++){
		printf("%s\n",*(strValues+i));
	}
}

void str_getStringInput(char* strInput, int ln, char* strMssg){
	printf("%s\n", strMssg);
	__fpurge(stdin);
	fgets(strInput, ln,stdin);
}

char str_getYesNoQstion(char* strMssg){
	char qst;
	printf("%s\n", strMssg);
	__fpurge(stdin);
	scanf("%c",&qst);
	qst = toupper(qst);

	return qst;
}

int str_cleanString(char* strValue, int length){
	int success = TRUE;
	int strSize;

	if(strValue != NULL){
		strSize = str_getStringSize(strValue, length);
		*(strValue+(strSize-1))=0;
	}else{
		success = FALSE;
	}

	return success;
}

int str_getStringSize(char* strValue, int length){
	int i;
	if(strValue != NULL){
		for(i=0;*(strValue+i)!=0 && i<length;i++);
	}else{
		i = -1;
	}
	return i;
}

