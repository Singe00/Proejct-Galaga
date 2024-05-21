// Fill out your copyright notice in the Description page of Project Settings.


#include "SuisideEnemy.h"

ASuisideEnemy::ASuisideEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/spaceship_3_Cube_010.spaceship_3_Cube_010'");
	SetMType(EEnemyType::Suiside);
	SetMAttackType(EEnemyAttackType::Suiside);
	SetEnemyHp(2.0f);
	SetEnemySpeed(1000.0f);
	SetEnemyAttackSpeed(1.5f);
}

void ASuisideEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ASuisideEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
