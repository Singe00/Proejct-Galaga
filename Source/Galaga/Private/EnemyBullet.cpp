// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletBodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BulletBodyCollision"));
	BulletBodyCollision->SetRelativeScale3D(FVector(1, 0.5f, 0.25f));
	RootComponent = BulletBodyCollision;

	BulletBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletBody"));
	BulletBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BulletBody->SetupAttachment(BulletBodyCollision);

	ConstructorHelpers::FObjectFinder<UStaticMesh>BulletBodyMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (BulletBodyMesh.Succeeded())
	{
		BulletBody->SetStaticMesh(BulletBodyMesh.Object);
		BulletBody->SetRelativeScale3D(FVector(1, 0.5f, 0.25f));
		BulletBody->SetRelativeLocation(FVector(0, 0, -12.5f));
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_BulletBody(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/Instance/M_EnemyBullet_Inst.M_EnemyBullet_Inst'"));
	if (MI_BulletBody.Succeeded())
	{
		BulletBody->SetMaterial(0, MI_BulletBody.Object);
	}


	BulletBodyCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	BulletBodyCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnComponentBeginOverlap);

}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsActive())
	{
		BulletForwardMove(DeltaTime);
	}
}


void AEnemyBullet::BulletForwardMove(float DeltaTime)
{
	FVector P = GetActorLocation() + DeltaTime * BulletSpeed * GetActorForwardVector();
	SetActorLocation(P);
}

void AEnemyBullet::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player") && IsActive())
	{
		Deactivate();
		UGameplayStatics::ApplyDamage(OtherActor, 1, NULL, NULL, NULL);
	}
	else if (OtherActor->ActorHasTag("Edge"))
	{
		Deactivate();
	}
}

void AEnemyBullet::Deactivate()
{
	SetActive(false);
	SetActorLocation(FVector(2500, 2500, 0));
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnEnemyPooledBulletDespawn.Broadcast(this);
}

void AEnemyBullet::SetActive(bool IsActive)
{
	Active = IsActive;
	SetActorHiddenInGame(!IsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &AEnemyBullet::Deactivate, LifeSpan, false);
}

void AEnemyBullet::SetLifeSpan(float LifeTime)
{
	LifeSpan = LifeTime;
}

void AEnemyBullet::SetPoolIndex(int Index)
{
	PoolIndex = Index;
}

bool AEnemyBullet::IsActive()
{
	return Active;
}

int AEnemyBullet::GetPoolIndex()
{
	return PoolIndex;
}

