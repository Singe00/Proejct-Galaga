// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "EnemyFSM.h"
#include "EnemyManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyBodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	EnemyBodyCollision->SetRelativeScale3D(FVector(2, 2, 2));
	RootComponent = EnemyBodyCollision;

	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyBody"));
	EnemyBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EnemyBody->SetupAttachment(EnemyBodyCollision);

	EnemyBodyCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	EnemyBodyCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnComponentBeginOverlap);

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GameManager = Cast<UGameManager>(GetGameInstance());

	FVector AlignLocation = GetActorLocation();
	AlignLocation.Z = 0;
	SetActorLocation(AlignLocation);

	auto bulletPoolObject = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyBulletPool::StaticClass());
	bulletPool = Cast<AEnemyBulletPool>(bulletPoolObject);

	if (isActiveByTime)
	{
		FTimerHandle ActiveTimerHandle;
		GetWorldTimerManager().SetTimer(ActiveTimerHandle, this, &AEnemyBase::SetIsActiveFSM, GetFSMActiveTime(), false);
	}

}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isActiveByTime && !isActiveFSM)
	{
		if (GetDependencyEnemy()->IsPendingKill())
		{
			SetIsActiveFSM();
		}
	}
}

void AEnemyBase::SetIsActiveFSM_Implementation()
{
	isActiveFSM = true;
}

void AEnemyBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 1, NULL, NULL, NULL);
		if (GetMAttackType() == EEnemyAttackType::Suiside)
		{
			this->Destroy();
		}
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	this->EnemyHp -= damage;

	DestroyingEnemy();

	if (this->EnemyHp <= 0)
	{
		if (fsm)
		{
			fsm->DestroyComponent();
		}
		
		if (isSpawnItemWhenDie)
		{
			isSpawnItemWhenDie = false;
			FTransform spawnTransform = FTransform(FVector::ForwardVector.Rotation(), GetActorLocation(), FVector(2, 2, 2));
			GetWorld()->SpawnActor<AItem>(SpawnItem, spawnTransform);
		}
		GameManager->AddScorePoint(scorePoint);

		EnemyBodyCollision->SetSimulatePhysics(true);
		EnemyBodyCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		EnemyBodyCollision->SetCollisionProfileName("BlockAll");
		EnemyBodyCollision->SetMassOverrideInKg();


		FVector ImpulseDirection = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), -1);
		ImpulseDirection.Normalize();

		EnemyBodyCollision->AddForce(ImpulseDirection * 100000.0f); 
		EnemyBodyCollision->AddTorqueInDegrees(FVector(0,0,1) * 1000000.0f); // 회전력 적용


		//this->Destroy();
	}

	return 0.0f;
}

void AEnemyBase::SetEnemyBodyMesh(FString EnemyBodyPath)
{
	const TCHAR* MeshPath = *EnemyBodyPath;
	ConstructorHelpers::FObjectFinder<UStaticMesh>EnemyBodyMesh(MeshPath);

	if (EnemyBodyMesh.Succeeded())
	{
		EnemyBody->SetStaticMesh(EnemyBodyMesh.Object);
		EnemyBody->SetRelativeScale3D(FVector(0.02f, 0.02f, 0.02f));
	}
}

void AEnemyBase::SpawnPlayerItem()
{
}

FVector AEnemyBase::GetDirectionToTargetMovingPoint(float index)
{
	if (TargetMovingPoints[index] != nullptr)
	{
		FVector dir = TargetMovingPoints[index]->GetActorLocation() - GetActorLocation();
		dir.Normalize();
		return dir;
	}
	return FVector(1,1,1);
}

void AEnemyBase::FireSound_Implementation()
{
}

void AEnemyBase::DestroyingEnemy_Implementation()
{

}

void AEnemyBase::laserEffect_Implementation()
{
}
