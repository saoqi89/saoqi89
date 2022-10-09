// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PLUGIN_TT_API NRunnable : public FRunnable
{
public:
	NRunnable(const FString& ThreadName);
	~NRunnable();

public:
	void PauseThread();				// 线程挂起 方法一
	void WakeUpThread();			// 线程唤醒 方法一
	void Suspend(bool bSuspend);	// 线程挂起/唤醒 方法二
	void StopThread();				// 停止线程，一般用该方法
	void ShutDown(bool bShouldWait);// 停止线程，bShouldWait true的时候可强制 kill 线程

private:
	FString m_ThreadName;
	int32 m_ThreadID;
	bool bRun = true;				// 线程循环标志
	bool bPause = false;			//线程挂起标志
	FRunnableThread* ThreadIns;		// 线程实例
	FEvent* ThreadEvent;			//FEvent指针,挂起/激活线程, 在各自的线程内使用
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
};
