// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBulletPool.h"
#include "PlayerAttack.h"
#include "MyPlayer.h"

// Sets default values for this component's properties
UPlayerBulletPool::UPlayerBulletPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UPlayerBulletPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	me = Cast<AMyPlayer>(GetOwner());

	if (me == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No me"));
	}

	if (PooledObjectSubclass != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int i = 0; i < PoolSize; i++)
		{
			APlayerBullet* PoolableActor = GetWorld()->SpawnActor<APlayerBullet>(PooledObjectSubclass, FVector(-2500,-2500,0), FRotator::ZeroRotator, param);

			if (PoolableActor != nullptr)
			{
				PoolableActor->SetActive(false);
				PoolableActor->SetPoolIndex(i);
				PoolableActor->OnPlayerPooledBulletDespawn.AddDynamic(this, &UPlayerBulletPool::OnPlayerPooledBulletDespawn);

				this->ObjectPool.Add(PoolableActor);

			}
		}
	}
}

APlayerBullet* UPlayerBulletPool::SpawnPlayerPooledBullet()
{
	double angleBetweenBullets = (me->PlayerAttack->GetMaxAngle() != 0) ? (me->PlayerAttack->GetMaxAngle() / (me->PlayerAttack->GetBulletCount()-1)) : 0;
	double startAngle = (me->PlayerAttack->GetMaxAngle() != 0) ? ((me->PlayerAttack->GetMaxAngle() / 2)) : 0;

	for (int i = 0; i < me->PlayerAttack->GetBulletCount(); i++)
	{
		double angle = startAngle - i * angleBetweenBullets;
		double angleInRadians = FMath::DegreesToRadians(angle);


		FRotator bulletRotation = me->GetActorRotation();
		bulletRotation.Yaw += angle;

		FVector spawnLocation = me->GetActorLocation() + FVector(cos(angleInRadians), sin(angleInRadians), 0)*200;

		for (APlayerBullet* PoolableActor : this->ObjectPool)
		{
			if (PoolableActor != nullptr && !PoolableActor->IsActive())
			{
				if (!PoolableActor->TeleportTo(spawnLocation, bulletRotation,false,true))
				{
					UE_LOG(LogTemp, Warning, TEXT("teleport fail %d"), i);
				}
				PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
				PoolableActor->SetActive(true);
				SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
				break;
			}
		}
	}

	return nullptr;
}


void UPlayerBulletPool::OnPlayerPooledBulletDespawn(APlayerBullet* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

