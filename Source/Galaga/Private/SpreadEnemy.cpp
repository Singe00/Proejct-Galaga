// Fill out your copyright notice in the Description page of Project Settings.


#include "SpreadEnemy.h"

// Sets default values
ASpreadEnemy::ASpreadEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/spaceship_3_Cube_010.spaceship_3_Cube_010'");
	SetMType(EEnemyType::Fixed);
	SetMAttackType(EEnemyAttackType::Spread);
	SetEnemyHp(5.0f);
	SetEnemySpeed(700.0f);
	SetEnemyAttackSpeed(0.01f);
}

// Called when the game starts or when spawned
void ASpreadEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpreadEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

