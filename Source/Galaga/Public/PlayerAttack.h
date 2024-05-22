// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerAttack.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_API UPlayerAttack : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
	UPlayerAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	// 인풋 오버라이딩
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	// 업그레이드 함수
	void IncreaseAttackSpeed(); // 공격속도 증가
	void IncreaseBulletDamage(); // 공격력 증가
	void IncreaseBulletCount(); // 총알 개수 증가

private:
	void Fire(); // 공격
	void Ultimate(); // 필살기

private: // Attack

	// 공격력
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float AttackDamage;

	// 공격속도
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float AttackSpeed;

	// 공격속도 타이머
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float AttackSpeedTimer = 0.0f;

	// 공격 여부
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	bool isAttack = false;

	// 필살기 사용 여부
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	bool isUlt = false;

	// 총알 개수
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	int BulletCount;


	// 최대 각도
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float MaxAngle;

	// 총알 발사 함수
	void FireBullet(float DeltaTime);

public: // Getter
	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	float GetAttackDamage() const { return AttackDamage; }
	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	int GetBulletCount() const { return BulletCount; }
	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	float GetAttackSpeed() const { return AttackSpeed; }
	float GetMaxAngle() const { return MaxAngle; }
	UFUNCTION(BlueprintCallable, Category = PlayerAttackGetter)
	bool GetIsUlt() const { return isUlt; }

public: // Setter
	void SetAttackDamage(float newAttackDamage) { this->AttackDamage = newAttackDamage; }
	void SetAttackSpeed(float newAttackSpeed) { this->AttackSpeed = newAttackSpeed; }
	void SetBulletCount(float newBulletCount) { this->BulletCount = newBulletCount; }
	void SetMaxAngle(float newMaxAngle) { this->MaxAngle = newMaxAngle; }
	void SetIsUlt(bool NewIsUlt) { this->isUlt = NewIsUlt; }

public:

	// 필살기 타이머 변수
	FTimerHandle FireUltTimer;

	// 필살기 틱 데미지 함수
	void FireUlt();
	// 필살기 중단 함수
	void StopUlt();
};
