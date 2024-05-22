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
	// ��ǲ �������̵�
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	// ���׷��̵� �Լ�
	void IncreaseAttackSpeed(); // ���ݼӵ� ����
	void IncreaseBulletDamage(); // ���ݷ� ����
	void IncreaseBulletCount(); // �Ѿ� ���� ����

private:
	void Fire(); // ����
	void Ultimate(); // �ʻ��

private: // Attack

	// ���ݷ�
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float AttackDamage;

	// ���ݼӵ�
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float AttackSpeed;

	// ���ݼӵ� Ÿ�̸�
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float AttackSpeedTimer = 0.0f;

	// ���� ����
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	bool isAttack = false;

	// �ʻ�� ��� ����
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	bool isUlt = false;

	// �Ѿ� ����
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	int BulletCount;


	// �ִ� ����
	UPROPERTY(VisibleAnywhere, Category = PlayerAttackStat)
	float MaxAngle;

	// �Ѿ� �߻� �Լ�
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

	// �ʻ�� Ÿ�̸� ����
	FTimerHandle FireUltTimer;

	// �ʻ�� ƽ ������ �Լ�
	void FireUlt();
	// �ʻ�� �ߴ� �Լ�
	void StopUlt();
};
