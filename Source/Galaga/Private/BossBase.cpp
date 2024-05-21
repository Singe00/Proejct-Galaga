// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBase.h"
#include "EnemyManager.h"
#include "SaveStage.h"
#include "Kismet/GameplayStatics.h"

ABossBase::ABossBase()
{
	SetEnemyBodyMesh("/Script/Engine.StaticMesh'/Game/Meshs/fast_texturing_output_Polygon.fast_texturing_output_Polygon'");
	SetMType(EEnemyType::Fixed);
	SetMAttackType(EEnemyAttackType::Orbit);
	SetEnemyMaxHp(10.0f);
	SetEnemyHp(10);
	SetEnemySpeed(600.0f);
	SetEnemyAttackSpeed(2.0f);
}

void ABossBase::BeginPlay()
{
	Super::BeginPlay();
	GameManager = Cast<UGameManager>(GetGameInstance());
}

void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SeeHp();
}

void ABossBase::ChangeMoveType(EEnemyType newMoveType)
{
	this->SetMType(EEnemyType::Fixed);
}

void ABossBase::ChangeAttackType(EEnemyAttackType newAttackType)
{
	this->SetMAttackType(newAttackType);
}

void ABossBase::SeeHp()
{
	if (GetEnemyHp() > 0) // Is Boss Alive
	{
		if (TypeChangeByHp.Num() > SeeHpIndex) // Exception Handling Index Out of Bound
		{
			if (GetEnemyHp() <= TypeChangeByHp[SeeHpIndex].changeHp) // If Boss Hp under next pattern hp first time
			{
				// Type
				SetMAttackType(TypeChangeByHp[SeeHpIndex].changeAttackType);
				SetMType(TypeChangeByHp[SeeHpIndex].changeMoveType);
				SetIsFocusPlayer(TypeChangeByHp[SeeHpIndex].isFocusPlayer);

				// Stat
				SetEnemyAttackSpeed(TypeChangeByHp[SeeHpIndex].changeAttackSpeed);
				SetEnemySpeed(TypeChangeByHp[SeeHpIndex].changeMoveSpeed);

				// Fixed Move
				SetAutoFixedMovingPoint(TypeChangeByHp[SeeHpIndex].AutoFixedMove);
				SetFixedMovingPointIndex(TypeChangeByHp[SeeHpIndex].FixedMovingPointIndex);

				// Patrol Move
				SetAutoPatrolMovingPoint(TypeChangeByHp[SeeHpIndex].AutoPatrolMove);
				SetIdleDelayTime(TypeChangeByHp[SeeHpIndex].PatrolDelayTime);
				SetFirstPatrolMovingPointIndex(TypeChangeByHp[SeeHpIndex].FirstPatrolMovingPointIndex);
				SetSecondPatrolMovingPointIndex(TypeChangeByHp[SeeHpIndex].SecondPatrolMovingPointIndex);

				SetWaveRange(TypeChangeByHp[SeeHpIndex].BossWaveRange);
				SetBulletCount(TypeChangeByHp[SeeHpIndex].BossBulletCount);

				switch (GetMType())
				{
				case EEnemyType::Fixed:
					SetFixedMovingPoint(GetAutoFixedMovingPoint(), GetFixedMovingPointIndex());
					break;
				case EEnemyType::Patrol:
					SetPatrolMovingPoint(GetAutoPatrolMovingPoint(), GetFirstPatrolMovingPointIndex(), GetSecondPatrolMovingPointIndex());
					break;
				case EEnemyType::Random:
					SetRandomMovingPoint();
					break;
				default:
					break;
				}
				SeeHpIndex += 1;
			} 
		} // SeeHpIndex is bigger than size of TypeChangeByHp array
	} // Boss die
	else 
	{
		if (GameManager->GetClearStage() < this->BossStageIndex)
		{
			USaveStage* NewSaveStage = NewObject<USaveStage>();
			NewSaveStage->ClearStageIndex = this->BossStageIndex;

			if (UGameplayStatics::SaveGameToSlot(NewSaveStage, GameManager->SaveSlotName, 0) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("SaveGame Error!"));
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Already Clear!"));
		}
	}

}

void ABossBase::SetFixedMovingPoint(bool isAutoFixedMove, int NewFixedMovingPointIndex)
{

	TargetMovingPoints.Empty();

	if (isAutoFixedMove)
	{
		AActor* FixedMovingPoints = fsm->enemyManager->GetFixedMovingPoint();
		TargetMovingPoints.Add(FixedMovingPoints);
	}
	else
	{
		AActor* FixedMovingPoints = fsm->enemyManager->GetFixedMovingPoint(NewFixedMovingPointIndex);
		TargetMovingPoints.Add(FixedMovingPoints);
	}

	SetEnemyTargetMovingPointIndex(0);
}

void ABossBase::SetPatrolMovingPoint(bool isAutoPatrolMove, int NewFirstPatrolMovingPointIndex, int NewSecondPatrolMovingPointIndex)
{
	TargetMovingPoints.Empty();

	if (isAutoPatrolMove)
	{
		TArray<AActor*> PatrolMovingPoints = fsm->enemyManager->GetRandomPatrolMovingPoint();
		TargetMovingPoints.Add(PatrolMovingPoints[0]);
		TargetMovingPoints.Add(PatrolMovingPoints[1]);
		
	}
	else
	{
		// doesn't matter
		AActor* FirstPatrolMovingPoints = fsm->enemyManager->GetFixedMovingPoint(NewFirstPatrolMovingPointIndex); // Function is GetFixedMovingPoint But Actual work is get inner movingpoint by index
		AActor* SecondPatrolMovingPoints = fsm->enemyManager->GetFixedMovingPoint(NewSecondPatrolMovingPointIndex); // Function is GetFixedMovingPoint But Actual work is get inner movingpoint by index

		TargetMovingPoints.Add(FirstPatrolMovingPoints);
		TargetMovingPoints.Add(SecondPatrolMovingPoints);
	}
	SetEnemyTargetMovingPointIndex(0);
	FVector targetLocation = TargetMovingPoints[0]->GetActorLocation();
	FVector dir = targetLocation - GetActorLocation();
	dir.Normalize();
	fsm->SetNowMovingDir(dir);
}

void ABossBase::SetRandomMovingPoint()
{
	FVector targetLocation = fsm->enemyManager->GetRandomInnerMovingPoint();
	FVector dir = targetLocation - GetActorLocation();
	dir.Normalize();
	fsm->SetNowMovingDir(dir);
}
