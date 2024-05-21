// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"

UPlayerMove::UPlayerMove()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move(DeltaTime);
}

void UPlayerMove::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &UPlayerMove::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &UPlayerMove::Vertical);

	PlayerInputComponent->BindAction(TEXT("Speed"), IE_Pressed, this, &UPlayerMove::Slow);
	PlayerInputComponent->BindAction(TEXT("Speed"), IE_Released, this, &UPlayerMove::Fast);
}

void UPlayerMove::Horizontal(float value)
{
	Direction.X = value;
}

void UPlayerMove::Vertical(float value)
{
	Direction.Y = value;
}

void UPlayerMove::Move(float DeltaTime)
{
	FVector P0 = me->GetActorLocation();
	FVector vt = DeltaTime * MoveSpeed * Direction;

	FVector P = P0 + vt;

	me->SetActorLocation(P, true);
	Direction = FVector::ZeroVector;
}

void UPlayerMove::Slow()
{
	SetMoveSpeed(800);
}

void UPlayerMove::Fast()
{
	SetMoveSpeed(1500);
}