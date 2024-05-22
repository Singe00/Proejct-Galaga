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

	// 공격 입력이 들어오면
	if (isAttack)
	{
		// 총알 발사
		FireBullet(DeltaTime);
	}
}

void UPlayerAttack::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	// 공격 시작 바인딩
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPlayerAttack::Fire);
	// 공격 중단 바인딩
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &UPlayerAttack::Fire);
	// 필살기 사용 바인딩
	PlayerInputComponent->BindAction(TEXT("Ult"), IE_Released, this, &UPlayerAttack::Ultimate);
}

void UPlayerAttack::Fire()
{
	if (!isAttack) // Pressed 시
	{
		isAttack = true; // 공격 중
	}
	else // Released 시
	{
		isAttack = false; // 공격 중단
	}
}

void UPlayerAttack::Ultimate()
{
	// 필살기 중복 사용 방지
	if (!GetIsUlt())
	{
		SetIsUlt(true);

		// 필살기 이펙트 효과 함수, 블루프린트로 구현
		me->PlayerUltEffect();

		// 예외처리
		if (me != nullptr)
		{
			// 필살기 공격 함수 실행 0.1초마다 반복 실행
			GetWorld()->GetTimerManager().SetTimer(FireUltTimer, this, &UPlayerAttack::FireUlt, 0.1f, true);
			// 필살기 중단 함수 실행 3초 후 호출되어 공격 함수 중단
			FTimerHandle UltTimer;
			GetWorld()->GetTimerManager().SetTimer(UltTimer, this, &UPlayerAttack::StopUlt, 3.0f, false);
		}
	}
}

void UPlayerAttack::FireBullet(float DeltaTime)
{
	// 공격 속도 누적합
	AttackSpeedTimer += DeltaTime;

	// 공격 속도 시간 도달 시
	if (AttackSpeedTimer >= AttackSpeed)
	{
		// 사운드 작업
		me->FireSound();

		// 기존 Bullet Factory 소스 코드
		//FActorSpawnParameters param;
		//param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//APlayerBullet* bullet = GetWorld()->SpawnActor<APlayerBullet>(BulletFactory, GetActorLocation(), FRotator::ZeroRotator, param);

		// Object Pooling 코드
		me->PlayerBulletPool->SpawnPlayerPooledBullet();

		// 공격 속도 타이머 초기화
		AttackSpeedTimer = 0.0f;
	}
}

void UPlayerAttack::FireUlt()
{
	// 시작 위치
	FVector StartPos = me->GetActorLocation() + FVector(200.0f, 0, 0);
	// 끝 위치
	FVector EndPos = StartPos + me->GetActorForwardVector() * 4500.f;

	// 충돌한 대상 정보를 담을 HitResults 배열
	TArray<FHitResult> HitResults;

	// 충돌 설정 파라미터
	FCollisionQueryParams CollisionParams;
	// 본인은 제외한다.
	CollisionParams.AddIgnoredActor(me);

	// 시작, 끝 위치로 ECC_GameTraceChannel2 채널의 SweepMultiByChannel을 발사
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

	// 충돌이 유효하면
	if (Result)
	{
		// 모든 충돌 대상 검사
		for (FHitResult HitResult : HitResults)
		{
			// 충돌 대상이 액터이고
			if (HitResult.GetActor())
			{
				// Enemy 태그를 가지고 있다면
				if (HitResult.GetActor()->ActorHasTag("Enemy"))
				{
					// 공격력만큼 ApplyDamage() 적용
					UGameplayStatics::ApplyDamage(HitResult.GetActor(), 1, NULL, NULL, NULL);

				}// EnemyBullet 태그를 가지고 있다면
				else if (HitResult.GetActor()->ActorHasTag("EnemyBullet"))
				{
					// Pooling 총알을 역소환으로 비활성화
					AEnemyBullet* bullet = Cast<AEnemyBullet>(HitResult.GetActor());
					bullet->Deactivate();
				}
			}
		}
	}
}
void UPlayerAttack::StopUlt()
{
	// 루프 중인 필살기 타이머 클리어로 중단
	GetWorld()->GetTimerManager().ClearTimer(FireUltTimer);
}

void UPlayerAttack::IncreaseAttackSpeed()
{
	// 공격 속도 감소 > 빨라짐
	if (this->AttackSpeed > 0.2)
	{
		this->AttackSpeed -= 0.025f;
	}
}

void UPlayerAttack::IncreaseBulletDamage()
{
	// 공격력 증가
	if (this->AttackDamage < 2)
	{
		this->AttackDamage += 0.25f;
	}
}

void UPlayerAttack::IncreaseBulletCount()
{
	// 총알 개수 증가
	if (this->BulletCount < 9)
	{
		this->BulletCount += 2;
		// 총알 발사 최대 각도 계산
		this->MaxAngle = 5.0f * (BulletCount - 1);
	}
}