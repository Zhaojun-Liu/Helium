
#include"utils.h"


string stdfuncallconv ReplaceString(string rawstr, string deststr, string repstr)
{
    string text = rawstr;
    int iter = text.find(deststr);
    text.replace(iter, iter + deststr.size(), repstr);
    return text;
}

bool stdfuncallconv have(string a, string b)
{
    if (a.find(b) != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> split(const string& str, const string& pattern)
{
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    vector<string> resultVec;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultVec;
}

list<string> splittolist(const string& str, const string& pattern)
{
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    list<string> resultList;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultList.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultList;
}

string makestring(list<string> list_, string spiliter)
{
    string result;
    for (auto iter = list_.begin(); iter != list_.end(); iter++)
    {
        result.append(iter->c_str());
        if (iter == list_.end())
        {
            //�ڽ�β���ӷָ���
        }
        else
        {
            result.append(spiliter);
        }
    }
    return result;
}

string makestring(vector<string> list_, string spiliter)
{
    string result;
    for (auto iter = list_.begin(); iter != list_.end(); iter++)
    {
        result.append(iter->c_str());
        if (iter == list_.end())
        {
            //�ڽ�β���ӷָ���
        }
        else
        {
            result.append(spiliter);
        }
    }
    return result;
}


//Ѱ���ļ����Ƿ���� strpath:Ŀ¼
//����true��Ϊ�ļ��д��� ����falseΪ�ļ��в����ڻ���Ϊ�ļ�
/**
bool CheckFolderExist(const string& strPath) {
    HANDLE hTest;
    string folder;
    folder.append(".\\").append(strPath);
    WIN32_FIND_DATA wfdFind;
    hTest = FindFirstFile(folder.c_str(), &wfdFind);
    if ((hTest == INVALID_HANDLE_VALUE) && wfdFind.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
    {
        FindClose(hTest);
        return true;
    }
    return false;
}

vector<string> stdfuncallconv ListFiles(string path)
{
    CheckFolderExist(path);
    HANDLE hFind;
    vector<string> result;
    string path_ = path + "\\*";
    WIN32_FIND_DATA wfdFind;
    hFind = FindFirstFile(path_.c_str(), &wfdFind);
    DWORD dwError = 0;
    if (hFind == INVALID_HANDLE_VALUE) {}
    else
    {
        string tmp;
        do
        {
            if (wfdFind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {

            }
            else
            {
                tmp = wfdFind.cFileName;
                result.push_back(tmp);
            }
        } while (FindNextFile(hFind, &wfdFind) != 0);
        dwError = GetLastError();
        if (dwError != ERROR_NO_MORE_FILES)
        {
            return result;
        }

    }
    FindClose(hFind);
    return result;
}

vector<string> stdfuncallconv ListFiles(string path, string ext)
{
    CheckFolderExist(path);
    HANDLE hFind;
    vector<string> result;
    string path_ = path + "\\*";
    WIN32_FIND_DATA wfdFind;
    hFind = FindFirstFile(path_.c_str(), &wfdFind);
    DWORD dwError = 0;
    if (hFind == INVALID_HANDLE_VALUE) {}
    else
    {
        string tmp;
        do
        {
            if (wfdFind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {

            }
            else
            {
                tmp = wfdFind.cFileName;
                vector<string> filenames = split(tmp, ".");
                if (filenames[filenames.size() + 1] == ext)
                {
                    result.push_back(tmp);
                }

            }
        } while (FindNextFile(hFind, &wfdFind) != 0);
        dwError = GetLastError();
        if (dwError != ERROR_NO_MORE_FILES)
        {
            return result;
        }

    }
    FindClose(hFind);
    return result;
}
*/



