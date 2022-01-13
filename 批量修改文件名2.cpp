#include <windows.h>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

const char flagStr[] = "@2x";

void fun(string rootPath)
{
    map<string, string> result;
    queue<string> directory;
    WIN32_FIND_DATA fileData;
    HANDLE hFindFile;
    //strcat_s(nextFile->path, "*.*");
    directory.push(rootPath);
    while (!directory.empty())
    {
        string forderPath = directory.front();
        rootPath = forderPath;
        directory.pop();
        forderPath += "*.*";
        hFindFile = ::FindFirstFile(forderPath.c_str(), &fileData);//解决办法：项目—>属性—>字符集 修改为未设置
        if (hFindFile != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (fileData.cFileName[0] == '.')continue;
                if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    string tempStr = rootPath + string(fileData.cFileName) + "\\";
                    directory.push(tempStr);
                }
                else
                {
                    string fileName = fileData.cFileName;
                    int pos = fileName.find(flagStr);
                    if (pos != -1)
                    {
                        string changeName = fileName;
                        changeName.erase(pos, 3);
                        result.insert(make_pair(rootPath + fileName, rootPath + changeName));
                    }
                }
            } while (::FindNextFile(hFindFile, &fileData));
        }
    }
    for (map<string, string>::iterator it = result.begin(); it != result.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
        rename(it->first.c_str(), it->second.c_str());
    }
}

//int main()
//{
//    fun("C:\\Users\\cyj\\Desktop\\Instance\\");
//    getchar();
//    return 0;
//}