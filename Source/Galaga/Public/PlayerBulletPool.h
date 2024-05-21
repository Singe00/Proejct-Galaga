// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBullet.h"
#include "PlayerBulletPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAGA_API UPlayerBulletPool : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UPlayerBulletPool();

	UFUNCTION()
	APlayerBullet* SpawnPlayerPooledBullet();

	UPROPERTY(EditDefaultsOnly, Category = ObjectPool)
	TSubclassOf<class APlayerBullet> PooledObjectSubclass;
	UPROPERTY(EditAnywhere, Category = ObjectPool)
	int PoolSize = 50;
	UPROPERTY(EditAnywhere, Category = ObjectPool)
	float PooledObjectLifeSpan = 1.0f;
	
	UFUNCTION()
	void OnPlayerPooledBulletDespawn(APlayerBullet* PoolActor);

protected:

	UPROPERTY(EditAnywhere, Category = ObjectPool)
	TArray<APlayerBullet*> ObjectPool;
	UPROPERTY(EditAnywhere, Category = ObjectPool)
	TArray<int> SpawnedPoolIndexes;
		
private:
	// Pool 소유자 저장
	UPROPERTY(VisibleAnywhere, Category = FSM)
	class AMyPlayer* me = nullptr;

};
