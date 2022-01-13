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
    strcat(szFind, "\\*.*");//\\*.*Ϊ���ҵ�ǰĿ¼���ԡ������ļ�����������չ�����������ļ�  D:\\��������\\*

    cout << "szFind = " << szFind << endl;

    HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);//����취����Ŀ��>���ԡ�>�ַ��� �޸�Ϊδ����
    if (INVALID_HANDLE_VALUE == hFind)
        return -1;

    do
    {
        //�ж�Ŀ���ļ��Ƿ�Ϊ�ļ���
        if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {   
            cout << "cFileName = " << (const char*)FindFileData.cFileName << endl;
            if (strcmp((const char *)FindFileData.cFileName, ".") != 0 && strcmp((const char *)FindFileData.cFileName, "..") != 0)
            {
                string tempFileName = (const char*)FindFileData.cFileName;
                order.assign(tempFileName, 2, tempFileName.size() - 1);
                cout << "order = " << order << endl;
                //������Ŀ¼���ݹ�֮
                char szFile[MAX_PATH_1] = { 0 };
                strcpy(szFile, lpPath);
                cout << "szFile = " << szFile << endl;
                strcat(szFile, "\\"); /*   D:\\��������\\    */
                cout << "szFile = " << szFile << endl;
                strcat(szFile, (const char*)FindFileData.cFileName);
                cout << "szFile = " << szFile << endl;
                find_all_files(szFile);//��һ����·��
            }
        }
        else
        {
            //�ҵ��ļ�������֮
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
            if (rename(oldName.c_str(), newName.c_str()) == 0)  //�� old_filename ��ָ����ļ�����Ϊ new_filename
                //printf("Renamed %s to %s.\n", oldName, newName);
                cout << "oldName = " << oldName + "->" + "newName = " << newName + "\n";
            else
                perror("rename");
            //cout<<"new:"<<FindFileData.cFileName<<endl;
            //const char* path_01 = "D:\\��������2\\01";
            string fileName = newName.substr(newName.find_last_of("\\") + 1);
            string newfilePath = "D:\\��������\\01";
            newfilePath.append("\\").append(fileName);
            CopyFile(newName.c_str(), newfilePath.c_str(), true);
        }
    } while (::FindNextFile(hFind, &FindFileData));

    ::FindClose(hFind);

    return 0;
}


//int main()
//{
//    const char* lpPath = "D:\\��������";
//    find_all_files(lpPath);
//    return 0;
//}

