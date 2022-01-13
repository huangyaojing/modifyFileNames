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
    //文件句柄  
    //long hFile = 0;  //win7
    intptr_t hFile = 0;   //win10
    //文件信息  
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
        // "\\*"是指读取文件夹下的所有类型的文件，若想读取特定类型的文件，以png为例，则用“\\*.png”
    {
        cout << "p = " << p << endl;
        do
        {
            //如果是目录,迭代之  
            //如果不是,加入列表  
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
        CopyFile(filePath.c_str(), newfilePath.c_str(), true);//false代表覆盖，true不覆盖
    }
}

string getWorkPath()
{
    char   szBuf[256];
    char* p;
    GetModuleFileName(NULL, szBuf, sizeof(szBuf));//拿到全部路径 
    p = szBuf;
    string exePath = p;
    cout << "p = " << p << endl;
    exePath = exePath.substr(0, exePath.find_last_of("\\"));
    cout << "exePath = " << exePath << endl;
    return exePath;
}

/*
* 程序功能：将test文件夹（C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test）下面的每个
* 文件夹下面的文件依次复制到Debug文件夹（C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug）下
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
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600地砖薄贴机器人已开机.mp3
name = AW002
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\*
name = .
name = ..
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600地砖薄贴机器人已开机.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_正在自检请稍侯.mp3
name = AW003
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\*
name = .
name = ..
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600地砖薄贴机器人已开机.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_正在自检请稍侯.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_机器自检正常可以使用.mp3
name = AW013
p = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\*
name = .
name = ..
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600地砖薄贴机器人已开机.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_正在自检请稍侯.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_机器自检正常可以使用.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\013_调缝.mp3
list<string> files =
C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600地砖薄贴机器人已开机.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_正在自检请稍侯.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_机器自检正常可以使用.mp3 C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\013_调缝.mp3
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW001\001_600地砖薄贴机器人已开机.mp3
fileName = 001_600地砖薄贴机器人已开机.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW002\002_正在自检请稍侯.mp3
fileName = 002_正在自检请稍侯.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW003\003_机器自检正常可以使用.mp3
fileName = 003_机器自检正常可以使用.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
filePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug\test\AW013\013_调缝.mp3
fileName = 013_调缝.mp3
newfilePath = C:\Users\huangzhaojing01\source\repos\Modifyfilename\x64\Debug
*/

