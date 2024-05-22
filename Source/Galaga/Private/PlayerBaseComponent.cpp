// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseComponent.h"


// Called when the game starts
void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// 소유자 초기화
	me = Cast<AMyPlayer>(GetOwner());
}

