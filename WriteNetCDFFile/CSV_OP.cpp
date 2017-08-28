// CSV_OP.cpp : 定义控制台应用程序的入口点。
//

#include <tchar.h>
#include "CSVOperator.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

    CCSVOperator CSVOperator;
    CSVOperator.LoadCSV("config.csv");

    std::string* pString = CSVOperator.GetString(1,1);
    if (pString)
    {
        std::cout<< pString->c_str() << '\n';
    }

    pString = CSVOperator.GetString(2,4);
    if (pString)
    {
        std::cout<< pString->c_str() << '\n';
    }
    
    int _int = 0;
    if (CSVOperator.GetInt(3,1,_int))
    {
        std::cout<< _int <<'\n';
    }

    float _float = 0.0f;
    if (CSVOperator.GetFloat(4,1, _float))
    {
        std::cout<< _float<<'\n';
    }


    system("pause");
	return 0;
}

