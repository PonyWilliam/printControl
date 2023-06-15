#pragma once
// ʹ��PrintControl�����
#ifndef PrintControl_H
#define PrintControl_H
#include <windows.h>
#include <winspool.h>
class __declspec(dllexport) PrintControl
{
public:
	PrintControl(const char* filepath, int number);// ���캯��
	~PrintControl();// ��������
	void SetPath(const char* filepath);// �����ļ�·��
	void print_file();// ��ʼ��ӡ�ļ�
	void print_once(); // ��ӡһ��
	void setNumber(int number);

private:
	const char* filePath; // ��ӡ�ļ�·��
	int number = 1; // ��ӡ����,Ĭ��Ϊ1
};
#endif // !PrintControl_H