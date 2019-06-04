// VirtualPort.cpp: определяет точку входа для консольного приложения.
//


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
int REGXm;
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
	//Объявление номера СОМ пота
	LPCTSTR sPortName = L"COM1";

	//Открытие  ком порта для записи / чтения:
	hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	//Проверка работоспособности :
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			cout << "serial port does not exist.\n" << endl;
		}
		cout << "some other error occurred.\n" << endl;
	}

	// настройка параметров соединения :


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

	
	ofstream fout;
	fout.open("Myfile.txt");
	if (!fout.is_open())
		cout << "File isn't open"<<endl;
	else 

			while (1)
			{
				ReadCOM();
			
			}

		//	fin.close();
		return 0;
}


//////////////////////////////////////////////////////////////////////Функция чтения :
void ReadCOM()
{


	DWORD iSize;
	unsigned int sReceivedChar;
	while (true)

	{

		sReceivedChar = 0x00;
	a1:

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
					 cout << "Саботаж" << endl;
				 }

				 i++;
			 }
			
				 cout << "CHIPS = " << result << endl;
			

			
			//Sleep(1100);
			 goto a1;
		
		
	}
}

	
 