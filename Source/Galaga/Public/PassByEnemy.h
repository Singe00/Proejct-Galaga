// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "PassByEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_API APassByEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APassByEnemy();

	// Auto Moving Point Get Select
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPassByMovingPoint")
	bool AutoPassByMovingPoint = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPassByMovingPoint")
	bool TargetIsLeft = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPassByMovingPoint", meta = (EditCondition = "!AutoPassByMovingPoint", ClampMin = "0", ClampMax = "5"))
	int PassByMovingPointIndex = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
