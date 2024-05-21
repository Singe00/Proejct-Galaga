// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttack.h"
#include "EnemyBullet.h"
#include "Kismet/GameplayStatics.h"

UPlayerAttack::UPlayerAttack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerAttack::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (isAttack)
	{
		FireBullet(DeltaTime);
	}
}

void UPlayerAttack::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPlayerAttack::Fire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &UPlayerAttack::Fire);

	PlayerInputComponent->BindAction(TEXT("Ult"), IE_Released, this, &UPlayerAttack::Ultimate);
}

void UPlayerAttack::Fire()
{
	if (!isAttack)
	{
		isAttack = true;
	}
	else {
		isAttack = false;
	}
}

void UPlayerAttack::Ultimate()
{
	if (!GetIsUlt())
	{
		me->PlayerUltEffect();
		SetIsUlt(true);

		if (me != nullptr)
		{

			GetWorld()->GetTimerManager().SetTimer(FireUltTimer, this, &UPlayerAttack::FireUlt, 0.1f, true);

			FTimerHandle UltTimer;
			GetWorld()->GetTimerManager().SetTimer(UltTimer, this, &UPlayerAttack::StopUlt, 3.0f, false);
		}
	}
}

void UPlayerAttack::FireBullet(float DeltaTime)
{

	AttackSpeedTimer += DeltaTime;

	if (AttackSpeedTimer >= AttackSpeed)
	{
		me->FireSound();
		//FActorSpawnParameters param;
		//param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//APlayerBullet* bullet = GetWorld()->SpawnActor<APlayerBullet>(BulletFactory, GetActorLocation(), FRotator::ZeroRotator, param);

		me->PlayerBulletPool->SpawnPlayerPooledBullet();

		AttackSpeedTimer = 0.0f;
	}
}

void UPlayerAttack::FireUlt()
{
	FVector StartPos = me->GetActorLocation() + FVector(200.0f, 0, 0);
	FVector EndPos = StartPos + me->GetActorForwardVector() * 4500.f;

	TArray<FHitResult> HitResults;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(me);

	bool Result = GetWorld()->SweepMultiByChannel
	(
		HitResults,
		StartPos,
		EndPos,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeBox(FVector(180, 180, 180)),
		CollisionParams
	);

	// Draw the trace path
	//DrawDebugBox(GetWorld(), StartPos, FVector(180, 180, 180), FQuat::Identity, FColor::Green, false, 2.0f);
	//DrawDebugBox(GetWorld(), EndPos, FVector(180, 180, 180), FQuat::Identity, FColor::Red, false, 2.0f);
	//DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Blue, false, 2.0f, 0, 5.0f);


	if (Result)
	{
		for (FHitResult HitResult : HitResults)
		{
			if (HitResult.GetActor())
			{
				if (HitResult.GetActor()->ActorHasTag("Enemy"))
				{

					UGameplayStatics::ApplyDamage(HitResult.GetActor(), 1, NULL, NULL, NULL);

					//DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(60, 60, 60), FQuat::Identity, FColor::Yellow, false, 2.0f);
				}
				else if (HitResult.GetActor()->ActorHasTag("EnemyBullet"))
				{
					AEnemyBullet* bullet = Cast<AEnemyBullet>(HitResult.GetActor());
					bullet->Deactivate();
				}
			}
		}
	}
}
void UPlayerAttack::StopUlt()
{
	GetWorld()->GetTimerManager().ClearTimer(FireUltTimer);
}

void UPlayerAttack::IncreaseAttackSpeed()
{
	if (this->AttackSpeed > 0.2)
	{
		this->AttackSpeed -= 0.025f;
	}
}

void UPlayerAttack::IncreaseBulletDamage()
{
	if (this->AttackDamage < 2)
	{
		this->AttackDamage += 0.25f;
	}
}

void UPlayerAttack::IncreaseBulletCount()
{
	if (this->BulletCount < 9)
	{
		this->BulletCount += 2;
		this->MaxAngle = 5.0f * (BulletCount - 1);
	}
}