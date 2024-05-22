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
	// 풀 순회
	for (AEnemyBullet* PoolableActor : ObjectPool)
	{
		// 총알이 존재하고 && 활성화 상태가 아니라면
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			// 소환된 위치로 이동
			PoolableActor->TeleportTo(newLocation, newRotation, false, true);
			// 매개변수 시간만큼 생명 주기 설정
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			// 활성화
			PoolableActor->SetActive(true);
			// 활성화 목록 배열에 추가
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			// 풀링 오브젝트 반환
			return PoolableActor;
		}
	}

	// 조건에 맞는 총알이 없었다면 반환 실패하고 실행됨
	// 활성화 목록 배열의 크기가 1 이상이라면 > 예외처리
	if (SpawnedPoolIndexes.Num() > 0)
	{
		// 가장 오래된 총알을 제거한 후
		int PoolObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PoolObjectIndex);
		AEnemyBullet* PoolableActor = this->ObjectPool[PoolObjectIndex];

		// 활성화를 초기화해준다.
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

