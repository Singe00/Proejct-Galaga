// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveStage.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_API USaveStage : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveStage();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	int32 ClearStageIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<float> SoundVolumns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	float totalScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	int ScreenMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	int Resolution;

	//UPROPERTY()
	//FString PlayerName;

};
