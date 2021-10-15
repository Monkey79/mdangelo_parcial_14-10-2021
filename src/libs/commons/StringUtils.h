/*
 * StringUtils.h
 * Created on: 12 oct. 2021
 * Author: mdangelo
 */

#ifndef LIBS_COMMONS_STRINGUTILS_H_
#define LIBS_COMMONS_STRINGUTILS_H_

void str_showStringMatrix(char* strValues[], int rows);
void str_getStringInput(char* strInput, int ln, char* strMssg);
char str_getYesNoQstion(char* strMssg);
int str_cleanString(char* strValue, int length);
int str_getStringSize(char* strValue, int length);

#endif /* LIBS_COMMONS_STRINGUTILS_H_ */
