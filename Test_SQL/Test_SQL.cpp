// Test_SQL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include <vector>
#include "sort.h"
#include "Windows.h"
#include "MyString.h"

using namespace std;
//#include "DbgHelp.h"
#include <tchar.h>
#ifdef WIN32
#include <io.h>		// windows
#include <Windows.h>
#pragma warning(disable:4091)
#include <DbgHelp.h>
#else
#include <unistd.h>		// linux
#endif
#pragma comment(lib,"dbghelp.lib")    // dump
#include <metahost.h>  
#include <mscoree.h> 

//int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
//{
//    // 定义函数指针
//    typedef BOOL(WINAPI* MiniDumpWriteDumpT)(
//        HANDLE,
//        DWORD,
//        HANDLE,
//        MINIDUMP_TYPE,
//        PMINIDUMP_EXCEPTION_INFORMATION,
//        PMINIDUMP_USER_STREAM_INFORMATION,
//        PMINIDUMP_CALLBACK_INFORMATION
//        );
//    // 从 "DbgHelp.dll" 库中获取 "MiniDumpWriteDump" 函数
//    MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
//    HMODULE hDbgHelp = LoadLibrary(_T("DbgHelp.dll"));
//    if (NULL == hDbgHelp)
//    {
//        return EXCEPTION_CONTINUE_EXECUTION;
//    }
//    pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
//
//    if (NULL == pfnMiniDumpWriteDump)
//    {
//        FreeLibrary(hDbgHelp);
//        return EXCEPTION_CONTINUE_EXECUTION;
//    }
//    // 创建 dmp 文件件
//    TCHAR szFileName[MAX_PATH] = { 0 };
//    //TCHAR* szVersion = _T("DumpDemo_v1.0");
//    TCHAR* szVersion = ("DumpDemo_v1.0");
//    SYSTEMTIME stLocalTime;
//    GetLocalTime(&stLocalTime);
//    wsprintf(szFileName, L"%s-%04d%02d%02d-%02d%02d%02d.dmp",
//        szVersion, stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
//        stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);
//    HANDLE hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
//        FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
//    if (INVALID_HANDLE_VALUE == hDumpFile)
//    {
//        FreeLibrary(hDbgHelp);
//        return EXCEPTION_CONTINUE_EXECUTION;
//    }
//    // 写入 dmp 文件
//    MINIDUMP_EXCEPTION_INFORMATION expParam;
//    expParam.ThreadId = GetCurrentThreadId();
//    expParam.ExceptionPointers = pExceptionPointers;
//    expParam.ClientPointers = FALSE;
//    pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
//        hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);
//    // 释放文件
//    CloseHandle(hDumpFile);
//    FreeLibrary(hDbgHelp);
//    return EXCEPTION_EXECUTE_HANDLER;
//}
//
//LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
//{
//    // 这里做一些异常的过滤或提示
//    if (IsDebuggerPresent())
//    {
//        return EXCEPTION_CONTINUE_SEARCH;
//    }
//    return GenerateMiniDump(lpExceptionInfo);
//}

static LONG WINAPI pfnUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}

	HMODULE hDbgHelp = LoadLibrary(L"dbghelp.dll");
	if (NULL == hDbgHelp)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	SYSTEMTIME stSysTime;
	memset(&stSysTime, 0, sizeof(SYSTEMTIME));
	GetLocalTime(&stSysTime);

	char szFile[MAX_PATH] = { 0 };		//根据字符集，有时候可能为WCHAR
	// 判断目录是否存在
	if (ENOENT == _access_s(".\\dump", 0))
	{
		CreateDirectoryA(".\\dump", NULL);
	}

	sprintf_s(szFile, ".\\dump\\%0.4d-%0.2d-%0.2d-%0.2d-%0.2d-%0.2d-%0.3d.dmp", \
		stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, \
		stSysTime.wMinute, stSysTime.wSecond, stSysTime.wMilliseconds);

	HANDLE hFile = CreateFileA(szFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, \
		0, CREATE_ALWAYS, 0, 0);
	if (INVALID_HANDLE_VALUE != hFile)
	{
		MINIDUMP_EXCEPTION_INFORMATION objExInfo;
		objExInfo.ThreadId = ::GetCurrentThreadId();
		objExInfo.ExceptionPointers = pExceptionInfo;
		objExInfo.ClientPointers = NULL;

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, \
			MiniDumpWithDataSegs, (pExceptionInfo ? &objExInfo : NULL), NULL, NULL);
		CloseHandle(hFile);
	}

	FreeLibrary(hDbgHelp);

	return EXCEPTION_EXECUTE_HANDLER;
}
#define CRTDBG_MAP_ALLOC 
#include <crtdbg.h>  
#include "Composite.h"
int main()
{
	
    SetUnhandledExceptionFilter(pfnUnhandledExceptionFilter);
   // SetUnhandledExceptionFilter(ExceptionFilter);
    int arr[5] = {3,5,78,89,9};
   // BubbleSort(arr,5);
	QuickSort(arr,0,4);
    int x = 8;
	////int* pInt = new int[10];
	//_CrtDumpMemoryLeaks();
	//system("pause");
	/*char arr[] = "hello";
	char arr2[] = "hellf";
	
	int xx = Mymemcmp(arr, arr2,5);*/
	/*Component* leaf1 = new Leaf();
	Component* leaf2 = new Leaf();

	Composite* composite1 = new Composite();
	composite1->add(leaf1);
	composite1->add(leaf2);

	Composite* composite2 = new Composite();
	composite2->add(composite1);

	composite2->operation();*/
	
	int te = 0;
}

