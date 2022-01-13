#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

BOOL SearchFilesByWildcard(WCHAR* wildcardPath)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA pNextInfo;

	//hFile = FindFirstFile(wildcardPath, &pNextInfo);//����취����Ŀ��>���ԡ�>�ַ��� �޸�ΪUNICODE�ַ���
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

	//���� abc��ͷ��txt�ļ�
	printf("Search 1:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\abc*.txt");
	printf("\r\n");

	//���� abc��ͷ���ļ�
	printf("Search 2:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\abc*");
	printf("\r\n");

	//����jnt�ļ�
	printf("Search 3:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\*.jnt");
	printf("\r\n");

	//�����ļ���Ϊ4���ַ���txt�ļ�
	printf("Search 4:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\????.txt");
	printf("\r\n");

	//���Ұ���"����"���ļ�
	printf("Search 5:\r\n");
	SearchFilesByWildcard(L"E:\\Test\\*����*");
	printf("\r\n");

	getchar();
	return 0;
}
*/