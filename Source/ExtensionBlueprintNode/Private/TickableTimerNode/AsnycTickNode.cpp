// Fill out your copyright notice in the Description page of Project Settings.


#include "TickableTimerNode/AsnycTickNode.h"

UAsnycTickNode::UAsnycTickNode(const FObjectInitializer& Initializer) :
	Super(Initializer), FTickableGameObject()
{
	TickInfo.Timer = this;
	bCanTickInPaused = false;
}

UAsnycTickNode* UAsnycTickNode::StartupTickableTimer(UObject* WorldContextObject, float Time, int LoopCount, bool CanTickInPaused)
{
	// 创建异步节点
	UAsnycTickNode* Node = NewObject<UAsnycTickNode>(WorldContextObject);

	// 防止GC自动回收, 同时GC自动检测回收条件
	Node->RegisterWithGameInstance(WorldContextObject);
	FCoreUObjectDelegates::GetPreGarbageCollectDelegate().AddUObject(Node, &UAsnycTickNode::PreGarbageCollect);

	Node->TickInfo.Init(Time, LoopCount);
	Node->bCanTickInPaused = CanTickInPaused;
	
	return Node;
}

bool UAsnycTickNode::IsTickable() const
{
	return TickInfo.State == ETimerState::Ticking;
}

bool UAsnycTickNode::IsTickableWhenPaused() const
{
	return bCanTickInPaused;
}

TStatId UAsnycTickNode::GetStatId() const
{
	return Super::GetStatID();
}

UWorld* UAsnycTickNode::GetTickableGameObjectWorld() const
{
	return GetWorld();
}

void UAsnycTickNode::Tick(float DeltaTime)
{
	TickInfo.AddDeltaTime(DeltaTime);
	OnTicked.Broadcast(TickInfo);
	
	if (TickInfo.CheckEnd()) OnStoped.Broadcast(TickInfo);
}

void UAsnycTickNode::Activate()
{
	OnTicked.Broadcast(TickInfo);
}

void UAsnycTickNode::End_Implementation()
{
	if (TickInfo.State == ETimerState::Break || TickInfo.State == ETimerState::Finished) return;
	TickInfo.State = ETimerState::Break;
	OnStoped.Broadcast(TickInfo);
}

void UAsnycTickNode::Pause_Implementation()
{
	if (TickInfo.State == ETimerState::Break || TickInfo.State == ETimerState::Finished) return;
	TickInfo.State = ETimerState::Paused;
	OnStoped.Broadcast(TickInfo);
}

void UAsnycTickNode::Continue_Implementation()
{
	if (TickInfo.State == ETimerState::Break || TickInfo.State == ETimerState::Finished) return;
	TickInfo.State = ETimerState::Ticking;
}

void UAsnycTickNode::PreGarbageCollect()
{
	if (TickInfo.State == ETimerState::Break || TickInfo.State == ETimerState::Finished)
		SetReadyToDestroy();
}
