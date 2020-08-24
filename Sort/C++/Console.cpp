#include "console.h"


///////////////////////////////
/* 색상 문자열을 정수로 변환 */
///////////////////////////////
int Console::ColorNameToNumber(const string& colorName) const
{
	if (colorName == "default")
		return -1;

	if (colorName == "random")						// 랜덤이 입력되면
	{
		int colorSet[5] = { 12, 10, 3, 13, 14 };	// 적절한 색상 중에서
		return colorSet[rand() % 5];				// 무작위로 선택
	}
	else if (colorName == "red")	return 12;		// 빨강
	else if (colorName == "green")	return 10;		// 초록
	else if (colorName == "blue")	return 3;		// 파랑
	else if (colorName == "purple")	return 13;		// 보라
	else if (colorName == "yellow")	return 14;		// 노랑
	else if (colorName == "white")	return 15;		// 하양
	else if (colorName == "black")	return 0;		// 검정

	return -1;
}


////////////////////
/* 텍스트 색 지정 */
////////////////////
void Console::Color(const string& foreground, const string& background)
{
	int colorForeground = ColorNameToNumber(foreground);	// 글자 색상 문자열을 정수로 변환
	int colorBackground = ColorNameToNumber(background);	// 배경 색상 문자열을 정수로 변환
	int colorValue;

	if (colorForeground == -1) colorForeground = 7;			// 기본 값 7
	if (colorBackground == -1) colorBackground = 0;			// 기본 값 0
	colorValue = (colorBackground * 16) + colorForeground;	// 정수로 변환한 값을 적절하게 대입

	SetConsoleTextAttribute(mHandleConsole, colorValue);	// 윈도우 제공 함수 이용, 색상 변경
}


////////////////////
/* 커서 위치 지정 */
////////////////////
void Console::CursorPosition(int x, int y)
{
	SetConsoleCursorPosition(mHandleConsole, { (short)x, (short)y });	// 윈도우 제공 함수 이용, 커서 위치 변경
}


/////////////////////////
/* 콘솔 창 전체 비우기 */
/////////////////////////
void Console::Clear()
{
	mEraser.resize(130, ' ');					// 지우개 폭 설정

	CursorPosition(0, 0);						// 콘솔의 좌측 상단부터

	for (int count = 0; count < 45; count++)	// 콘솔의 행만큼 반복
		printf("%s\n", mEraser.c_str());		// 공백 문자열인 지우개 출력

	CursorPosition(0, 0);
}


/////////////////////////
/* 콘솔 창 일부 비우기 */
/////////////////////////
void Console::Clear(int XPosStart, int YPosStart, int width, int height)
{
	mEraser.resize(width, ' ');							// 지우개 폭 설정

	for (int count = 0; count < height; count++)		// 높이만큼 반복
	{
		CursorPosition(XPosStart, YPosStart + count);	// 설정한 좌표부터 아래로
		printf("%s\n", mEraser.c_str());				// 공백 문자열인 지우개 출력
	}
}


//////////////////////////////
/* Draw TXT File to Console */
//////////////////////////////
void Console::Draw(string str_or_file, const char* color, int startX, int startY)
{
	// 인자가 "*.txt"
	if (4 <= str_or_file.size() && str_or_file.substr(str_or_file.size() - 4) == ".txt")
	{
		string line;
		fstream file(str_or_file, ios_base::in);	// 텍스트 파일 읽기

		for (Color(color); !file.eof(); startY++)	// 색상 변경, 파일의 끝까지, y좌표 업데이트
		{
			getline(file, line);			// 텍스트 파일 한 줄 읽기

			CursorPosition(startX, startY);	// 좌표 설정
			cout << line;					// 출력
		}

		file.close();
	}
	// 인자가 "*.txt" 아님
	else
	{
		size_t pos = 0;
		size_t prePos = 0;

		Color(color);

		for (int count = 0; pos < str_or_file.size(); count++)			// 행만큼 반복
		{
			pos = str_or_file.find('\n', pos + 1);						// 개행 문자 위치 저장
			CursorPosition(startX, startY + count);						// 좌표 업데이트
			cout << str_or_file.substr(prePos, pos - prePos) << '\n';	// 문자열을 자른 후 출력
			prePos = pos + 1;
		}
	}

	CursorPosition(0, 44);
}


void Console::Draw(string str_or_file, const char* color)
{
	// 인자가 "*.txt"
	if (4 <= str_or_file.size() && str_or_file.substr(str_or_file.size() - 4) == ".txt")
	{
		string line;
		fstream file(str_or_file, ios_base::in);	// 텍스트 파일 읽기

		for (Color(color); !file.eof();)	// 색상 변경, 파일의 끝까지, y좌표 업데이트
		{
			getline(file, line);			// 텍스트 파일 한 줄 읽기
			cout << line << '\n';			// 출력
		}

		file.close();
	}
	// 인자가 "*.txt" 아님
	else
	{
		size_t pos = 0;
		size_t prePos = 0;

		Color(color);

		for (int count = 0; pos < str_or_file.size(); count++)			// 행만큼 반복
		{
			pos = str_or_file.find('\n', pos + 1);						// 개행 문자 위치 저장
			cout << str_or_file.substr(prePos, pos - prePos) << '\n';	// 문자열을 자른 후 출력
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
