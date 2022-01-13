#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include<io.h>
#include<iostream>
using namespace std;
void getAllFiles(string path, list<string>& files);
void copyAllFiles(list<string>& files, string dirNewPath);
string getWorkPath();

int main(int argc, char* argv[])
{
    string exePath = getWorkPath();
    list<string> files;
    string oldPath = exePath;
    getAllFiles(oldPath.append("\\test"), files);
    copyAllFiles(files, exePath);
    return 0;
}

void getAllFiles(string path, list<string>& files)
{
    //�ļ����  
    //long hFile = 0;  //win7
    intptr_t hFile = 0;   //win10
    //�ļ���Ϣ  
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
        // "\\*"��ָ��ȡ�ļ����µ��������͵��ļ��������ȡ�ض����͵��ļ�����pngΪ�������á�\\*.png��
    {
        cout << "p = " << p << endl;
        do
        {
            //�����Ŀ¼,����֮  
            //�������,�����б�  
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                string name = fileinfo.name;
                cout << "name = " << name << endl;
                if (name.find(".", 0) == string::npos)
                    getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
            {
                files.push_back(path + "\\" + fileinfo.name);
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        cout << "list<string> files =" << endl;
        for (list<string>::const_iterator iter = files.begin(); iter != files.end(); iter++)
        {
            cout << * iter << " ";
        }
        cout << endl;
        _findclose(hFile);
    }
}

void copyAllFiles(list<string>& files, string dirNewPath)
{
    for (auto obj : files)
    {
        string filePath = obj;
        cout << "filePath = " << filePath << endl;
        string fileName = filePath.substr(filePath.find_last_of("\\") + 1);
        cout << "fileName = " << fileName << endl;
        string newfilePath = dirNewPath;
        cout << "newfilePath = " << newfilePath << endl;
        newfilePath.append("\\").append(fileName);
        CopyFile(filePath.c_str(), newfilePath.c_str(), true);//false�����ǣ�true������
    }
}

string getWorkPath()
{
    char   szBuf[256];
    char* p;
    GetModuleFileName(NULL, szBuf, sizeof(szBuf));//�õ�ȫ��·�� 
    p = szBuf;
    string exePath = p;
    cout << "p = " << p << endl;
    exePath = exePath.substr(0, exePath.find_last_of("\\"));
    cout << "exePath = " << exePath << endl;
    return exePath;
}

/*
* �����ܣ���test�ļ��У�C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test�������ÿ��
* �ļ���������ļ����θ��Ƶ�Debug�ļ��У�C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug����
* 
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\Modifyfilename.exe
exePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\*
name = .
name = ..
name = AW001
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\*
name = .
name = ..
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600��ש�����������ѿ���.mp3
name = AW002
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\*
name = .
name = ..
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600��ש�����������ѿ���.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_�����Լ����Ժ�.mp3
name = AW003
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\*
name = .
name = ..
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600��ש�����������ѿ���.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_�����Լ����Ժ�.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_�����Լ���������ʹ��.mp3
name = AW013
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\*
name = .
name = ..
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600��ש�����������ѿ���.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_�����Լ����Ժ�.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_�����Լ���������ʹ��.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\013_����.mp3
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600��ש�����������ѿ���.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_�����Լ����Ժ�.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_�����Լ���������ʹ��.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\013_����.mp3
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600��ש�����������ѿ���.mp3
fileName = 001_600��ש�����������ѿ���.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_�����Լ����Ժ�.mp3
fileName = 002_�����Լ����Ժ�.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_�����Լ���������ʹ��.mp3
fileName = 003_�����Լ���������ʹ��.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\013_����.mp3
fileName = 013_����.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
*/

