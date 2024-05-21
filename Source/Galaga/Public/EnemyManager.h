// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class GALAGA_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Inner Moving Points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnSettings)
	TArray<class AActor*> InnerMovingPoints;

	void FindEnemyInnerMovingPoints();

	// Left Moving Points
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TArray<class AActor*> LeftMovingPoints;

	void FindEnemyLeftMovingPoints();

	// Right Moving Points
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TArray<class AActor*> RightMovingPoints;

	void FindEnemyRightMovingPoints();

	// Bottom Moving Points
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TArray<class AActor*> BottomMovingPoints;

	void FindEnemyBottomMovingPoints();

	// Top Moving Points
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TArray<class AActor*> TopMovingPoints;

	void FindEnemyTopMovingPoints();

public: // Return Moving Points What You Want
	FVector GetRandomInnerMovingPoint();

	TArray<class AActor*> GetInnerMovingPoint() const { return InnerMovingPoints; }
	TArray<class AActor*> GetRandomPatrolMovingPoint();

	// Fixed Moving Point 리턴
	// 오버로딩을 통해 index를 명시해주면 해당 인덱스의 MP가 아니면 랜덤 MP를 반환하도록 한다.
	AActor* GetFixedMovingPoint();
	AActor* GetFixedMovingPoint(int index);
	// Left Moving Point
	AActor* GetLeftMovingPoint();
	AActor* GetLeftMovingPoint(int index);
	// Right Moving Point
	AActor* GetRightMovingPoint();
	AActor* GetRightMovingPoint(int index);
	// Bottom Moving Point
	AActor* GetBottomMovingPoint();
	AActor* GetBottomMovingPoint(int index);
	// Bottom Moving Point
	AActor* GetTopMovingPoint();
	AActor* GetTopMovingPoint(int index);

	int32 ExtractNumberFromName(const FString& Name, FString Prefix);
};
