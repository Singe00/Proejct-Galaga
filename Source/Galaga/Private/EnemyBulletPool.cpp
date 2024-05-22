// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBulletPool.h"

// Sets default values
AEnemyBulletPool::AEnemyBulletPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyBulletPool::BeginPlay()
{
	Super::BeginPlay();
	
	if (PooledObjectSubclass != nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		for (int i = 0; i < PoolSize; i++)
		{
			AEnemyBullet* PoolableActor = GetWorld()->SpawnActor<AEnemyBullet>(PooledObjectSubclass, GetActorLocation(), FRotator::ZeroRotator, param);

			if (PoolableActor != nullptr)
			{
				PoolableActor->SetActive(false);
				PoolableActor->SetPoolIndex(i);
				PoolableActor->OnEnemyPooledBulletDespawn.AddDynamic(this, &AEnemyBulletPool::OnEnemyPooledBulletDespawn);

				this->ObjectPool.Add(PoolableActor);

			}
		}
	}
}

void AEnemyBulletPool::DeactiveAllBullets()
{
	for (AEnemyBullet* bullet : ObjectPool)
	{
		bullet->Deactivate();
	}
	SpawnedPoolIndexes.Empty();
}

AEnemyBullet* AEnemyBulletPool::SpawnPooledObject(FVector newLocation, FRotator newRotation)
{
	// Ǯ ��ȸ
	for (AEnemyBullet* PoolableActor : ObjectPool)
	{
		// �Ѿ��� �����ϰ� && Ȱ��ȭ ���°� �ƴ϶��
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			// ��ȯ�� ��ġ�� �̵�
			PoolableActor->TeleportTo(newLocation, newRotation, false, true);
			// �Ű����� �ð���ŭ ���� �ֱ� ����
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			// Ȱ��ȭ
			PoolableActor->SetActive(true);
			// Ȱ��ȭ ��� �迭�� �߰�
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			// Ǯ�� ������Ʈ ��ȯ
			return PoolableActor;
		}
	}

	// ���ǿ� �´� �Ѿ��� �����ٸ� ��ȯ �����ϰ� �����
	// Ȱ��ȭ ��� �迭�� ũ�Ⱑ 1 �̻��̶�� > ����ó��
	if (SpawnedPoolIndexes.Num() > 0)
	{
		// ���� ������ �Ѿ��� ������ ��
		int PoolObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PoolObjectIndex);
		AEnemyBullet* PoolableActor = this->ObjectPool[PoolObjectIndex];

		// Ȱ��ȭ�� �ʱ�ȭ���ش�.
		if (PoolableActor != nullptr)
		{
			PoolableActor->SetActive(false);

			PoolableActor->TeleportTo(newLocation, newRotation, false, true);
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());

			return PoolableActor;
		}
	}


	return nullptr;
}

void AEnemyBulletPool::OnEnemyPooledBulletDespawn(AEnemyBullet* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

