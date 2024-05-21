// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserEnemy.h"

// Sets default values
ALaserEnemy::ALaserEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/SpaceFighter_Cube_006.SpaceFighter_Cube_006'");
	SetMType(EEnemyType::Fixed);
	SetMAttackType(EEnemyAttackType::Laser);
	SetEnemyHp(4.0f);
	SetEnemySpeed(700.0f);
	SetEnemyAttackSpeed(4.0f);
}

// Called when the game starts or when spawned
void ALaserEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

