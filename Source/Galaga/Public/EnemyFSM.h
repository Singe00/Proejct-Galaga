// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	DIE,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAGA_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	bool isIn = true;

private:
	UPROPERTY(VisibleAnywhere,Category=FSM)
	EEnemyState mState = EEnemyState::MOVE;

	// 공격 대상 저장
	UPROPERTY(VisibleAnywhere, Category = FSM)
	class AMyPlayer* attackTarget = nullptr;
	// FSM 소유자 저장
	UPROPERTY(VisibleAnywhere, Category = FSM)
	class AEnemyBase* me = nullptr;
	// 상태 누적 시간
	UPROPERTY(VisibleAnywhere, Category = FSM)
	float currentTime = 0.0f;
	// 현재 이동 방향
	UPROPERTY(VisibleAnywhere, Category = FSM)
	FVector NowMovingDir;
	// 이동상태
	UPROPERTY(VisibleAnywhere, Category = FSM)
	bool isMoving = true;
	UPROPERTY(VisibleAnywhere, Category = FSM)
	float patternTime = 0.0f;

	FTimerHandle LaserTimer;

public:
	// EnemyManager 저장
	UPROPERTY(VisibleAnywhere, Category = enemyManager)
	class AEnemyManager* enemyManager = nullptr;

private:
	void FindTarget();
	FVector GetDirection();

private:
	void IdleState();
	void MoveState();
	void AttackState();
	void DieState();

public: // Getter
	bool GetIsMoving() const { return isMoving; }
	FVector GetNowMovingDir() const { return NowMovingDir; }

public: // Setter
	void SetIdleState() { this->mState = EEnemyState::IDLE; }
	void SetMoveState() { this->mState = EEnemyState::MOVE; }
	void SetAttackState() { this->mState = EEnemyState::ATTACK; }
	void SetDieState() { this->mState = EEnemyState::DIE;}

	void SetIsMoving(bool newIsMoving) { this->isMoving = newIsMoving; }
	void SetNowMovingDir(FVector newNowMovingDir) { this->NowMovingDir = newNowMovingDir; }

private:
	void SuisideMove();
	void PatrolMove();
	void FixedMove();
	void PassByMove();
	void RandomMove();
	void InOutMove();

private:
	void FrontAttack();
	void TargetAttack();
	void SpreadAttack();
	void OrbitAttack();
	void WaveAttack();
	void LaserAttack();
	void AngleAttack();

private:
	void FocusPlayer();
	void FocusTargetMP();
	void FocusCenter();
	void FocusFront();
	void FocusBack();
	void FocusPlayerOnce();
};
