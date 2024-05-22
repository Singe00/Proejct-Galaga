// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyFSM.h"
#include "Item.h"
#include "GameManager.h"
#include "EnemyBulletPool.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"


UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Suiside,	// 자폭형
	Patrol,		// 순회형
	Fixed,		// 고정형
	PassBy,		// 패스형
	Random,		// 무작위형
	InOut,		// 출입형
};

UENUM(BlueprintType)
enum class EEnemyAttackType : uint8
{
	Suiside,	// 자폭형
	Front,		// 전방형
	Target,		// 대상형
	Spread,		// 확산형
	Orbit,		// 궤도형
	Laser,		// 즉발형 
	Wave,		// 파도형
	Angle,		// 각도형
};

UENUM(BlueprintType)
enum class EEnemyFocus : uint8
{
	Player,		// 플레이어 주시
	TargetMP,	// 목표 MP 주시
	Front,		// 전방 주시
	Back,		// 후방 주시
	Center,		// 중앙 주시
	PlayerOnce,	// 플레이어 1회 주시
};

UCLASS()
class GALAGA_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UGameManager* GameManager;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected: // Components
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=EnemyBody,meta=(AllowPrivateAccess = true))
	class UStaticMeshComponent* EnemyBody;

	UPROPERTY(VisibleAnywhere,Category = EnemyBody)
	class UBoxComponent* EnemyBodyCollision;


public: // FSM
	// FSM 액터 컴포넌트
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = FSM)
	class UEnemyFSM* fsm;
	// 활성화 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FSM)
	bool isActiveFSM = false;
	// 활성화 타입 시간 or 의존 대상
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	bool isActiveByTime = true;
	// 활성화 시간 경과 시 FSM 활성화
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM, meta = (EditCondition = "isActiveByTime"))
	float FSMActiveTime = 10.0f;

	// 의존 대상 사망 시 FSM 활성화
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM, meta = (EditCondition = "!isActiveByTime"))
	AActor* dependencyEnemy = nullptr;

	// 출입 움직임 패턴 대기 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	float InOutDelayTime = 1.0f;

protected: // Enemy Stat
	// 체력
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnemyStat, meta = (AllowPrivateAccess = "true"))
	float EnemyHp = 3.0f;
	// 최대 체력
	UPROPERTY(EditAnywhere, Category = EnemyStat)
	float EnemyMaxHp = 3.0f;
	// 이동속도
	UPROPERTY(EditAnywhere, Category = EnemyStat)
	float EnemySpeed = 750.0f;
	// 공격속도
	UPROPERTY(EditAnywhere, Category = EnemyStat)
	float EnemyAttackSpeed = 1.5f;
	// 움직임 패턴
	UPROPERTY(EditAnywhere, Category = EnemyStat)
	EEnemyType mType;
	// 공격패턴
	UPROPERTY(EditAnywhere, Category = EnemyStat)
	EEnemyAttackType mAttackType;
	// 대기시간
	float IdleDelayTime = 0;

	// 점수
	UPROPERTY(EditAnywhere, Category = EnemyStat)
	int scorePoint = 50;

public: // Else
	// 주시 패턴
	UPROPERTY(EditAnywhere, Category = FSM)
	EEnemyFocus isFocusPlayer = EEnemyFocus::Front;
	// 아이템 드랍 여부
	UPROPERTY(EditAnywhere, Category = SpawnItem)
	bool isSpawnItemWhenDie = false;
	// 아이템 공장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnItem, meta = (EditCondition = "isSpawnItemWhenDie"))
	TSubclassOf<class AItem> SpawnItem;
	// 파도 공격 패턴 진폭값
	UPROPERTY(EditAnywhere, Category = EnemyStat, meta = (EditCondition = "mAttackType == EEnemyAttackType::Wave", ClampMin = "300", ClampMax = "800"))
	float WaveRange = 300;
	// 각도 공격 패턴 총알 개수
	UPROPERTY(EditAnywhere, Category = EnemyStat, meta = (EditCondition = "mAttackType == EEnemyAttackType::Angle", ClampMin = "3", ClampMax = "13"))
	float BulletCount = 3;

public: // Getter
	UFUNCTION(BlueprintCallable, Category = EnemyStat)
	float GetEnemyHp() const { return EnemyHp; }
	UFUNCTION(BlueprintCallable, Category = EnemyStat)
	float GetEnemyMaxHp() const { return EnemyMaxHp; }
	float GetEnemySpeed()const { return EnemySpeed; }
	float GetEnemyAttackSpeed()const { return EnemyAttackSpeed; }
	EEnemyType GetMType() const { return mType; }
	EEnemyAttackType GetMAttackType() const { return mAttackType; }
	UEnemyFSM* GetFSM() const { return fsm; }
	AActor* GetTargetMovingPoint() const { return TargetMovingPoints[0]; }
	AActor* GetTargetMovingPointByIndex(int targetMovingPointIndex) const { return TargetMovingPoints[targetMovingPointIndex]; }
	int GetEnemyTargetMovingPointIndex() const{ return enemyTargetMovingPointIndex; }
	EEnemyFocus GetIsFocusPlayer() const { return isFocusPlayer; }
	float GetIdleDelayTime() const { return IdleDelayTime; }

	// FSM Active
	bool GetIsActiveFSM() const { return isActiveFSM; }
	float GetFSMActiveTime() const { return FSMActiveTime; }
	AActor* GetDependencyEnemy() const { return dependencyEnemy; }

	float GetInOutDelayTime() const { return InOutDelayTime; }
	
	float GetWaveRange() const { return WaveRange; }
	float GetBulletCount() const { return BulletCount; }

public: // Setter
	void SetEnemyHp(float NewEnemyHp) { this->EnemyHp = NewEnemyHp; }
	void SetEnemyMaxHp(float NewEnemyMaxHp) { this->EnemyMaxHp = NewEnemyMaxHp; }
	void SetEnemySpeed(float NewEnemySpeed) { this->EnemySpeed = NewEnemySpeed; }
	void SetEnemyAttackSpeed(float NewEnemyAttackSpeed) { this->EnemyAttackSpeed = NewEnemyAttackSpeed; }
	void SetMType(EEnemyType NewMType) { this->mType = NewMType; }
	void SetMAttackType(EEnemyAttackType NewMAttackType) { this->mAttackType = NewMAttackType; }
	void SetEnemyTargetMovingPointIndex(int NewEnemyTargetMovingPointIndex) { this->enemyTargetMovingPointIndex = NewEnemyTargetMovingPointIndex; }
	void SetIsFocusPlayer(EEnemyFocus NewIsFocusPlayer) { this->isFocusPlayer = NewIsFocusPlayer; }
	void SetIdleDelayTime(float NewIdleDelayTime) { this->IdleDelayTime = NewIdleDelayTime; }

	// FSM Active
	void SetFSMActiveTime(float NewFSMActiveTime) { this->FSMActiveTime = NewFSMActiveTime; }
	void SetDependencyEnemy(AActor* NewDependencyEnemy) { this->dependencyEnemy = NewDependencyEnemy; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "FSM")
	void SetIsActiveFSM();

	void SetInOutDelayTime(float NewInOutDelayTime) { this->InOutDelayTime = NewInOutDelayTime; }
	void SetWaveRange(float NewWaveRange) { this->WaveRange = NewWaveRange; }
	void SetBulletCount(float NewBulletCount) { this->BulletCount = NewBulletCount; }

protected: // Function
	UFUNCTION()
	void OnComponentBeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// 피격 함수
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// 적 외형 동적 할당 함수
	void SetEnemyBodyMesh(FString EnemyBodyPath);
	// 아이템 드랍 함수
	void SpawnPlayerItem();


protected: // MovingPoints
	// 대상 무빙포인트
	UPROPERTY(EditAnywhere, Category = MovingPoint)
	TArray<class AActor*> TargetMovingPoints;
	// 대상 무빙포인트 인덱스
	UPROPERTY(VisibleAnywhere, Category = MovingPoint)
	int enemyTargetMovingPointIndex = 0;

public:
	// 목표 무빙포인트 방향 얻기
	FVector GetDirectionToTargetMovingPoint(float index);
	
public:
	// 총알 Object Pool
	UPROPERTY(VisibleAnywhere,Category="EnemyBulletPool")
	AEnemyBulletPool* bulletPool;

public: // 이펙트
	// 레이저 이펙트
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LaserEffect")
	void laserEffect();
	// 사망 시 폭팔 이펙트
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detroying")
	void DestroyingEnemy();
	// 총알 발사 소리
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "FireSound")
	void FireSound();
};
