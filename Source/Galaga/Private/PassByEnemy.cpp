// Fill out your copyright notice in the Description page of Project Settings.


#include "PassByEnemy.h"
#include "EnemyManager.h"

APassByEnemy::APassByEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/spaceship_3_Cube_003.spaceship_3_Cube_003'");
	SetMType(EEnemyType::PassBy);
	SetMAttackType(EEnemyAttackType::Target);
	SetEnemyHp(1.0f);
	SetEnemySpeed(1200.0f);
	SetEnemyAttackSpeed(2.5f);
	EnemyBody->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
}

void APassByEnemy::BeginPlay()
{
	Super::BeginPlay();

	AActor* PassByMovingPoints;
	if (AutoPassByMovingPoint)
	{
		
		if (TargetIsLeft)
		{
			PassByMovingPoints = fsm->enemyManager->GetLeftMovingPoint();
		}
		else 
		{
			PassByMovingPoints = fsm->enemyManager->GetRightMovingPoint();
		}
	}
	else
	{
		if (TargetIsLeft)
		{
			PassByMovingPoints = fsm->enemyManager->GetLeftMovingPoint(PassByMovingPointIndex);
		}
		else
		{
			PassByMovingPoints = fsm->enemyManager->GetRightMovingPoint(PassByMovingPointIndex);
		}
	}
	TargetMovingPoints.Add(PassByMovingPoints);
	SetEnemyTargetMovingPointIndex(0);
}

void APassByEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
