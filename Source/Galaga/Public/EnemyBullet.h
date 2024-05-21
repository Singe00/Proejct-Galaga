// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBullet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyPooledBulletDespawn, AEnemyBullet* ,PoolActor);

UCLASS()
class GALAGA_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: // Components
	UPROPERTY(VisibleAnywhere, Category = BulletBody)
	class USphereComponent* BulletBodyCollision;

	UPROPERTY(VisibleAnywhere, Category = BulletBody)
	class UStaticMeshComponent* BulletBody;

private: // BulletStat
	UPROPERTY(EditAnywhere, Category = BulletStat)
	float BulletSpeed = 2000;

	UPROPERTY(VisibleAnywhere, Category = BulletStat)
	FVector BulletSize = FVector(1, 0.5f, 0.25f);

private: // Function
	void BulletForwardMove(float DeltaTime);

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:
	FOnEnemyPooledBulletDespawn OnEnemyPooledBulletDespawn;

	UFUNCTION()
	void Deactivate();

	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);

	bool IsActive();
	int GetPoolIndex();

protected:
	bool Active;
	float LifeSpan = 6.0f;
	int PoolIndex;

	FTimerHandle LifeSpanTimer;

};
