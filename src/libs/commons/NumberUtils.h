/*
 * NumberUtils.h
 *
 *  Created on: 12 oct. 2021
 *      Author: monkey
 */

#ifndef LIBS_COMMONS_NUMBERUTILS_H_
#define LIBS_COMMONS_NUMBERUTILS_H_

int nmb_validateIntByRank(int value,int from,int until);
float nmb_getFloatInput(char* strMssg);
int nmb_getIntInput(char* strMssg);
int nmb_getInputByRank(char* strMssg,int from, int until);

#endif /* LIBS_COMMONS_NUMBERUTILS_H_ */
