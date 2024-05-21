// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolEnemy.h"
#include "EnemyManager.h"

APatrolEnemy::APatrolEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/SpaceFighter_Cube_006.SpaceFighter_Cube_006'");
	SetMType(EEnemyType::Patrol);
	SetMAttackType(EEnemyAttackType::Front);
	SetEnemyHp(3.0f);
	SetEnemySpeed(550.0f);
	SetEnemyAttackSpeed(3.0f);
	SetIdleDelayTime(PatrolDelayTime);
}

void APatrolEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (AutoPatrolMovingPoint)
	{
		TArray<AActor*> PatrolMovingPoints = fsm->enemyManager->GetRandomPatrolMovingPoint();
		TargetMovingPoints.Add(PatrolMovingPoints[0]);
		TargetMovingPoints.Add(PatrolMovingPoints[1]);
	}
	else
	{
		// doesn't matter
		AActor* FirstPatrolMovingPoints = fsm->enemyManager->GetFixedMovingPoint(FirstPatrolMovingPointIndex); // Function is GetFixedMovingPoint But Actual work is get inner movingpoint by index
		AActor* SecondPatrolMovingPoints = fsm->enemyManager->GetFixedMovingPoint(SecondPatrolMovingPointIndex); // Function is GetFixedMovingPoint But Actual work is get inner movingpoint by index

		TargetMovingPoints.Add(FirstPatrolMovingPoints);
		TargetMovingPoints.Add(SecondPatrolMovingPoints);
	}
	SetEnemyTargetMovingPointIndex(0);
	FVector targetLocation = TargetMovingPoints[0]->GetActorLocation();
	FVector dir = targetLocation - GetActorLocation();
	dir.Normalize();
	fsm->SetNowMovingDir(dir);


}

void APatrolEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
