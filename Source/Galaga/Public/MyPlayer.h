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
	// 플레이어 몸체
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBody, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* PlayerBody;

	//플레이어 콜리전
	UPROPERTY(VisibleAnywhere, Category = PlayerBody)
	class USphereComponent* PlayerBodyCollision;

	// 총알 오브젝트풀 액터 컴포넌트 부착
	UPROPERTY(VisibleAnywhere, Category = PlayerBulletPool)
	class UPlayerBulletPool* PlayerBulletPool;

	// 이동 액터 컴포넌트 부착
	UPROPERTY(VisibleAnywhere, Category = "PlayerMove")
	class UPlayerMove* PlayerMove;

	// 공격 액터 컴포넌트 부착
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "PlayerAttack")
	class UPlayerAttack* PlayerAttack;

private:
	// 게임 매니저
	UGameManager* GameManager;

private: // Player Stat
	// 체력
	UPROPERTY(EditAnywhere, Category = PlayerInfo)
	float PlayerHp;
	// 폭탄 개수
	UPROPERTY(VisibleAnywhere, Category = PlayerInfo)
	int PlayerBoomCount;

private: // User Input
	// 폭탄 사용 바인딩 함수
	void Boom();

public:
	// 일시정지 바인딩 함수
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="GamePause")
	void Pause();


private: // Function
	// 피격 함수
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// 플레이어 스탯 데이터 로드 함수
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
	// 체력 증가 함수
	void IncreasePlayerHp();
	// 폭탄 개수 증가 함수
	void IncreasePlayerBoomCount();

	// 플레이어 파괴 전 이펙트 이벤트 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detroying")
	void DestroyingPlayer();

	// 폭탄 사용  이펙트 이벤트 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BoomEffect")
	void PlayerBoomEffect();

	// 필살기 이펙트 이벤트 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UltEffect")
	void PlayerUltEffect();

	// 총알 발사 시 사운드 이펙트 이벤트 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "FireSound")
	void FireSound();

private: // Else
	// 피격 상태 여부
	UPROPERTY(VisibleAnywhere, Category = PlayerInfo)
	bool isHit = false;

	// 폭탄 쿨타임 여부
	UPROPERTY(VisibleAnywhere, Category = PlayerInfo)
	bool isBoomCool = false;

	// 폭탄 쿨타임
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo, meta=(AllowPrivateAccess = true))
	float coolTime = 5.0f;

	// 필살기 쿨타임
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo, meta = (AllowPrivateAccess = true))
	float UltCoolTime = 20.0f;

	// 무적 상태 함수
	void setCanHit() { this->isHit = false; }

	// 폭탄 사용 함수
	void setCanUseBoom() { this->isBoomCool = false; }


};
