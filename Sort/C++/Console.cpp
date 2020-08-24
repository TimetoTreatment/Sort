#include "console.h"


///////////////////////////////
/* ���� ���ڿ��� ������ ��ȯ */
///////////////////////////////
int Console::ColorNameToNumber(const string& colorName) const
{
	if (colorName == "default")
		return -1;

	if (colorName == "random")						// ������ �ԷµǸ�
	{
		int colorSet[5] = { 12, 10, 3, 13, 14 };	// ������ ���� �߿���
		return colorSet[rand() % 5];				// �������� ����
	}
	else if (colorName == "red")	return 12;		// ����
	else if (colorName == "green")	return 10;		// �ʷ�
	else if (colorName == "blue")	return 3;		// �Ķ�
	else if (colorName == "purple")	return 13;		// ����
	else if (colorName == "yellow")	return 14;		// ���
	else if (colorName == "white")	return 15;		// �Ͼ�
	else if (colorName == "black")	return 0;		// ����

	return -1;
}


////////////////////
/* �ؽ�Ʈ �� ���� */
////////////////////
void Console::Color(const string& foreground, const string& background)
{
	int colorForeground = ColorNameToNumber(foreground);	// ���� ���� ���ڿ��� ������ ��ȯ
	int colorBackground = ColorNameToNumber(background);	// ��� ���� ���ڿ��� ������ ��ȯ
	int colorValue;

	if (colorForeground == -1) colorForeground = 7;			// �⺻ �� 7
	if (colorBackground == -1) colorBackground = 0;			// �⺻ �� 0
	colorValue = (colorBackground * 16) + colorForeground;	// ������ ��ȯ�� ���� �����ϰ� ����

	SetConsoleTextAttribute(mHandleConsole, colorValue);	// ������ ���� �Լ� �̿�, ���� ����
}


////////////////////
/* Ŀ�� ��ġ ���� */
////////////////////
void Console::CursorPosition(int x, int y)
{
	SetConsoleCursorPosition(mHandleConsole, { (short)x, (short)y });	// ������ ���� �Լ� �̿�, Ŀ�� ��ġ ����
}


/////////////////////////
/* �ܼ� â ��ü ���� */
/////////////////////////
void Console::Clear()
{
	mEraser.resize(130, ' ');					// ���찳 �� ����

	CursorPosition(0, 0);						// �ܼ��� ���� ��ܺ���

	for (int count = 0; count < 45; count++)	// �ܼ��� �ุŭ �ݺ�
		printf("%s\n", mEraser.c_str());		// ���� ���ڿ��� ���찳 ���

	CursorPosition(0, 0);
}


/////////////////////////
/* �ܼ� â �Ϻ� ���� */
/////////////////////////
void Console::Clear(int XPosStart, int YPosStart, int width, int height)
{
	mEraser.resize(width, ' ');							// ���찳 �� ����

	for (int count = 0; count < height; count++)		// ���̸�ŭ �ݺ�
	{
		CursorPosition(XPosStart, YPosStart + count);	// ������ ��ǥ���� �Ʒ���
		printf("%s\n", mEraser.c_str());				// ���� ���ڿ��� ���찳 ���
	}
}


//////////////////////////////
/* Draw TXT File to Console */
//////////////////////////////
void Console::Draw(string str_or_file, const char* color, int startX, int startY)
{
	// ���ڰ� "*.txt"
	if (4 <= str_or_file.size() && str_or_file.substr(str_or_file.size() - 4) == ".txt")
	{
		string line;
		fstream file(str_or_file, ios_base::in);	// �ؽ�Ʈ ���� �б�

		for (Color(color); !file.eof(); startY++)	// ���� ����, ������ ������, y��ǥ ������Ʈ
		{
			getline(file, line);			// �ؽ�Ʈ ���� �� �� �б�

			CursorPosition(startX, startY);	// ��ǥ ����
			cout << line;					// ���
		}

		file.close();
	}
	// ���ڰ� "*.txt" �ƴ�
	else
	{
		size_t pos = 0;
		size_t prePos = 0;

		Color(color);

		for (int count = 0; pos < str_or_file.size(); count++)			// �ุŭ �ݺ�
		{
			pos = str_or_file.find('\n', pos + 1);						// ���� ���� ��ġ ����
			CursorPosition(startX, startY + count);						// ��ǥ ������Ʈ
			cout << str_or_file.substr(prePos, pos - prePos) << '\n';	// ���ڿ��� �ڸ� �� ���
			prePos = pos + 1;
		}
	}

	CursorPosition(0, 44);
}


void Console::Draw(string str_or_file, const char* color)
{
	// ���ڰ� "*.txt"
	if (4 <= str_or_file.size() && str_or_file.substr(str_or_file.size() - 4) == ".txt")
	{
		string line;
		fstream file(str_or_file, ios_base::in);	// �ؽ�Ʈ ���� �б�

		for (Color(color); !file.eof();)	// ���� ����, ������ ������, y��ǥ ������Ʈ
		{
			getline(file, line);			// �ؽ�Ʈ ���� �� �� �б�
			cout << line << '\n';			// ���
		}

		file.close();
	}
	// ���ڰ� "*.txt" �ƴ�
	else
	{
		size_t pos = 0;
		size_t prePos = 0;

		Color(color);

		for (int count = 0; pos < str_or_file.size(); count++)			// �ุŭ �ݺ�
		{
			pos = str_or_file.find('\n', pos + 1);						// ���� ���� ��ġ ����
			cout << str_or_file.substr(prePos, pos - prePos) << '\n';	// ���ڿ��� �ڸ� �� ���
			prePos = pos + 1;
		}
	}

	CursorPosition(0, 44);
}


Console* Console::sInstance = nullptr;

Console* Console::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Console;

	return sInstance;
}

void Console::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
