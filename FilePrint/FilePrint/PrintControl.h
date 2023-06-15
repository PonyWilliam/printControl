#pragma once
// 使用PrintControl类控制
#ifndef PrintControl_H
#define PrintControl_H
#include <windows.h>
#include <winspool.h>
class __declspec(dllexport) PrintControl
{
public:
	PrintControl(const char* filepath, int number);// 构造函数
	~PrintControl();// 析构函数
	void SetPath(const char* filepath);// 设置文件路径
	void print_file();// 开始打印文件
	void print_once(); // 打印一次
	void setNumber(int number);

private:
	const char* filePath; // 打印文件路径
	int number = 1; // 打印份数,默认为1
};
#endif // !PrintControl_H