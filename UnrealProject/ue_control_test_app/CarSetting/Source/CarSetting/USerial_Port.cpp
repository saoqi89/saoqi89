//Based off the "Arduino and C++ (for Windows)" code found at: http://playground.arduino.cc/Interfacing/CPPWindows

#include "USerial_Port.h"
#include <string>
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinWindows.h"

#define BOOL2bool(B) B == 0 ? false : true

USerial_Port* USerial_Port::OpenComPort(bool &bOpened, int32 Port, int32 BaudRate)
{
	USerial_Port* Serial = NewObject<USerial_Port>();
	bOpened = Serial->Open(Port, BaudRate);
	return Serial;
}

USerial_Port::USerial_Port()
	:m_hIDComDev(nullptr)
	, m_OverlappedRead(nullptr)
	, m_Port(-1)
	, m_Baud(-1)
{
	// Allocate the OVERLAPPED structs
	m_OverlappedRead = new OVERLAPPED();

	FMemory::Memset(m_OverlappedRead, 0, sizeof(OVERLAPPED));
}

USerial_Port::~USerial_Port()
{
	Close();

	// Delete allocated OVERLAPPED structs
	delete m_OverlappedRead;
}

bool USerial_Port::Open(int32 nPort, int32 nBaud)
{
	if (nPort < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid port number: %d"), nPort);
		return false;
	}
	if (m_hIDComDev)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to use opened Serial instance to open a new one. "
				"Current open instance port: %d | Port tried: %d"), m_Port, nPort);
		return false;
	}

	FString szPort;
	if (nPort < 10)
		szPort = FString::Printf(TEXT("COM%d"), nPort);
	else
		szPort = FString::Printf(TEXT("\\\\.\\COM%d"), nPort);
	DCB dcb;

	m_hIDComDev = CreateFile(*szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (m_hIDComDev == NULL)
	{
		unsigned long dwError = GetLastError();
		UE_LOG(LogTemp, Error, TEXT("Failed to open port COM%d (%s). Error: %08X"), nPort, *szPort, dwError);
		return false;
	}

	FMemory::Memset(m_OverlappedRead, 0, sizeof(OVERLAPPED));

	COMMTIMEOUTS CommTimeOuts;
	//CommTimeOuts.ReadIntervalTimeout = 10;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 10;
	SetCommTimeouts(m_hIDComDev, &CommTimeOuts);

	m_OverlappedRead->hEvent = CreateEvent(NULL, true, false, NULL);

	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hIDComDev, &dcb);
	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;

	if (!SetCommState(m_hIDComDev, &dcb) ||
		!SetupComm(m_hIDComDev, 10000, 10000) ||
		m_OverlappedRead->hEvent == NULL )
	{
		unsigned long dwError = GetLastError();
		if (m_OverlappedRead->hEvent != NULL) CloseHandle(m_OverlappedRead->hEvent);
		CloseHandle(m_hIDComDev);
		m_hIDComDev = NULL;
		UE_LOG(LogTemp, Error, TEXT("Failed to setup port COM%d. Error: %08X"), nPort, dwError);
		return false;
	}

	//FPlatformProcess::Sleep(0.05f);
	AddToRoot();
	m_Port = nPort;
	m_Baud = nBaud;
	return true;
}

void USerial_Port::Close()
{
	if (!m_hIDComDev) return;

	if (m_OverlappedRead->hEvent != NULL) CloseHandle(m_OverlappedRead->hEvent);
	CloseHandle(m_hIDComDev);
	m_hIDComDev = NULL;

	RemoveFromRoot();
}

FString USerial_Port::ReadString(bool &bSuccess)
{
	return ReadStringUntil(bSuccess, '\0');
}

FString USerial_Port::Readln(bool &bSuccess)
{
	return ReadStringUntil(bSuccess, '\n');
}

FString USerial_Port::ReadStringUntil(bool &bSuccess, uint8 Terminator)
{
	bSuccess = false;
	if (!m_hIDComDev) return TEXT("");

	TArray<uint8> Chars;
	uint8 Byte = 0x0;
	bool bReadStatus;
	unsigned long dwBytesRead, dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);
	if (!ComStat.cbInQue) return TEXT("");

	do {
		bReadStatus = BOOL2bool(ReadFile(
			m_hIDComDev,
			&Byte,
			1,
			&dwBytesRead,
			m_OverlappedRead));

		if (!bReadStatus)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				WaitForSingleObject(m_OverlappedRead->hEvent, 2000);
			}
			else
			{
				Chars.Add(0x0);
				break;
			}
		}

		if (Byte == Terminator || dwBytesRead == 0)
		{
			if (Chars.Num() > 0 && Terminator == '\n' && Chars.Top() == '\r') Chars.Pop(false);

			Chars.Add(0x0);
			break;
		}
		else Chars.Add(Byte);

	} while (Byte != 0x0 && Byte != Terminator);

	bSuccess = true;
	auto asd = Chars.GetData();  
	char* asda = (ANSICHAR*)Chars.GetData();
	TStringConversion<FUTF8ToTCHAR_Convert> Convert = FUTF8ToTCHAR((ANSICHAR*)Chars.GetData());
	int srclen = Convert.Length();
	FString asad = Convert.Get();

	/*unsigned char data[3];
	char *tmpStr = new char[strlen(asda)];
	strcpy(tmpStr, asda);
	char* res = strtok(tmpStr, " ");
	int tmpXor = 0x00;
	int i = 0;
	while (res != NULL) {
		int r = strtoull(res, NULL, 16);
		data[i] = r;
		tmpXor ^= r;
		//std::cout << res << "  " << r << " outData:" << ((int)outData[i]) << std::endl;
		i++;
        
		res = strtok(NULL, " ");
	}*/
	
	
	return FString(Convert.Get());
}


void USerial_Port::Log(FString ReadMsg, FString Order)
{
	//[ReadMsg]F1 01 [Order]Open Windows 

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("[ReadMsg]%s [Order]%s "), *ReadMsg, *Order));
	UE_LOG(LogTemp, Warning, TEXT("[ReadMsg]%s [Order]%s"), *ReadMsg, *Order);
	
}



