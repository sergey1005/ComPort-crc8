// VirtualPort.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include<fstream>
#include<string>
#include<stdint.h>
#include<math.h>

using namespace std;

uint8_t REG1;
uint8_t  REGX;
int  REGY;
int  REGZ;
int REGCRC8;
float REG12;
int regXm;
int regYm;
int regZm;
int regX;
int regX1;
int regY;
int regZ;
int regXn;
int regYn;
int regZn;
int dregX;
int dregY;
int dregZ;
int d;
uint8_t setnull = 0;
uint8_t factoryset = 0;
uint8_t security =  0;
uint8_t influence = 0;
HANDLE hSerial;//Обработчик порта


void ReadCOM();

int main(int argc, CHAR* argv[])
{
	setlocale(LC_ALL, "Ru");
	//Объявляем номер СОМ пота
	LPCTSTR sPortName = L"COM1";

	//Открываем  ком порт для записи / чтения:
	hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//Проверяем работоспособность :
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			cout << "serial port does not exist.\n" << endl;
		}
		cout << "some other error occurred.\n" << endl;
	}

	//Теперь нужно настроить параметры соединения :


	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		cout << "getting state error\n" << endl;
	}
	dcbSerialParams.BaudRate = CBR_1200;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		cout << "error setting serial port state\n" << endl;
	}

	//Теперь объявим строку, которую будем передавать и переменные необходимые для этого :


//char data[] = "Hello from C++";  // строка для передачи

	//DWORD dwSize = sizeof(data);   // размер этой строки
///////////////////////////////////////////////
	ofstream fout;
	fout.open("Myfile.txt");
	if (!fout.is_open())
		cout << "File isn't open"<<endl;
	else 
////////////////////////////////////////////
	
	//cout << "Введите число"<<endl;
//	char a[]="222";
	//cin >> (a);
	//for (int i = 0; i < dwSize; i++) {
	//	fout << data[i];
	//}
	
//	fout << a;
//	cout << a;
	//cout << data[15];

		//DWORD dwBytesWritten;    // тут будет количество собственно переданных байт

		//Посылаем строку.Напомню, что пример простейший, поэтому никаких особо проверок я не делаю :	
	//	BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
		//BOOL iRet1 = WriteFile(hSerial,a, 70, &dwBytesWritten , NULL );

		//Также я решил вывести для контроля размер строки и количество отосланных байт :
		//cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;

		//В конце программы делаем бесконечный цикл чтения данных :
		//fout.close();
	//	fstream fin;
	//	fin.open("Myfile.txt");
	//	if (fin.is_open())
	//		cout << "Файл открыт"<<endl;
	//	else
	//		cout << "Ошибка открытия файла"<<endl;
	//	char ch;
	//	while (fin.get(ch))
	//		cout << ch,"/n";
			while (1)
			{
				ReadCOM();
			
			}

		//	fin.close();
		return 0;
}

///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////Функция чтения :
void ReadCOM()
{


	DWORD iSize;
	unsigned int sReceivedChar;
	while (true)

	{

		sReceivedChar = 0x00;
	//a1:

		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
		
		
			REGX = 0;
             REGX = sReceivedChar;
			 //cout <<"REGX = "<< REGX << endl;
			 uint8_t set = 0;
			 uint8_t mask = 0;
			 uint8_t i = 0;
			 string result = "";
			 string bit = "";
			 while (i < 8) { 
				  mask = 1 << i;
				 set = REGX & mask;
				 (set == mask) ? bit = "1" : bit = "0";
				 result = bit + result;
				 if (i == 4 && set == mask){
					 cout << "Воздействие" << endl;
				 }
				 i++;
			 }

			 cout <<"REGX = " << result<<endl;
				

			 
			
		Sleep(1100);
	}
}

	
 