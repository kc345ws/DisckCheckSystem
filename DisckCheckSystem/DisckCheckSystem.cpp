// DisckCheckSystem.cpp: 定义控制台应用程序的入口点。
//
//硬盘检测信息形态

#include "stdafx.h"

#include<windows.h>

#include<iostream>

#include<string>
using namespace std;

//声明逻辑磁盘类型

struct
{
	UINT type; //GetDriveType返回类型
	LPCSTR name;//ASCII名称 
}
DriveTypeFlags[] = {
	{DRIVE_NO_ROOT_DIR,"无效路径"},
	{DRIVE_REMOVABLE,"移动硬盘"},
	{DRIVE_FIXED,"固定硬盘"},
	{DRIVE_REMOTE,"网络驱动器"},
	{DRIVE_CDROM,"CD_ROM"},
	{DRIVE_RAMDISK,"随机存储"},
	{0,NULL},
	{DRIVE_UNKNOWN,"未知"},
};


int main()
{
	//获取逻辑驱动器的字符串: A:\ B:\ C:\ D:\.....
	TCHAR cBuffer[100];

	//以位图形式代替字符串形式获取信息
	DWORD dLen = GetLogicalDriveStrings(sizeof(cBuffer) / sizeof(TCHAR), cBuffer);

	//获取且显示每一个驱动器的信息

	string msg = "本地逻辑驱动器列表:\n";

	for (TCHAR *s = cBuffer; *s; s += _tcslen(s) + 1)
	{
		LPCTSTR sDrivePath = s;
		msg += sDrivePath;
		msg += " ";

		//获取枚举类型
		UINT uDriveType = GetDriveType(sDrivePath);

		//查找驱动器类型
		for (int i = 0; DriveTypeFlags[i].name; i++)
		{
			if (uDriveType == DriveTypeFlags[i].type)
			{
				msg += DriveTypeFlags[i].name;
				break;
			}
		}
		msg += "\n";
	}
	cout << msg.c_str();

    return 0;
}

