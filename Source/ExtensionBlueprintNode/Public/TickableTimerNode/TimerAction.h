// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TimerAction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UTimerAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EXTENSIONBLUEPRINTNODE_API ITimerAction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void End();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pause();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Continue();
};
