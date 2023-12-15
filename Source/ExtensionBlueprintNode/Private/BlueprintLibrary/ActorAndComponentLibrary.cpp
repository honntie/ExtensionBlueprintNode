// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibrary/ActorAndComponentLibrary.h"


UActorComponent* UActorAndComponentLibrary::GetComponentByName(const AActor* Target, TSubclassOf<UActorComponent> ComponentType, FString Name)
{
	for (UActorComponent* Component : Target->K2_GetComponentsByClass(ComponentType))
	{
		if (Component->GetName() == Name) return Component;
	}
	return nullptr;
}

UActorComponent* UActorAndComponentLibrary::GetComponentByClassOnOwner(const UActorComponent* Target,
	TSubclassOf<UActorComponent> ComponentType)
{
	return Target->GetOwner()->GetComponentByClass(ComponentType);
}

TArray<UActorComponent*> UActorAndComponentLibrary::GetComponentsByClassOnOwner(const UActorComponent* Target,
	TSubclassOf<UActorComponent> ComponentType)
{
	return Target->GetOwner()->K2_GetComponentsByClass(ComponentType);
}

TArray<UActorComponent*> UActorAndComponentLibrary::GetComponentsByInterfaceOnOwner(const UActorComponent* Target,
	TSubclassOf<UInterface> InterfaceType)
{
	return Target->GetOwner()->GetComponentsByInterface(InterfaceType);
}

TArray<UActorComponent*> UActorAndComponentLibrary::GetComponentsByTagOnOwner(const UActorComponent* Target,
	TSubclassOf<UActorComponent> ComponentType, FName Tag)
{
	return Target->GetOwner()->GetComponentsByTag(ComponentType, Tag);
}

UActorComponent* UActorAndComponentLibrary::GetComponentsByNameOnOwner(const UActorComponent* Target,
	TSubclassOf<UActorComponent> ComponentType, FString Name)
{
	return GetComponentByName(Target->GetOwner(), ComponentType, Name);
}
