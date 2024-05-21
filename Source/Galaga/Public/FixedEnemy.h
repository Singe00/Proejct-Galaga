// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "FixedEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_API AFixedEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFixedEnemy();


	// Auto Moving Point Get Select
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoFixedMovingPoint")
	bool AutoFixedMovingPoint = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoFixedMovingPoint", meta = (EditCondition = "!AutoFixedMovingPoint", ClampMin = "0", ClampMax = "31"))
	int FixedMovingPointIndex = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
