#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <stdio.h>
//#include <WINDOWS.H>
using namespace std;

#define MAX_PATH_1 99999

int find_all_files(const char* lpPath)
{
    char szFind[MAX_PATH_1];
    static string order = "";
    WIN32_FIND_DATA FindFileData;
    strcpy(szFind, lpPath);
    strcat(szFind, "\\*.*");//\\*.*为查找当前目录下以“任意文件名，任意扩展名”命名的文件  D:\\语音播报\\*

    cout << "szFind = " << szFind << endl;

    HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);//解决办法：项目—>属性—>字符集 修改为未设置
    if (INVALID_HANDLE_VALUE == hFind)
        return -1;

    do
    {
        //判断目标文件是否为文件夹
        if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {   
            cout << "cFileName = " << (const char*)FindFileData.cFileName << endl;
            if (strcmp((const char *)FindFileData.cFileName, ".") != 0 && strcmp((const char *)FindFileData.cFileName, "..") != 0)
            {
                string tempFileName = (const char*)FindFileData.cFileName;
                order.assign(tempFileName, 2, tempFileName.size() - 1);
                cout << "order = " << order << endl;
                //发现子目录，递归之
                char szFile[MAX_PATH_1] = { 0 };
                strcpy(szFile, lpPath);
                cout << "szFile = " << szFile << endl;
                strcat(szFile, "\\"); /*   D:\\语音播报\\    */
                cout << "szFile = " << szFile << endl;
                strcat(szFile, (const char*)FindFileData.cFileName);
                cout << "szFile = " << szFile << endl;
                find_all_files(szFile);//下一级子路径
            }
        }
        else
        {
            //找到文件，处理之
            cout << lpPath << "\\" << FindFileData.cFileName << endl;
            string temporaryName = (const char*)FindFileData.cFileName;
            cout << "temporaryName = " << temporaryName << endl;
            string oldName(lpPath);
            oldName += "\\";
            oldName += temporaryName;
            int pos = temporaryName.find("_");
            string newTemporaryName = temporaryName;
            if (pos != -1)
            {               
                newTemporaryName.replace(0, pos, order);
            }
            else
            {
                newTemporaryName = order + "_" + newTemporaryName;
            }
            cout << "newTemporaryName = " << newTemporaryName << endl;
            string newName(lpPath);
            newName += "\\";
            newName += newTemporaryName;
            if (rename(oldName.c_str(), newName.c_str()) == 0)  //把 old_filename 所指向的文件名改为 new_filename
                //printf("Renamed %s to %s.\n", oldName, newName);
                cout << "oldName = " << oldName + "->" + "newName = " << newName + "\n";
            else
                perror("rename");
            //cout<<"new:"<<FindFileData.cFileName<<endl;
            //const char* path_01 = "D:\\语音播报2\\01";
            string fileName = newName.substr(newName.find_last_of("\\") + 1);
            string newfilePath = "D:\\语音播报\\01";
            newfilePath.append("\\").append(fileName);
            CopyFile(newName.c_str(), newfilePath.c_str(), true);
        }
    } while (::FindNextFile(hFind, &FindFileData));

    ::FindClose(hFind);

    return 0;
}


//int main()
//{
//    const char* lpPath = "D:\\语音播报";
//    find_all_files(lpPath);
//    return 0;
//}

