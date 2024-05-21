// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBullet.h"
#include "EnemyBulletPool.generated.h"

UCLASS()
class GALAGA_API AEnemyBulletPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBulletPool();

	UFUNCTION()
	AEnemyBullet* SpawnPooledObject(FVector newLocation, FRotator newRotation);

	UPROPERTY(EditAnywhere,Category="Object Pool")
	TSubclassOf<class AEnemyBullet> PooledObjectSubclass;

	UPROPERTY(EditAnywhere,Category="Object Pool")
	int PoolSize = 200;

	UPROPERTY(EditAnywhere,Category="Object Pool")
	float PooledObjectLifeSpan = 6.0f;

	UFUNCTION()
	void OnEnemyPooledBulletDespawn(AEnemyBullet* PoolActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	TArray<AEnemyBullet*> ObjectPool;
	TArray<int> SpawnedPoolIndexes;

public:
	void DeactiveAllBullets();
};
