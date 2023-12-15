// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMath.h"
#include "TickableTimerInfo.generated.h"

UENUM(BlueprintType)
enum class ETimerState : uint8
{
	Ticking     UMETA(ToolTip="运行中"),
	Finished    UMETA(ToolTip="完成计时"),
	Break	    UMETA(ToolTip="中断计时"),
	Paused      UMETA(ToolTip="暂停计时")
};

USTRUCT(BlueprintType)
struct FTickableTimerInfo
{
	GENERATED_BODY()

public:
	/**
	 * @brief 计时器本体
	 */
	UPROPERTY(BlueprintReadOnly)
	UObject* Timer;
	
	/**
	 * @brief 当前Tick时间
	 */
	UPROPERTY(BlueprintReadOnly)
	float DeltaTime = 0;

	/**
	 * @brief 计时器进度
	 */
	UPROPERTY(BlueprintReadOnly)
	float Program = 0;

	/**
	 * @brief 停止的类型模式
	 */
	UPROPERTY(BlueprintReadOnly)
	ETimerState State = ETimerState::Ticking;

	/**
	 * @brief 剩余循环次数
	 */
	UPROPERTY(BlueprintReadOnly)
	int RemainLoop = 1;

public:
	FTickableTimerInfo();
	void Init(float Time, int bLoop);

	void AddDeltaTime(float DeltaSecond);

	bool CheckEnd();

public:
	float EndTime = 0;
	float CurrentTime = 0;
};
