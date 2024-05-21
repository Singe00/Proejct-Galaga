// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GameManager.h"
#include "BossBase.generated.h"

USTRUCT(BlueprintType)
struct FChangeByHp
{
    GENERATED_BODY()

public:

	// Set Enemy Stat
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
    float changeHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	float changeMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	float changeAttackSpeed;

	// Set Enemy Attack Type
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEnemyAttackType changeAttackType;

	// Set Enemy Moving Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "changeAttackType != EEnemyAttackType::Suiside"))
	EEnemyType changeMoveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyFocus isFocusPlayer = EEnemyFocus::Front;

	// Set Auto Fixed Move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "changeMoveType == EEnemyType::Fixed"))
	bool AutoFixedMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "!AutoFixedMove && changeMoveType == EEnemyType::Fixed", ClampMin = "0"))
	int FixedMovingPointIndex = 0;

	// Set Auto Patrol Move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "changeMoveType == EEnemyType::Patrol"))
	bool AutoPatrolMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!AutoPatrolMove && changeMoveType == EEnemyType::Patrol", ClampMin = "0", ClampMax = "3"))
	float PatrolDelayTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!AutoPatrolMove && changeMoveType == EEnemyType::Patrol", ClampMin = "0"))
	int FirstPatrolMovingPointIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!AutoPatrolMove && changeMoveType == EEnemyType::Patrol", ClampMin = "0"))
	int SecondPatrolMovingPointIndex = 0;

	// Wave Range
	UPROPERTY(EditAnywhere, Category = EnemyStat, meta = (EditCondition = "changeAttackType == EEnemyAttackType::Wave", ClampMin = "300", ClampMax = "800"))
	float BossWaveRange = 300;

	// Angle Bullet Count
	UPROPERTY(EditAnywhere, Category = EnemyStat, meta = (EditCondition = "changeAttackType == EEnemyAttackType::Angle", ClampMin = "3", ClampMax = "13"))
	float BossBulletCount = 3;

};
/**
 * 
 */
UCLASS()
class GALAGA_API ABossBase : public AEnemyBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABossBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeMoveType(EEnemyType newMoveType);
	void ChangeAttackType(EEnemyAttackType newAttackType);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=TypeChange)
	TArray<FChangeByHp> TypeChangeByHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameManager)
	UGameManager* GameManager;
	int SeeHpIndex = 0;

	void SeeHp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameManager)
	int32 BossStageIndex = 0;


private: // Fixed Move

	bool AutoFixedMovingPoint = true;

	int FixedMovingPointIndex = 0;

	void SetFixedMovingPoint(bool isAutoFixedMove, int NewFixedMovingPointIndex);

private: // Patrol Move
	// Auto Moving Point Get Select
	bool AutoPatrolMovingPoint = true;

	int FirstPatrolMovingPointIndex = 0;

	int SecondPatrolMovingPointIndex = 0;

	void SetPatrolMovingPoint(bool isAutoPatrolMove, int NewFirstPatrolMovingPointIndex,int NewSecondPatrolMovingPointIndex);


private: // Random Move
	void SetRandomMovingPoint();

public: // Getter
	// Fixed Move
	bool GetAutoFixedMovingPoint() const { return AutoFixedMovingPoint; }
	int GetFixedMovingPointIndex() const { return FixedMovingPointIndex; }

	// Patrol Move
	bool GetAutoPatrolMovingPoint() const { return AutoPatrolMovingPoint; }
	int GetFirstPatrolMovingPointIndex() const { return FirstPatrolMovingPointIndex; }
	int GetSecondPatrolMovingPointIndex() const { return SecondPatrolMovingPointIndex; }

public: // Setter
	// Fixed Move
	void SetAutoFixedMovingPoint(bool NewAutoFixedMovingPoint) { this->AutoFixedMovingPoint = NewAutoFixedMovingPoint; }
	void SetFixedMovingPointIndex(int NewFixedMovingPointIndex) { this->FixedMovingPointIndex = NewFixedMovingPointIndex; }

	// Patrol Move
	void SetAutoPatrolMovingPoint(bool NewAutoPatrolMovingPoint) { this->AutoPatrolMovingPoint = NewAutoPatrolMovingPoint; }
	void SetFirstPatrolMovingPointIndex(int NewFirstPatrolMovingPointIndex) { this->FirstPatrolMovingPointIndex = NewFirstPatrolMovingPointIndex; }
	void SetSecondPatrolMovingPointIndex(int NewSecondPatrolMovingPointIndex) { this->SecondPatrolMovingPointIndex = NewSecondPatrolMovingPointIndex; }
};
