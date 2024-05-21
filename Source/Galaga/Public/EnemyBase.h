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
	Suiside,
	Patrol,
	Fixed,
	PassBy,
	Random,
	InOut,
};

UENUM(BlueprintType)
enum class EEnemyAttackType : uint8
{
	Suiside,
	Front,
	Target,
	Spread,
	Orbit,
	Laser,
	Wave,
	Angle,
};

UENUM(BlueprintType)
enum class EEnemyFocus : uint8
{
	Player,
	TargetMP,
	Front,
	Back,
	Center,
	PlayerOnce,
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
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = FSM)
	class UEnemyFSM* fsm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FSM)
	bool isActiveFSM = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	bool isActiveByTime = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM, meta = (EditCondition = "isActiveByTime"))
	float FSMActiveTime = 10.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM, meta = (EditCondition = "!isActiveByTime"))
	AActor* dependencyEnemy = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
	float InOutDelayTime = 1.0f;

protected: // Enemy Stat
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnemyStat, meta = (AllowPrivateAccess = "true"))
	float EnemyHp = 3.0f;

	UPROPERTY(EditAnywhere, Category = EnemyStat)
	float EnemyMaxHp = 3.0f;

	UPROPERTY(EditAnywhere, Category = EnemyStat)
	float EnemySpeed = 750.0f;

	UPROPERTY(EditAnywhere, Category = EnemyStat)
	float EnemyAttackSpeed = 1.5f;

	UPROPERTY(EditAnywhere, Category = EnemyStat)
	EEnemyType mType;

	UPROPERTY(EditAnywhere, Category = EnemyStat)
	EEnemyAttackType mAttackType;

	float IdleDelayTime = 0;


	UPROPERTY(EditAnywhere, Category = EnemyStat)
	int scorePoint = 50;

public: // Else
	UPROPERTY(EditAnywhere, Category = FSM)
	EEnemyFocus isFocusPlayer = EEnemyFocus::Front;

	UPROPERTY(EditAnywhere, Category = SpawnItem)
	bool isSpawnItemWhenDie = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnItem, meta = (EditCondition = "isSpawnItemWhenDie"))
	TSubclassOf<class AItem> SpawnItem;

	UPROPERTY(EditAnywhere, Category = EnemyStat, meta = (EditCondition = "mAttackType == EEnemyAttackType::Wave", ClampMin = "300", ClampMax = "800"))
	float WaveRange = 300;

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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SetEnemyBodyMesh(FString EnemyBodyPath);

	void SpawnPlayerItem();


protected: // MovingPoints
	UPROPERTY(EditAnywhere, Category = MovingPoint)
	TArray<class AActor*> TargetMovingPoints;
	UPROPERTY(VisibleAnywhere, Category = MovingPoint)
	int enemyTargetMovingPointIndex = 0;

public:
	FVector GetDirectionToTargetMovingPoint(float index);
	
public:
	UPROPERTY(VisibleAnywhere,Category="EnemyBulletPool")
	AEnemyBulletPool* bulletPool;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LaserEffect")
	void laserEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detroying")
	void DestroyingEnemy();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "FireSound")
	void FireSound();
};
