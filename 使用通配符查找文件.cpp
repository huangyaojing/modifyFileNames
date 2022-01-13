#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

BOOL SearchFilesByWildcard(WCHAR* wildcardPath)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA pNextInfo;

	//hFile = FindFirstFile(wildcardPath, &pNextInfo);//解决办法：项目—>属性—>字符集 修改为UNICODE字符集
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}

	WCHAR infPath[MAX_PATH] = { 0 };
	if (pNextInfo.cFileName[0] != '.')
	{
		printf("Find result = %ws\r\n", pNextInfo.cFileName);
	}

	while (FindNextFile(hFile, &pNextInfo))
	{
		if (pNextInfo.cFileName[0] == '.')
		{
			continue;
		}

		printf("Find result = %ws\r\n", pNextInfo.cFileName);
	}

	return FALSE;
}
/*
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");

	//查找 abc开头的txt文件
	printf("Search 1:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\abc*.txt");
	printf("\r\n");

	//查找 abc开头的文件
	printf("Search 2:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\abc*");
	printf("\r\n");

	//查找jnt文件
	printf("Search 3:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\*.jnt");
	printf("\r\n");

	//查找文件名为4个字符的txt文件
	printf("Search 4:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\????.txt");
	printf("\r\n");

	//查找包含"档案"的文件
	printf("Search 5:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\*档案*");
	printf("\r\n");

	getchar();
	return 0;
}
*/