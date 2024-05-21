// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"


class AMyPlayer;
class AEnemyBase;

USTRUCT(BlueprintType)
struct FPlayerStats
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerHp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int BoomCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int BulletCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxAngle;
};
/**
 * 
 */
UCLASS()
class GALAGA_API UGameManager : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UGameManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SaveData)
    int32 ClearStage = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SaveData)
    FString SaveSlotName;

public:

    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=SaveData)
    FPlayerStats GM_PlayerStat;

    AMyPlayer* MyPlayer;
    AEnemyBase* Enemy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StageNumber)
    int StageNumber = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Score)
    int score = 0;

    int32 GetClearStage() const { return ClearStage; }

public:
    void SavePlayerStat(float savePlayerHp, int saveBoomCount, float saveAttackDamage, float saveAttackSpeed, int saveBulletCount, float saveMaxAngle);
    FPlayerStats LoadPlayerStat();

    void InitStat();

    UFUNCTION(BlueprintCallable,Category=OnStageClear)
    void OnStageClear();

    UFUNCTION(BlueprintCallable, Category = OnStageClear)
    void OnStageRestart();

    void AddScorePoint(int sp);

    void SetClearStage(int32 NewClearStage) { this->ClearStage = NewClearStage; }

    UFUNCTION(BlueprintCallable,Category=SaveData)
    void LoadSaveData(FString slotName);
};
