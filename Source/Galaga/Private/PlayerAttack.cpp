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

	// ���� �Է��� ������
	if (isAttack)
	{
		// �Ѿ� �߻�
		FireBullet(DeltaTime);
	}
}

void UPlayerAttack::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	// ���� ���� ���ε�
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPlayerAttack::Fire);
	// ���� �ߴ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &UPlayerAttack::Fire);
	// �ʻ�� ��� ���ε�
	PlayerInputComponent->BindAction(TEXT("Ult"), IE_Released, this, &UPlayerAttack::Ultimate);
}

void UPlayerAttack::Fire()
{
	if (!isAttack) // Pressed ��
	{
		isAttack = true; // ���� ��
	}
	else // Released ��
	{
		isAttack = false; // ���� �ߴ�
	}
}

void UPlayerAttack::Ultimate()
{
	// �ʻ�� �ߺ� ��� ����
	if (!GetIsUlt())
	{
		SetIsUlt(true);

		// �ʻ�� ����Ʈ ȿ�� �Լ�, �������Ʈ�� ����
		me->PlayerUltEffect();

		// ����ó��
		if (me != nullptr)
		{
			// �ʻ�� ���� �Լ� ���� 0.1�ʸ��� �ݺ� ����
			GetWorld()->GetTimerManager().SetTimer(FireUltTimer, this, &UPlayerAttack::FireUlt, 0.1f, true);
			// �ʻ�� �ߴ� �Լ� ���� 3�� �� ȣ��Ǿ� ���� �Լ� �ߴ�
			FTimerHandle UltTimer;
			GetWorld()->GetTimerManager().SetTimer(UltTimer, this, &UPlayerAttack::StopUlt, 3.0f, false);
		}
	}
}

void UPlayerAttack::FireBullet(float DeltaTime)
{
	// ���� �ӵ� ������
	AttackSpeedTimer += DeltaTime;

	// ���� �ӵ� �ð� ���� ��
	if (AttackSpeedTimer >= AttackSpeed)
	{
		// ���� �۾�
		me->FireSound();

		// ���� Bullet Factory �ҽ� �ڵ�
		//FActorSpawnParameters param;
		//param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//APlayerBullet* bullet = GetWorld()->SpawnActor<APlayerBullet>(BulletFactory, GetActorLocation(), FRotator::ZeroRotator, param);

		// Object Pooling �ڵ�
		me->PlayerBulletPool->SpawnPlayerPooledBullet();

		// ���� �ӵ� Ÿ�̸� �ʱ�ȭ
		AttackSpeedTimer = 0.0f;
	}
}

void UPlayerAttack::FireUlt()
{
	// ���� ��ġ
	FVector StartPos = me->GetActorLocation() + FVector(200.0f, 0, 0);
	// �� ��ġ
	FVector EndPos = StartPos + me->GetActorForwardVector() * 4500.f;

	// �浹�� ��� ������ ���� HitResults �迭
	TArray<FHitResult> HitResults;

	// �浹 ���� �Ķ����
	FCollisionQueryParams CollisionParams;
	// ������ �����Ѵ�.
	CollisionParams.AddIgnoredActor(me);

	// ����, �� ��ġ�� ECC_GameTraceChannel2 ä���� SweepMultiByChannel�� �߻�
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

	// �浹�� ��ȿ�ϸ�
	if (Result)
	{
		// ��� �浹 ��� �˻�
		for (FHitResult HitResult : HitResults)
		{
			// �浹 ����� �����̰�
			if (HitResult.GetActor())
			{
				// Enemy �±׸� ������ �ִٸ�
				if (HitResult.GetActor()->ActorHasTag("Enemy"))
				{
					// ���ݷ¸�ŭ ApplyDamage() ����
					UGameplayStatics::ApplyDamage(HitResult.GetActor(), 1, NULL, NULL, NULL);

				}// EnemyBullet �±׸� ������ �ִٸ�
				else if (HitResult.GetActor()->ActorHasTag("EnemyBullet"))
				{
					// Pooling �Ѿ��� ����ȯ���� ��Ȱ��ȭ
					AEnemyBullet* bullet = Cast<AEnemyBullet>(HitResult.GetActor());
					bullet->Deactivate();
				}
			}
		}
	}
}
void UPlayerAttack::StopUlt()
{
	// ���� ���� �ʻ�� Ÿ�̸� Ŭ����� �ߴ�
	GetWorld()->GetTimerManager().ClearTimer(FireUltTimer);
}

void UPlayerAttack::IncreaseAttackSpeed()
{
	// ���� �ӵ� ���� > ������
	if (this->AttackSpeed > 0.2)
	{
		this->AttackSpeed -= 0.025f;
	}
}

void UPlayerAttack::IncreaseBulletDamage()
{
	// ���ݷ� ����
	if (this->AttackDamage < 2)
	{
		this->AttackDamage += 0.25f;
	}
}

void UPlayerAttack::IncreaseBulletCount()
{
	// �Ѿ� ���� ����
	if (this->BulletCount < 9)
	{
		this->BulletCount += 2;
		// �Ѿ� �߻� �ִ� ���� ���
		this->MaxAngle = 5.0f * (BulletCount - 1);
	}
}