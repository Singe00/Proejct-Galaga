// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "LaserEnemy.generated.h"

UCLASS()
class GALAGA_API ALaserEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
