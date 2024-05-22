// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayer.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAGA_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBaseComponent()
	{
		PrimaryComponentTick.bCanEverTick = false;;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// 소유자
	UPROPERTY()
	AMyPlayer* me;

	// 가상함수 생성
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {};
};
