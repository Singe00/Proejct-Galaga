// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.h"
#include "EnemyMovingPoint.generated.h"

UCLASS()
class GALAGA_API AEnemyMovingPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyMovingPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = PointBody)
	class USphereComponent* PointBodyCollision;
	UPROPERTY(VisibleAnywhere, Category = PointBody)
	class UStaticMeshComponent* PointBody;

	FVector GetMovingPointLocation();

private:
	UFUNCTION()
	void OnComponentBeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool CheckTargetMovingPoint(AEnemyBase* enemy);
};
