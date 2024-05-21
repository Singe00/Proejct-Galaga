// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "WaveEnemy.generated.h"

UCLASS()
class GALAGA_API AWaveEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
