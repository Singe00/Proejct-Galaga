// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveEnemy.h"

// Sets default values
AWaveEnemy::AWaveEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/spaceship_Cube_034.spaceship_Cube_034'");
	SetMType(EEnemyType::Fixed);
	SetMAttackType(EEnemyAttackType::Wave);
	SetEnemyHp(4.0f);
	SetEnemySpeed(700.0f);
	SetEnemyAttackSpeed(0.05f);
}

// Called when the game starts or when spawned
void AWaveEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

