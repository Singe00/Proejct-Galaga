// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/SphereComponent.h"
#include "PlayerAttack.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerBullet::APlayerBullet()
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

	ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_BulletBody(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/Instance/M_PlayerBullet_Inst.M_PlayerBullet_Inst'"));
	if (MI_BulletBody.Succeeded())
	{
		BulletBody->SetMaterial(0, MI_BulletBody.Object);
	}

	BulletBodyCollision->SetCollisionProfileName(TEXT("BlockAll"));
	BulletBodyCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnComponentBeginOverlap);

}

// Called when the game starts or when spawned
void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsActive())
	{
		BulletForwardMove(DeltaTime);
	}
}

void APlayerBullet::BulletForwardMove(float DeltaTime)
{
	FVector P = GetActorLocation() + DeltaTime * BulletSpeed * GetActorForwardVector();
	SetActorLocation(P);
}

void APlayerBullet::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		auto playerTemp = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPlayer::StaticClass());
		if (playerTemp)
		{
			AMyPlayer* player = Cast<AMyPlayer>(playerTemp);
			if (player != nullptr)
			{
				UGameplayStatics::ApplyDamage(OtherActor, player->PlayerAttack->GetAttackDamage(), NULL, NULL, NULL);
				Deactivate();
			}
		}
	}
	else if (OtherActor->ActorHasTag("Edge"))
	{
		Deactivate();
	}
}

void APlayerBullet::Deactivate()
{
	SetActive(false);
	SetActorLocation(FVector(-2500,-2500,0));
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPlayerPooledBulletDespawn.Broadcast(this);
}

void APlayerBullet::SetActive(bool IsActive)
{
	Active = IsActive;
	SetActorHiddenInGame(!IsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APlayerBullet::Deactivate, LifeSpan, false);
}

void APlayerBullet::SetLifeSpan(float LifeTime)
{
	LifeSpan = LifeTime;
}

void APlayerBullet::SetPoolIndex(int Index)
{
	PoolIndex = Index;
}

bool APlayerBullet::IsActive()
{
	return Active;
}

int APlayerBullet::GetPoolIndex()
{
	return PoolIndex;
}

