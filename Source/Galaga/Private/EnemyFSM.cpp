// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "MyPlayer.h"
#include "EnemyBase.h"
#include "EnemyBullet.h"
#include "Engine/World.h"
#include "EnemyManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FindTarget();


}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// FSM 활성화 시 실행
	if (me->GetIsActiveFSM())
	{
		// 상태전환 시간 누적합
		currentTime += DeltaTime;
		// 주시 패턴
		switch (me->GetIsFocusPlayer())
		{
		case EEnemyFocus::Player:
			FocusPlayer();
			break;
		case EEnemyFocus::TargetMP:
			FocusTargetMP();
			break;
		case EEnemyFocus::Front:
			FocusFront();
			break;
		case EEnemyFocus::Back:
			FocusBack();
			break;
		case EEnemyFocus::Center:
			FocusCenter();
			break;
		case EEnemyFocus::PlayerOnce:
			FocusPlayerOnce();
			break;
		default:
			break;
		}

		// 상태 전환
		switch (mState)
		{
		case EEnemyState::IDLE:
			IdleState();
			break;
		case EEnemyState::MOVE:
			MoveState();
			break;
		case EEnemyState::ATTACK:
			AttackState();
			break;
		case EEnemyState::DIE:
			DieState();
			break;
		default:
			break;
		}
	}
}

void UEnemyFSM::IdleState()		// 대기 상태
{
	if (currentTime >= me->GetIdleDelayTime())
	{
		SetIsMoving(true);
		SetMoveState();
	}

}

void UEnemyFSM::MoveState()		// 움직임 상태
{
	// 움직임 패턴
	switch (me->GetMType())
	{
	case EEnemyType::Suiside:
		SuisideMove();
		break;
	case EEnemyType::Patrol:
		PatrolMove();
		break;
	case EEnemyType::Fixed:
		FixedMove();
		break;
	case EEnemyType::PassBy:
		PassByMove();
		break;
	case EEnemyType::Random:
		RandomMove();
		break;
	case EEnemyType::InOut:
		InOutMove();
		break;
	default:
		break;
	}

	if (currentTime >= me->GetEnemyAttackSpeed())
	{
		SetAttackState();
	}
}

void UEnemyFSM::AttackState()	// 공격 상태
{
	// 총알 발사 시 사운드
	me->FireSound();
	// 공격 패턴
	switch (me->GetMAttackType())
	{
	case EEnemyAttackType::Suiside:
		SetMoveState();
		break;
	case EEnemyAttackType::Front:
		FrontAttack();
		break;
	case EEnemyAttackType::Target:
		TargetAttack();
		break;
	case EEnemyAttackType::Spread:
		SpreadAttack();
		break;
	case EEnemyAttackType::Orbit:
		OrbitAttack();
		break;
	case EEnemyAttackType::Laser:
		me->laserEffect();
		me->GetWorldTimerManager().SetTimer(LaserTimer, this, &UEnemyFSM::LaserAttack, 2.0f, false);
		break;
	case EEnemyAttackType::Wave:
		WaveAttack();
		break;
	case EEnemyAttackType::Angle:
		AngleAttack();
	default:
		break;
	}

	SetMoveState();
	currentTime = 0.0f;
}

void UEnemyFSM::DieState()
{
	me->Destroy();
}



// 이동 패턴

// 자폭		- 플레이어에게 돌진
void UEnemyFSM::SuisideMove()
{
	FVector P0 = me->GetActorLocation();
	FVector dir = GetDirection();
	FVector vt = me->GetEnemySpeed() * GetWorld()->DeltaTimeSeconds * dir;

	FVector P = P0 + vt;
	me->SetActorRotation(dir.Rotation());
	me->SetActorLocation(P);
}
// 패트롤	- 특정 MovingPoint 반복
void UEnemyFSM::PatrolMove()
{

	FVector P0 = me->GetActorLocation();

	if (!isMoving)
	{
		if (me->GetEnemyTargetMovingPointIndex() == 0)
		{
			me->SetEnemyTargetMovingPointIndex(1);
		}
		else 
		{
			me->SetEnemyTargetMovingPointIndex(0);
		}

		FVector dir = me->GetDirectionToTargetMovingPoint(me->GetEnemyTargetMovingPointIndex());
		dir.Normalize();
		SetNowMovingDir(dir);

		SetIdleState();
		currentTime = 0.0f;
	}

	FVector vt = me->GetEnemySpeed() * GetWorld()->DeltaTimeSeconds * GetNowMovingDir();

	FVector P = P0 + vt;


	//me->SetActorRotation(FVector::BackwardVector.Rotation());
	me->SetActorLocation(P);
}
// 고정		- 소환 후 MovingPoint로 이동에서 움직이지 않음
void UEnemyFSM::FixedMove()
{
	if (GetIsMoving())
	{
		FVector P0 = me->GetActorLocation();

		FVector dir = me->GetDirectionToTargetMovingPoint(0);
		FVector vt = me->GetEnemySpeed() * GetWorld()->DeltaTimeSeconds * dir;

		FVector P = P0 + vt;

		me->SetActorLocation(P);
	}

}
// 통과		- 소환위치에서 목표 MovingPoint로 이동 후 소멸
void UEnemyFSM::PassByMove()
{
	FVector P0 = me->GetActorLocation();

	FVector dir = me->GetDirectionToTargetMovingPoint(0);
	FVector vt = me->GetEnemySpeed() * GetWorld()->DeltaTimeSeconds * dir;

	FVector P = P0 + vt;

	me->SetActorLocation(P);
}
// 랜덤		- 랜덤 MovingPoint로 계속해서 이동
void UEnemyFSM::RandomMove()
{
	FVector P0 = me->GetActorLocation();

	if (!isMoving)
	{
		SetIsMoving(true);
		FVector targetLocation = enemyManager->GetRandomInnerMovingPoint();
		FVector dir = targetLocation - me->GetActorLocation();
		dir.Normalize();
		SetNowMovingDir(dir);
	}

	FVector vt = me->GetEnemySpeed() * GetWorld()->DeltaTimeSeconds * GetNowMovingDir();

	FVector P = P0 + vt;


	me->SetActorLocation(P);
}

void UEnemyFSM::InOutMove()
{

	if (GetIsMoving())
	{
		FVector P0 = me->GetActorLocation();
		if (isIn)
		{
			FVector dir = me->GetDirectionToTargetMovingPoint(0);
			FVector vt = me->GetEnemySpeed() * GetWorld()->DeltaTimeSeconds * dir;

			FVector P = P0 + vt;

			me->SetActorLocation(P);
		}
		else {
			FVector dir = -me->GetActorForwardVector();
			dir.Normalize();

			FVector vt = me->GetEnemySpeed() * GetWorld()->DeltaTimeSeconds * dir;

			FVector P = P0 + vt;
			me->SetActorLocation(P);
		}

	}
	else {
		FTimerHandle MoveTimer;
		me->GetWorldTimerManager().SetTimer(MoveTimer, [this]() {
			SetIsMoving(true);
			}, (me->GetInOutDelayTime()+4.0f), false);

		FTimerHandle AttackTimer;
		me->GetWorldTimerManager().SetTimer(AttackTimer, [this]() {
			me->SetEnemyAttackSpeed(50.0f);
			}, me->GetInOutDelayTime(), false);


		FTimerHandle DieTimer;
		me->GetWorldTimerManager().SetTimer(DieTimer, [this]() {
			me->Destroy();
			}, (me->GetInOutDelayTime() + 8.0f), false);
	}

}

// 공격 패턴

// 전방 총알 발사
void UEnemyFSM::FrontAttack()
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEnemyBullet* bullet = me->bulletPool->SpawnPooledObject(me->GetActorLocation(), me->GetActorRotation());
	
}
// 플레이어에게 총알 발사
void UEnemyFSM::TargetAttack()
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector dir = GetDirection();
	dir.Normalize();
	FRotator rotation = dir.Rotation();

	AEnemyBullet* bullet = me->bulletPool->SpawnPooledObject(me->GetActorLocation(), rotation);
}
// 원을 그리며 360도로 확산 발사
void UEnemyFSM::SpreadAttack()
{
	if (!GetIsMoving())
	{
		static double standardAngle = 0;
		
		// 총알 소환 Location
		double angleRad = FMath::DegreesToRadians(standardAngle);
		FVector bulletSpawnLocation = me->GetActorLocation() + FVector(sin(angleRad), cos(angleRad), 0);
		// 총알 소환 Rotation
		FRotator bulletSpawnRotation = me->GetActorRotation();
		bulletSpawnRotation.Yaw -= standardAngle;

		AEnemyBullet* bullet = me->bulletPool->SpawnPooledObject(bulletSpawnLocation, bulletSpawnRotation);

		standardAngle += 10;
	}

}
// 360도로 원형으로 총알을 발사
void UEnemyFSM::OrbitAttack()
{
	// 각도
	double angleBetweenBullets = 360/60;

	for (int i = 0; i < 60; i++)
	{
		// 현재각도
		double angle = i * angleBetweenBullets;
		// 라디안 변환
		double angleInRadians = FMath::DegreesToRadians(angle);

		FRotator bulletSpawnRotation = me->GetActorRotation();
		bulletSpawnRotation.Yaw -= angle;


		// 총알이 나갈 위치를 계산합니다.
		FVector bulletSpawnLocation = me->GetActorLocation() + FVector(sin(angleInRadians), cos(angleInRadians), 0) * 300;

		AEnemyBullet* bullet = me->bulletPool->SpawnPooledObject(bulletSpawnLocation, bulletSpawnRotation);

	}

}
// Sweep By Single Channel을 사용하여 즉발형 공격 구현
void UEnemyFSM::LaserAttack()
{
	FVector StartPos = me->GetActorLocation();
	FVector EndPos = StartPos + me->GetActorForwardVector() * 4500.f;

	FHitResult HitResult;

	bool Result = GetWorld()->SweepSingleByChannel
	(
		HitResult,
		StartPos,
		EndPos,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeBox(FVector(60,60,60))
	);

	if (Result && HitResult.GetActor())
	{
		if (HitResult.GetActor()->ActorHasTag("Player"))
		{
			
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), 1, NULL, NULL, NULL);
		}
	}
}
// 전방 기준 Max Angle을 Bullet Count만큼 분할하여 총알 발사
void UEnemyFSM::AngleAttack()
{
	double angleBetweenBullets = 130.0/me->GetBulletCount();
	double startAngle = 65.0;

	for (int i = 0; i < me->GetBulletCount(); i++)
	{
		double angle = startAngle - i * angleBetweenBullets;
		double angleInRadians = FMath::DegreesToRadians(angle);


		FRotator bulletRotation = me->GetActorRotation();
		bulletRotation.Yaw += angle;

		FVector spawnLocation = me->GetActorLocation() + FVector(cos(angleInRadians), sin(angleInRadians), 0) * 200;

		AEnemyBullet* bullet = me->bulletPool->SpawnPooledObject(spawnLocation, bulletRotation);
	}
}
// Sin 그래프 모양으로 총알이 발사
void UEnemyFSM::WaveAttack()
{
	if (!GetIsMoving())
	{
		// 현재 각도
		static double angle = 0;
		// 파동의 주기
		double waveLength = 360.0;
		// 파동의 높이
		double amplitude = 500.0;
		// 각도를 라디안으로 변환
		double angleInRadians = FMath::DegreesToRadians(angle);

		FRotator bulletSpawnRotation = me->GetActorRotation();

		// 총알이 나갈 위치를 계산합니다.
		// 삼각함수에 값을 곱해 진폭을 조절하고, 평행이동으로 2쌍의 파동이 나가도록 구현
		FVector bulletSpawnLocationLeft = me->GetActorLocation() + FVector(0, (FMath::Sin(angleInRadians) * amplitude)+me->GetWaveRange(), 0);
		FVector bulletSpawnLocationRight = me->GetActorLocation() + FVector(0, (FMath::Sin(angleInRadians) * amplitude)- me->GetWaveRange(), 0);

		// 각도 설정
		AEnemyBullet* bulletLeft = me->bulletPool->SpawnPooledObject(bulletSpawnLocationLeft, bulletSpawnRotation);
		AEnemyBullet* bulletRight = me->bulletPool->SpawnPooledObject(bulletSpawnLocationRight, bulletSpawnRotation);

		// 각도를 업데이트합니다.
		angle += 5;
		if (angle >= waveLength)
		{
			angle -= waveLength;
		}
	}
}

// 대상 찾기
void UEnemyFSM::FindTarget()
{
	auto target = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPlayer::StaticClass());
	if (target)
	{
		attackTarget = Cast<AMyPlayer>(target);
	}

	me = Cast<AEnemyBase>(GetOwner());

	auto emTemp = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyManager::StaticClass());

	if (emTemp)
	{
		enemyManager = Cast<AEnemyManager>(emTemp);
	}

	if (attackTarget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Attack Target"));
	}

	if (me == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No me"));
	}

	if (emTemp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Enemy Manager"));
	}
}
// 방향 계산
FVector UEnemyFSM::GetDirection()
{
	if (attackTarget != nullptr)
	{
		FVector dir = attackTarget->GetActorLocation() - me->GetActorLocation();
		dir.Normalize();
		return dir;
	}
	return FVector::ZeroVector;
}


void UEnemyFSM::FocusPlayer()
{
	FVector LookPlayer = GetDirection();

	me->SetActorRotation(LookPlayer.Rotation());
}

void UEnemyFSM::FocusTargetMP()
{
	FVector TargetMPDirection = me->GetDirectionToTargetMovingPoint(me->GetEnemyTargetMovingPointIndex());
	FRotator TargetMPRotation = TargetMPDirection.Rotation();
	me->SetActorRotation(TargetMPRotation);
}

void UEnemyFSM::FocusCenter()
{
	FVector CenterLocation = FVector(0, 0, 0);
	FVector CenterDirection = (CenterLocation - me->GetActorLocation()).GetSafeNormal();
	FRotator CenterRotation = CenterDirection.Rotation();
	me->SetActorRotation(CenterRotation);
}

void UEnemyFSM::FocusFront()
{
	me->SetActorRotation(FVector::BackwardVector.Rotation());
}

void UEnemyFSM::FocusBack()
{
	me->SetActorRotation(FVector::ForwardVector.Rotation());
}

void UEnemyFSM::FocusPlayerOnce()
{
	if (GetIsMoving())
	{
		FVector LookPlayer = GetDirection();

		me->SetActorRotation(LookPlayer.Rotation());
	}
}