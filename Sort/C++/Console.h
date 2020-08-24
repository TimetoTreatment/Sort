//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// �ܼ� ��� ����
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- �ܼ� ��� ����
		- �ڵ��� ���̸� ���� �� ����

	2. ���
		- ��� Ŀ�� ��ġ ����
		- ��� ���� ����
		- �ܼ� â ��ü �Ǵ� �Ϻ� ����
		- �ؽ�Ʈ ���� ���
		- �� ����� ��� ��ģ ���� ���
*/

#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Console
{
private:

	HANDLE mHandleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string mEraser;

	/* ���� ���ڿ��� ������ ��ȯ */
	int ColorNameToNumber(const string& colorName) const;

	Console() {}
	~Console() {}


public:

	/* Ŀ�� ��ġ ���� */
	void CursorPosition(int x, int y);

	/* �ؽ�Ʈ �� ���� */
	void Color(const string& foreground = "default", const string& background = "default");

	/* �ܼ� â ���� */
	void Clear();

	/* �ܼ� â �Ϻ� ���� */
	void Clear(int XPosStart, int YPosStart, int width, int height);

	/* ���ڿ� �Ǵ� ���� ��� */
	void Draw(string str_or_file, const char* color, int startX, int startY);
	void Draw(string str_or_file, const char* color);


private:
	static Console* sInstance;

public:
	static Console* Instance();
	static void Release();
};


