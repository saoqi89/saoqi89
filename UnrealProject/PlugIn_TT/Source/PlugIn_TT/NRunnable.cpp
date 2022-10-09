// Fill out your copyright notice in the Description page of Project Settings.


#include "NRunnable.h"

NRunnable::NRunnable(const FString& ThreadName)
{
	// 获取 FEvent 指针
	ThreadEvent = FPlatformProcess::GetSynchEventFromPool();
	// 创建线程实例
	m_ThreadName = ThreadName;
	ThreadIns = FRunnableThread::Create(this, *m_ThreadName, 0, TPri_Normal);
	m_ThreadID = ThreadIns->GetThreadID();
	UE_LOG(LogTemp, Warning, TEXT("Thread Start! ThreadID = %d"), m_ThreadID);
}

NRunnable::~NRunnable()
{
	if (ThreadEvent)	// 清空 FEvent*
		{
		FPlatformProcess::ReturnSynchEventToPool(ThreadEvent); // delete ThreadEvent;
		ThreadEvent = nullptr;
		}
	if (ThreadIns)		// 清空 FRunnableThread*
		{
		delete ThreadIns;
		ThreadIns = nullptr;
		}
}

void NRunnable::PauseThread()
{
	bPause = true;
	UE_LOG(LogTemp, Warning, TEXT("Thread Pause!"));
}

void NRunnable::WakeUpThread()
{
	bPause = false;
	if (ThreadEvent)
	{
		ThreadEvent->Trigger();    //唤醒线程
	}
	UE_LOG(LogTemp, Warning, TEXT("Thread WarkUp!"));
}

void NRunnable::Suspend(bool bSuspend)
{
	if (ThreadEvent)
	{
		ThreadIns->Suspend(bSuspend);
	}
}

void NRunnable::StopThread()
{
	Stop();
	ThreadIns->WaitForCompletion();   //等待线程执行完毕
}

void NRunnable::ShutDown(bool bShouldWait)
{
	if (ThreadIns)
	{
		ThreadIns->Kill(bShouldWait);
	}
}

bool NRunnable::Init()
{
	return true;
}

uint32 NRunnable::Run()
{
	int32 count = 0;
	FPlatformProcess::Sleep(0.03f);  //延时
	while (bRun)
	{
		if (bPause)
		{
			ThreadEvent->Wait();  //挂起
			if (!bRun)
			{
				return 0;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("ThreadID : %d, Count : %d"), m_ThreadID, count);
		count++;
		FPlatformProcess::Sleep(0.1f);
	}
	return 0;
}

void NRunnable::Stop()
{
	bRun = false;
	bPause = false;
	if (ThreadEvent)
	{
		ThreadEvent->Trigger();  //保证线程不被挂起
	}
	Suspend(false);   
}

void NRunnable::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Thread Exit!"));
}
