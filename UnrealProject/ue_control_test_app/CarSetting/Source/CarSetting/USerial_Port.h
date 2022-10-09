#pragma once

#include "CoreTypes.h"
#include "USerial_Port.generated.h"

// Forward declaration
typedef struct _OVERLAPPED OVERLAPPED;

UCLASS()
class CARSETTING_API USerial_Port : public UObject
{
	GENERATED_BODY()

public:
	USerial_Port();
	~USerial_Port();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Serial Port"))
	static USerial_Port* OpenComPort(bool &bOpened, int32 Port = 1, int32 BaudRate = 9600);
	
	UFUNCTION(BlueprintCallable, meta=(DisplayName = "Open Port"))
	bool Open(int32 Port = 2, int32 BaudRate = 9600);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Close Port"))
	void Close();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Read String"))
	FString ReadString(bool &bSuccess);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Read Line"))
	FString Readln(bool &bSuccess);
	
	FString ReadStringUntil(bool &bSuccess, uint8 Terminator);
	
	UFUNCTION(BlueprintCallable,  meta = (DisplayName = "Log"))
	static void Log(FString ReadMsg, FString Order);

	
protected:
	void* m_hIDComDev;

	// These are pointers to be able to use OVERLAPPED with forward declaration
	OVERLAPPED* m_OverlappedRead;

	int32 m_Port;
	int32 m_Baud;

};