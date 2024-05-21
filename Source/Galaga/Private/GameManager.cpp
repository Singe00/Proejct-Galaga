// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "EnemyBase.h"
#include "PlayerAttack.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "SaveStage.h"


UGameManager::UGameManager()
{
	SaveSlotName = TEXT("Player1");

	LoadSaveData(SaveSlotName);

	InitStat();
}

void UGameManager::SavePlayerStat(float savePlayerHp, int saveBoomCount, float saveAttackDamage, float saveAttackSpeed, int saveBulletCount, float saveMaxAngle)
{

	UE_LOG(LogTemp, Warning, TEXT("GM Save Stat Func"));
	UE_LOG(LogTemp, Warning, TEXT("%f"),savePlayerHp);
	UE_LOG(LogTemp, Warning, TEXT("%d"), saveBoomCount);

	GM_PlayerStat.PlayerHp = savePlayerHp;
	GM_PlayerStat.BoomCount = saveBoomCount;
	GM_PlayerStat.AttackDamage = saveAttackDamage;
	GM_PlayerStat.AttackSpeed = saveAttackSpeed;
	GM_PlayerStat.BulletCount = saveBulletCount;
	GM_PlayerStat.MaxAngle = saveMaxAngle;

}

FPlayerStats UGameManager::LoadPlayerStat()
{
	return GM_PlayerStat;
}

void UGameManager::InitStat()
{
	GM_PlayerStat.PlayerHp = 3.0f;
	GM_PlayerStat.BoomCount = 2;
	GM_PlayerStat.AttackDamage = 1.0f;
	GM_PlayerStat.AttackSpeed = 0.3;
	GM_PlayerStat.BulletCount = 1;
	GM_PlayerStat.MaxAngle = 0.0f;
}

void UGameManager::OnStageClear()
{
	auto GetPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPlayer::StaticClass());
	if (GetPlayer)
	{
		MyPlayer = Cast<AMyPlayer>(GetPlayer);
		if (MyPlayer != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Is Null"));
		}

	}

	SavePlayerStat(MyPlayer->GetPlayerHp(), MyPlayer->GetPlayerBoomCount(), MyPlayer->PlayerAttack->GetAttackDamage(), MyPlayer->PlayerAttack->GetAttackSpeed(), MyPlayer->PlayerAttack->GetBulletCount(), MyPlayer->PlayerAttack->GetMaxAngle());
}

void UGameManager::OnStageRestart()
{
	InitStat();
}

void UGameManager::AddScorePoint(int sp)
{
	score += sp;
}

void UGameManager::LoadSaveData(FString slotName)
{
	USaveStage* SaveStage = Cast<USaveStage>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	if (SaveStage == nullptr)
	{
		SaveStage = GetMutableDefault<USaveStage>();
	}

	SetClearStage(SaveStage->ClearStageIndex);
}
