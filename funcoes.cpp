#include "funcoes.h"



    QString converter_StringToQstring(std::string string){     //Converte QString para String.
        QString convert;
        convert = QString::fromUtf8(string.c_str());

        return convert;
    }

    std::string converter_QstringToString(QString qstring){     //Converte QString para String.
        std::string convert;
        convert = qstring.toUtf8().constData();

        return convert;
    }

    QString converter_Int_ToQstring(int number){     //Converte int para QString.
        QString convert;
        convert = QString::number(number);

        return convert;
    }

    int converter_QstringToInt(QString qstring_int){     //Converte QString para int.
        int convert;
        convert = qstring_int.toInt();

        return convert;
    }


    int conv_StringToInt(string string_number)
    {
        return atoi(string_number.c_str());
    }

    string conv_IntToString(int number)
    {
        return std::to_string(number);
    }
