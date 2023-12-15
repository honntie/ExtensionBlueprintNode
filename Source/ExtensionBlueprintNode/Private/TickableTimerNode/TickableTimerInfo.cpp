// Fill out your copyright notice in the Description page of Project Settings.


#include "TickableTimerNode/TickableTimerInfo.h"

FTickableTimerInfo::FTickableTimerInfo()
{
	DeltaTime = 0;
	Program = 0;
	State = ETimerState::Ticking;
	RemainLoop = 1;
	EndTime = 0;
	CurrentTime = 0;
}

void FTickableTimerInfo::Init(float Time, int bLoop)
{
	EndTime = Time;
	RemainLoop = bLoop - 1;
	DeltaTime = 0;
	Program = 0;
	State = ETimerState::Ticking;
	CurrentTime = 0;
}

void FTickableTimerInfo::AddDeltaTime(float DeltaSecond)
{
	DeltaTime = DeltaSecond;
	CurrentTime += DeltaTime;
	Program = FMath::Clamp<float>(CurrentTime / EndTime, 0, 1);
}

bool FTickableTimerInfo::CheckEnd()
{
	if (Program >= 1)
	{
		if (RemainLoop == 0) State = ETimerState::Finished;
		else if (RemainLoop > 0) RemainLoop--; 
		CurrentTime = 0;
		return true;
	}
	return false;
}
