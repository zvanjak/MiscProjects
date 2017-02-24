// COMPort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class COMPort {
public:
	COMPort(int nCOM);
	~COMPort();

	bool	IsHandleValid();

	bool	SetBaudRate(DWORD dwBaudRate);
	bool	SetParity(BYTE cParity );
	bool	SetByteSize(BYTE ByteSize);
	bool	SetStopBits(BYTE StopBits);

	bool	SetProperties(DWORD dwBaudRate, BYTE ByteSize, BYTE cParity, BYTE StopBits);

	bool	ClearDisplay();

	DWORD	SendString(char achString[]);
	DWORD	SendString(char achString[], int nCharNum);
	
	DWORD	SetBottomLine( char achLine[] );
	DWORD	SetBottomLine( char achLine[], int nCharNum );
	DWORD	SetTopLine( char achLine[] );
	DWORD	SetTopLine( char achLine[], int nCharNum );

private:
	HANDLE	hComPort;
	
	char		achBottomLine[50];
	char		achTopLine[50];

	DWORD		dwError;
	DWORD		dwBaudRate;
	BYTE		ByteSize, cParity, StopBits;
};

COMPort::COMPort( int nCom )
{
	char	strName[5];

	if( nCom == 1 )
		strcpy(strName, "COM1");
	else
		strcpy(strName,"COM2");

	hComPort = CreateFile( strName,
    GENERIC_READ | GENERIC_WRITE,
    0,							// comm devices must be opened w/exclusive-access 
    NULL,						// no security attributes 
    OPEN_EXISTING,	// comm devices must use OPEN_EXISTING 
    0,							// not overlapped I/O 
    NULL						// hTemplate must be NULL for comm devices     
		);

	if (hComPort == INVALID_HANDLE_VALUE) {    
			dwError = GetLastError();						// handle error 
	}
	else {
		BOOL	fSuccess;
		DCB		dcb;

		fSuccess = GetCommState(hComPort, &dcb);
		if (!fSuccess) {    
			// Handle the error. 
		}			
		else {
			dcb.BaudRate = 9600;
			dcb.ByteSize = 8;
			dcb.Parity = NOPARITY;
			dcb.StopBits = ONESTOPBIT;
		
			fSuccess = SetCommState(hComPort, &dcb);
			if (!fSuccess) {
				;
			}

			this->ClearDisplay();
		}
	}
}

COMPort::~COMPort()
{
	CloseHandle(hComPort);
}

bool	COMPort::IsHandleValid() 
{
	if( hComPort == INVALID_HANDLE_VALUE ) {
		dwError = GetLastError();						// handle error 
		return false;
	}
	else
		return true;
}

bool	COMPort::SetProperties(DWORD dwBaudRate, BYTE ByteSize, BYTE cParity, BYTE StopBits)
{
	BOOL	fSuccess;
	DCB		dcb;

	fSuccess = GetCommState(hComPort, &dcb);
			
	if (!fSuccess) {    
		// Handle the error. 
	}			
	else {
		dcb.BaudRate = dwBaudRate;
		dcb.ByteSize = ByteSize;
		dcb.Parity = cParity;
		dcb.StopBits = StopBits;
	
		fSuccess = SetCommState(hComPort, &dcb);
	
		if (!fSuccess) {
			// Handle the error. 
			puts("Greska");
		}
	}
	return true;
}

bool	COMPort::ClearDisplay()
{
	char	strClear[]="\x1b@\f\x1bQ";

	SendString(strClear);

	return true;
}

DWORD	COMPort::SendString(char achString[])
{
	DWORD		dwWritten;

	WriteFile(hComPort, achString, strlen(achString), &dwWritten, NULL );
	
	return dwWritten;
}

DWORD	COMPort::SendString(char achString[], int nCharNum)
{
	DWORD		dwWritten;

	WriteFile(hComPort, achString, nCharNum, &dwWritten, NULL );
	
	return dwWritten;
}

DWORD COMPort::SetBottomLine( char achLine[] )
{
	char	*buff;

	strcpy(achBottomLine, achLine);

	buff = new char[strlen(achLine)+20];
	sprintf(buff, "\x1f\x24\x1\x2\x18%s", achLine );

	DWORD dwWritten = SendString(buff);
	delete []buff;

	return dwWritten;
}

DWORD COMPort::SetBottomLine( char achLine[], int nCharNum )
{
	char	*buff;

	buff = new char[strlen(achLine)+20];
	sprintf(buff, "\x1f\x24\x1\x2\x18%s", achLine );
	buff[nCharNum+5] = 0;

	strcpy(achBottomLine, buff+5);

	DWORD dwWritten = SendString(buff);
	delete []buff;

	return dwWritten;
}

DWORD COMPort::SetTopLine( char achLine[] )
{
	char	*buff;

	strcpy(achTopLine, achLine);

	buff = new char[strlen(achLine)+20];
	sprintf(buff, "\x1f\x24\x1\x1\x18%s", achLine );

	DWORD	dwWritten = SendString(buff);
	delete []buff;

	return dwWritten;
}

DWORD COMPort::SetTopLine( char achLine[], int nCharNum )
{
	char	*buff;

	buff = new char[strlen(achLine)+20];
	sprintf(buff, "\x1f\x24\x1\x1\x18%s", achLine );
	buff[nCharNum+5] = 0;

	strcpy(achTopLine, buff+5);

	DWORD	dwWritten = SendString(buff);
	delete []buff;


	return dwWritten;
}

int main(int argc, char* argv[])
{
	COMPort	hCom(2);

	if( hCom.IsHandleValid() == TRUE )
	{
//		hCom.ClearDisplay();

		char		str[100] = "OOP     OOP     OOP      OOP       OOP      OOP       OOP     OOP      OOP";
		char		str2[100] = "   C++     C++      C++       C++      C++       C++     C++      C++";

		while(1) {
			for( int i=0; i<36; i++ )
			{
				hCom.SetTopLine(&str[i], 20);
				hCom.SetBottomLine(&str2[i], 20);
				Sleep(200);
			}
		}
	}
	else
		puts("Greska!!!");

	return 0;
}
