// Test_SQL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include <vector>
#include "sort.h"
#include "Windows.h"
#include "MyString.h"
#include "common.h"

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
#include <list>
#include <vector>
using namespace std;

//渣渣版
NodeL* addTwoNumbers(NodeL* l1, NodeL* l2) {
	list<int> num;
	vector<int> num1, num2;
	int big = 0, i1 = 0, i2 = 0;
	for (l1; nullptr != l1; l1 = l1->next)
	{
		num1.push_back(l1->value);
		i1++;
	}

	for (l2; nullptr != l2; l2 = l2->next)
	{
		num2.push_back(l2->value);
		i2++;
	}


	//计算到list中
	big = max(i1,i2);
	int x1 = 0, x2 = 0, total = 0,next = 0;
	for (int i = 0;i < big;++i)
	{
		x1 = 0, x2 = 0, total = 0;
		if (i < i1) //第一个列表
		{
			x1 = num1[i];
		}
		if (i < i2)
		{
			x2 = num2[i];
		}
		total = x1 + x2 + next;
		next = 0;
		if (total/10 > 0)
		{
			total %= 10;
			next = 1;
		}
		num.push_front(total);
	}
	if (1== next)
	{
		num.push_front(next);
	}


	NodeL* ret = nullptr;
	NodeL* head = nullptr;
	list<int>::iterator itor;
	for (itor = num.begin();itor != num.end();++itor)
	{
		if ( nullptr == head)
		{
			ret = new NodeL(*itor);
			head = ret ;
		}
		else
		{
			ret->next = new NodeL(*itor);
			ret = ret->next;
		}

	}

	return head;
}

//NB 版
NodeL* addTwoNumbers_(NodeL* l1, NodeL* l2) {
	int carry = 0;
	int sum = 0;
	NodeL* newhead = new NodeL(0, nullptr);
	NodeL* nownode = newhead;
	while (l1 || l2 || carry)
	{
		sum = (l1 ? l1->value : 0) + (l2 ? l2->value : 0) + carry;
		carry = sum / 10;
		NodeL* node = new NodeL(sum % 10, nullptr);
		nownode->next = node;
		nownode = nownode->next;

		l1 = l1 ? l1->next : l1;
		l2 = l2 ? l2->next : l2;
	}

	return newhead->next;
}

NodeL* deleteDuplicates_(NodeL* head)
{
	if (nullptr == head || nullptr == head->next)
		return head;
	NodeL* v_slow = head;
	NodeL* v_fast = head->next;
	while (v_fast)
	{
		if (v_slow->value < v_fast->value)
		{
			v_slow = v_slow->next;
			v_slow->value = v_fast->value;
		}
		v_fast = v_fast->next;
	}
	if (nullptr != v_slow->next)
	{
		v_fast = v_slow->next; //截断
		v_slow->next = nullptr;


		while (nullptr != v_fast)
		{
			v_slow = v_fast;
			v_fast = v_fast->next;
			delete v_slow;
			v_slow = nullptr;
		}

	}
	return head;
}
//反转链表
NodeL* reverseList(NodeL* head)
{
	if (nullptr == head || nullptr == head->next)
		return head;
	NodeL* p = head, * q = head->next,*t = nullptr;
	//p->next = nullptr;
	while (nullptr != q)
	{
		t = q->next;
		q->next = p;
		p = q;
		q = t;
	}
	head->next = nullptr;
	return p;
}
#include <set>
bool isHappy(int n)
{
	long long xx = n;
	set<int> v_set;
	while (1 != xx)
	{
		int temp = xx,num = 0;
		xx = 0;
		while (temp > 0)
		{
			num = temp%10;
			xx += (num * num);
			temp /= 10;
			if (xx > 0x7fffffff)
			{
				return false;
			}
		}
		if (v_set.find(xx) != v_set.end() || v_set.size() > 100000)
			return false;
		v_set.insert(xx);

	}
	return true;
}

bool containsDuplicate(vector<int>& nums) 
{
	set<int> v_set;
	for (int i:nums)
	{
		if (v_set.find(i) != v_set.end())
			return true;
		v_set.insert(i);
	}
	return false;
}

class AB
{
public:
	int* m_p;
	int m_num;

	AB(int *p,int num)
	{
		m_p = nullptr;
		m_num = 0;
	}
	~AB()
	{

	}
};

int main()
{
	
    SetUnhandledExceptionFilter(pfnUnhandledExceptionFilter);
   // SetUnhandledExceptionFilter(ExceptionFilter);
 //   int arr[5] = {3,5,78,89,9};
 //  // BubbleSort(arr,5);
	//QuickSort(arr,0,4);
 //   int x = 8;
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
	NodeL* l1 = new NodeL(9);
	/*l1->next = new NodeL(4);
	l1->next->next = new NodeL(3);*/
	//l1->next->next->next = new NodeL(0);

	NodeL* l2 = new NodeL(1);
	l2->next = new NodeL(1);
	l2->next->next = new NodeL(2);
	l2->next->next->next = new NodeL(9);
	l2->next->next->next->next = new NodeL(9);
	//l2->next->next->next->next->next = new NodeL(9);
	//l2->next->next->next->next->next->next = new NodeL(9);
	//l2->next->next->next->next->next->next->next = new NodeL(9);
	//l2->next->next->next->next->next->next->next->next = new NodeL(9);
	//l2->next->next->next->next->next->next->next->next->next = new NodeL(9);
	//l2->next->next->next = new NodeL(0);
	//NodeL* xx = reverseList(l2);
	//addTwoNumbers_(l1,l2);
	bool tx = isHappy(77);
	cout << tx << endl;
	int&& te = 10;
	te = 0;
	cout << te << endl;
	int xx = te;
	string str("dddd");
	//cout << str << endl;
	string str1 = std::move(str);
	string str2 = std::forward<string>(str1);
	//cout << str1 << " "<< te << endl;
}

