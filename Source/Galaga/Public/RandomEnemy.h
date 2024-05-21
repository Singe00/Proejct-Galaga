// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "RandomEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_API ARandomEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARandomEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetRandomRange")
	bool SetRandomRange = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetRandomRange", meta = (EditCondition = "SetRandomRange", ClampMin = "4", ClampMax = "32"))
	int RadomMovingPointRange = 4;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
