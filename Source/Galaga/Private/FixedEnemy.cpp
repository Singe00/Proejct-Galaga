// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedEnemy.h"
#include "EnemyManager.h"

AFixedEnemy::AFixedEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/spaceship-cb1/source/spaceship-cb1.spaceship-cb1'");
	SetMType(EEnemyType::Fixed);
	SetMAttackType(EEnemyAttackType::Front);
	SetEnemyHp(4.0f);
	SetEnemySpeed(700.0f);
	SetEnemyAttackSpeed(4.0f);
}

void AFixedEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (AutoFixedMovingPoint)
	{
		AActor* FixedMovingPoints = fsm->enemyManager->GetFixedMovingPoint();
		TargetMovingPoints.Add(FixedMovingPoints);
	}
	else
	{
		AActor* FixedMovingPoints = fsm->enemyManager->GetFixedMovingPoint(FixedMovingPointIndex);
		TargetMovingPoints.Add(FixedMovingPoints);
	}
	SetEnemyTargetMovingPointIndex(0);
}

void AFixedEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}