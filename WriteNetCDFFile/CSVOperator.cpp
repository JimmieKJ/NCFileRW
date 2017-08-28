#include "CSVOperator.h"


//////////////////////////////////////////////////////////////////////////
//CSV operator

CCSVOperator::CCSVOperator(const char* path)
{
    LoadCSV(path);
}

bool CCSVOperator::LoadCSV(const char* path)
{
    FILE* pfile = fopen(path, "r");
    if (pfile)
    {
		fseek(pfile,0,SEEK_END);//函数设置文件指针stream的位置。
											//如果执行成功，stream将指向以fromwhere为基准，偏移offset（指针偏移量）个字节的位置，函数返回0。如果执行失败(比如offset超过文件自身大小)，则不改变stream指向的位置，函数返回一个非0值。
        u32 dwsize = ftell(pfile);//用于得到文件位置指针当前位置相对于文件首的偏移字节数。该函数对大于231-1文件，即：2.1G以上的文件操作时可能出错。
        rewind(pfile);//功能是将文件内部的指针重新指向一个流的开头

        char* filebuffer = new char[dwsize];
        fread(filebuffer, 1, dwsize, pfile);

        std::map<u32, std::string> StringMap;
        char* pBegin = filebuffer;
        char* pEnd = strchr(filebuffer, '\n');//extern char *strchr(const char *s,char c)，可以查找字符串s中首次出现字符'\n'的位置,返回首次出现_Val的位置的指针
        u32 uiIndex = 1;
        while (pEnd != NULL)
        {
            std::string strbuff;
            strbuff.insert(0, pBegin, pEnd-pBegin);
            if (!strbuff.empty())
            {
                StringMap[uiIndex] = strbuff;
            }
            pBegin = pEnd + 1;
            pEnd = strchr(pEnd + 1, '\n');
            ++uiIndex;
        }
        delete[] filebuffer;

        std::map<u32, std::string>::iterator iter = StringMap.begin();
        for (; iter != StringMap.end(); ++iter)
        {
            std::vector<std::string> StringVec;
            std::map<u32, std::string> l_StringMap;
            StringParser::GetParamFromString(iter->second, StringVec);
            for (int i = 0; i < StringVec.size(); ++i)
            {
                l_StringMap[i+1] = StringVec.at(i);
            }
            m_StringKeyMap[iter->first] = l_StringMap;
        }
        fclose(pfile);
        m_CSVName = path;
        return true;
    }

    return false;
}


bool CCSVOperator::GetInt(u32 uiLine, u32 uiRow, int& iValue)
{
    std::string* pKey = GetString(uiLine, uiRow);
    if (pKey)
    {
        iValue = atoi(pKey->c_str());
        return true;
    }
    else
    {
        return false;
    }
}

bool CCSVOperator::GetFloat(u32 uiLine, u32 uiRow, float& fValue)
{
    std::string* pKey = GetString(uiLine, uiRow);
    if (pKey)
    {
        fValue = atof(pKey->c_str());
        return true;
    }
    else
    {
        return false;
    }
}

std::string* CCSVOperator::GetString(u32 uiLine, u32 uiRow)
{
    std::map<u32, std::map<u32, std::string> >::iterator iterLine = m_StringKeyMap.find(uiLine);
    if (iterLine != m_StringKeyMap.end())
    {
        std::map<u32, std::string>& rStringMap = iterLine->second;
        std::map<u32, std::string>::iterator iterRow = rStringMap.find(uiRow);
        if (iterRow != rStringMap.end())
        {
            return &iterRow->second;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

bool CCSVOperator::SetNumber(u32 uiLine, u32 uiRow, int iValue)
{
    std::string* pKey = GetString(uiLine, uiRow);
    if (pKey)
    {
        char buffer[100];
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%d", iValue);
        pKey->clear();
        *pKey = buffer;
        return true;
    }
    else
    {
        return false;
    }
}

bool CCSVOperator::SetNumber(u32 uiLine, u32 uiRow, float fValue)
{
    std::string* pKey = GetString(uiLine, uiRow);
    if (pKey)
    {
        char buffer[100];
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%d", fValue);
        pKey->clear();
        *pKey = buffer;
        return true;
    }
    else
    {
        return false;
    }
}

bool CCSVOperator::SetString(u32 uiLine, u32 uiRow, const char* pStr)
{
    std::string* pKey = GetString(uiLine, uiRow);
    if (pKey)
    {
        pKey->clear();
        *pKey = pStr;
        return true;
    }
    else
    {
        return false;
    }
}

bool CCSVOperator::SaveCSV(const char* path)
{
    if (path != NULL)
    {
        m_CSVName = path;
    }

    FILE* pfile = fopen(m_CSVName.c_str(), "w");
    if (pfile)
    {
        std::map<u32, std::map<u32, std::string> >::iterator iter = m_StringKeyMap.begin();
        for (; iter != m_StringKeyMap.end(); ++iter)
        {
            std::map<u32, std::string>& rStringMap = iter->second;
            std::map<u32, std::string>::iterator it = rStringMap.begin();
            for (; it != rStringMap.end(); ++it)
            {
                std::string key = it->second;
                key += ',';
                fwrite(key.c_str(), 1, key.size(), pfile);
            }
            char Delim = '\n';
            fwrite(&Delim, 1, 1, pfile);
        }
        fclose(pfile);
    }
    else
    {
        return false;
    }

    return true;
}