// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
	UPlayerMove();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

private: // Player Move
	UPROPERTY(VisibleAnywhere, Category = PlayerMovement)
	float MoveSpeed = 1500;

	UPROPERTY(VisibleAnywhere, Category = PlayerMovement)
	FVector Direction;

	void Move(float DeltaTime);

	void Slow();
	void Fast();

	void Horizontal(float value);
	void Vertical(float value);

public:
	void SetMoveSpeed(float newMoveSpeed) { this->MoveSpeed = newMoveSpeed; }
};
