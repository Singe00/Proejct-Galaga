// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitEnemy.h"

// Sets default values
AOrbitEnemy::AOrbitEnemy()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/Merge_BBB8DABB.Merge_BBB8DABB'");
	SetMType(EEnemyType::Fixed);
	SetMAttackType(EEnemyAttackType::Orbit);
	SetEnemyHp(4.0f);
	SetEnemySpeed(700.0f);
	SetEnemyAttackSpeed(2.0f);
}

// Called when the game starts or when spawned
void AOrbitEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrbitEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

