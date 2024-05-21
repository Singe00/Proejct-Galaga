// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Damage,
	Speed,
	Count,
	Boom,
	Hp,
};

UCLASS()
class GALAGA_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ChangeMI")
	void ChangeType();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="ItemEffect")
	void ItemEffect(EItemType type);

private: // Components

	UPROPERTY(VisibleAnywhere,Category=ItemBody)
	class UBoxComponent* ItemBodyCollision;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=ItemBody,meta=(AllowPrivateAccess = true))
	class UStaticMeshComponent* ItemBody;


private:

	UFUNCTION()
	void OnComponentBeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	EItemType itemType;

	void ItemMove(float DeltaTime);

	FVector Direction = FVector(1, 1, 0);
	FVector TargetScale = FVector(2,2,2);
	bool isSmall = true;

	int boundCount = 20;

	FTimerHandle ChangeTypeTimerHandle;
	FTimerHandle ChangeScaleTimerHandle;

	void ChangeScale();
	void SetTargetScale();

	void DestroyItem();
};
