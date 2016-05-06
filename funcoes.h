#ifndef FUNCOES_H
#define FUNCOES_H

#include <QString>
#include <string>
using namespace std;


QString converter_StringToQstring(std::string string);
std::string converter_QstringToString(QString qstring);
QString converter_Int_ToQstring(int number);
int converter_QstringToInt(QString qstring_int);

int conv_StringToInt(std::string string_number);
std::string conv_IntToString(int string_number);

#endif // FUNCOES_H
