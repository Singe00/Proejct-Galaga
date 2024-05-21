// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "PatrolEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_API APatrolEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APatrolEnemy();


	// Auto Moving Point Get Select
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPatrolMovingPoint")
	bool AutoPatrolMovingPoint = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPatrolMovingPoint", meta = (EditCondition = "!AutoPatrolMovingPoint", ClampMin = "0", ClampMax = "20"))
	float PatrolDelayTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPatrolMovingPoint", meta = (EditCondition = "!AutoPatrolMovingPoint", ClampMin = "0", ClampMax = "20"))
	int FirstPatrolMovingPointIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPatrolMovingPoint", meta = (EditCondition = "!AutoPatrolMovingPoint", ClampMin = "0", ClampMax = "20"))
	int SecondPatrolMovingPointIndex = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
