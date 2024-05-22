// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerBulletPool.h"
#include "GameManager.h"
#include "MyPlayer.generated.h"


UCLASS()
class GALAGA_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public: // Component
	// �÷��̾� ��ü
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBody, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* PlayerBody;

	//�÷��̾� �ݸ���
	UPROPERTY(VisibleAnywhere, Category = PlayerBody)
	class USphereComponent* PlayerBodyCollision;

	// �Ѿ� ������ƮǮ ���� ������Ʈ ����
	UPROPERTY(VisibleAnywhere, Category = PlayerBulletPool)
	class UPlayerBulletPool* PlayerBulletPool;

	// �̵� ���� ������Ʈ ����
	UPROPERTY(VisibleAnywhere, Category = "PlayerMove")
	class UPlayerMove* PlayerMove;

	// ���� ���� ������Ʈ ����
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "PlayerAttack")
	class UPlayerAttack* PlayerAttack;

private:
	// ���� �Ŵ���
	UGameManager* GameManager;

private: // Player Stat
	// ü��
	UPROPERTY(EditAnywhere, Category = PlayerInfo)
	float PlayerHp;
	// ��ź ����
	UPROPERTY(VisibleAnywhere, Category = PlayerInfo)
	int PlayerBoomCount;

private: // User Input
	// ��ź ��� ���ε� �Լ�
	void Boom();

public:
	// �Ͻ����� ���ε� �Լ�
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GamePause")
	void Pause();


private: // Function
	// �ǰ� �Լ�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// �÷��̾� ���� ������ �ε� �Լ�
	UFUNCTION(BlueprintCallable,Category=LoadPlayerStat)
	void LoadPlayerStat();


public: // Getter

	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	float GetPlayerHp() const { return PlayerHp; }
	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	float GetPlayerBoomCount() const { return PlayerBoomCount; }

	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	float GetCoolTime() const { return coolTime; }
	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	float GetUltCoolTime() const { return UltCoolTime; }
	UFUNCTION(BlueprintCallable, Category = PlayerGetter)
	bool GetBoomCool() const { return isBoomCool; }




public: // Setter

	void SetPlayerHp(float newPlayerHp) { this->PlayerHp = newPlayerHp; }
	void SetBoomCount(float newBoomCount) { this->PlayerBoomCount = newBoomCount; }


public: // Function
	// ü�� ���� �Լ�
	void IncreasePlayerHp();
	// ��ź ���� ���� �Լ�
	void IncreasePlayerBoomCount();

	// �÷��̾� �ı� �� ����Ʈ �̺�Ʈ �Լ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detroying")
	void DestroyingPlayer();

	// ��ź ���  ����Ʈ �̺�Ʈ �Լ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BoomEffect")
	void PlayerBoomEffect();

	// �ʻ�� ����Ʈ �̺�Ʈ �Լ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UltEffect")
	void PlayerUltEffect();

	// �Ѿ� �߻� �� ���� ����Ʈ �̺�Ʈ �Լ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "FireSound")
	void FireSound();

private: // Else
	// �ǰ� ���� ����
	UPROPERTY(VisibleAnywhere, Category = PlayerInfo)
	bool isHit = false;

	// ��ź ��Ÿ�� ����
	UPROPERTY(VisibleAnywhere, Category = PlayerInfo)
	bool isBoomCool = false;

	// ��ź ��Ÿ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo, meta=(AllowPrivateAccess = true))
	float coolTime = 5.0f;

	// �ʻ�� ��Ÿ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo, meta = (AllowPrivateAccess = true))
	float UltCoolTime = 20.0f;

	// ���� ���� �Լ�
	void setCanHit() { this->isHit = false; }

	// ��ź ��� �Լ�
	void setCanUseBoom() { this->isBoomCool = false; }


};
