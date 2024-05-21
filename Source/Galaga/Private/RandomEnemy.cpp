// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomEnemy.h"
#include "EnemyManager.h"

ARandomEnemy::ARandomEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/spaceship_Cube_005'");
	SetMType(EEnemyType::Random);
	SetMAttackType(EEnemyAttackType::Front);
	SetEnemyHp(3.0f);
	SetEnemySpeed(550.0f);
	SetEnemyAttackSpeed(4.0f);
}

void ARandomEnemy::BeginPlay()
{
	Super::BeginPlay();


	FVector targetLocation = fsm->enemyManager->GetRandomInnerMovingPoint();
	FVector dir = targetLocation - GetActorLocation();
	dir.Normalize();
	fsm->SetNowMovingDir(dir);
}

void ARandomEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
