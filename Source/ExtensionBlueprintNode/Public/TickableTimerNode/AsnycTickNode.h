// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerAction.h"
#include "Tickable.h"
#include "Engine/World.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "TickableTimerNode/TickableTimerInfo.h"

#include "AsnycTickNode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickableTimerDelegate, FTickableTimerInfo, Result);

UCLASS(meta=(BlueprintThreadSafe))
class EXTENSIONBLUEPRINTNODE_API UAsnycTickNode : public UBlueprintAsyncActionBase, public FTickableGameObject, public ITimerAction
{
	GENERATED_BODY()

public:
	/**
	 * @brief 每帧回调
	 */
	UPROPERTY(BlueprintAssignable)
	FTickableTimerDelegate OnTicked;

	/**
	 * @brief 完成回调
	 */
	UPROPERTY(BlueprintAssignable)
	FTickableTimerDelegate OnStoped;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly ="true", WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", NotBlueprintThreadSafe="false"))
	static UAsnycTickNode* StartupTickableTimer(UObject* WorldContextObject, float Time, int LoopCount = 1, bool CanTickInPaused = false);

public:
	UAsnycTickNode(const FObjectInitializer& Initializer);
	
	virtual bool IsTickable() const override;
	
	virtual bool IsTickableWhenPaused() const override;
	
	virtual TStatId GetStatId() const override;
	
	virtual UWorld* GetTickableGameObjectWorld() const override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Activate() override;

	virtual void End_Implementation() override;

	virtual void Pause_Implementation() override;

	virtual void Continue_Implementation() override;

private:
	FTickableTimerInfo TickInfo;
	bool bCanTickInPaused;

	void PreGarbageCollect();
};
