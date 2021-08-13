
#include"utils.h"
bool _stdcall Split(const std::string& str, std::map<size_t, std::string>& ret, std::string sep) { // https://blog.csdn.net/qq_22186119/article/details/110472493
    if (str.empty()) {
        return false;
    }

    std::string temp;
    std::string::size_type begin = str.find_first_not_of(sep);
    std::string::size_type pos = 0;
    size_t line = 0;
    while (begin != std::string::npos) {
        line += 1;
        pos = str.find(sep, begin);
        if (pos != std::string::npos) {
            temp = str.substr(begin, pos - begin);
            begin = pos + sep.length();
        }
        else {
            temp = str.substr(begin);
            begin = pos;
        }

        if (!temp.empty()) {
            ret[line] = temp;
            temp.clear();
        }
    }
    return true;
}

string stdfuncallconv _stdcall ReplaceString(string rawstr, string deststr, string repstr)
{
    string text = rawstr;
    int iter = text.find(deststr);
    text.replace(iter, iter + deststr.size(), repstr);
    return text;
}

bool stdfuncallconv _stdcall have(string a, string b)
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

vector<string> _stdcall split(const string& str, const string& pattern)
{
    std::vector<std::string> resVec;
    if ("" == str)
    {
        return resVec;
    }
    //方便截取最后一段数据
    std::string strs;
    strs.append(pattern);

    size_t pos = strs.find(pattern);
    size_t size = strs.size();

    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0, pos);
        if (!x.empty())
            resVec.push_back(x);
        strs = strs.substr(pos + 1, size);
        pos = strs.find(pattern);
    }

    return resVec;
}

vector<string> _stdcall split(string str, const char* pattern)
{
    std::vector<std::string> resVec;
        if ("" == str)
        {
            return resVec;
        }
         //方便截取最后一段数据
        std::string strs;
        strs.append(pattern);
    
        size_t pos = strs.find(pattern);
        size_t size = strs.size();
    
        while (pos != std::string::npos)
        {
            std::string x = strs.substr(0, pos);
            if(!x.empty())
                resVec.push_back(x);
            strs = strs.substr(pos + 1, size);
            pos = strs.find(pattern);
        }
    
        return resVec;
}


list<string> _stdcall splittolist(const string& str, const string& pattern)
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

string _stdcall makestring(list<string> list_, string spiliter)
{
    string result;
    for (auto iter = list_.begin(); iter != list_.end(); iter++)
    {
        result.append(iter->c_str());
        if (iter == list_.end())
        {
            //在结尾不加分隔符
        }
        else
        {
            result.append(spiliter);
        }
    }
    return result;
}

string _stdcall makestring(vector<string> list_, string spiliter)
{
    string result;
    for (auto iter = list_.begin(); iter != list_.end(); iter++)
    {
        result.append(iter->c_str());
        if (iter == list_.end())
        {
            //在结尾不加分隔符
        }
        else
        {
            result.append(spiliter);
        }
    }
    return result;
}


