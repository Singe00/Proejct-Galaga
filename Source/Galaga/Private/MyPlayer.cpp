// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "PlayerBullet.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"
#include "EnemyBullet.h"
#include "EnemyBulletPool.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerBodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerBodyCollision"));
	RootComponent = PlayerBodyCollision;

	PlayerBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerBody"));
	PlayerBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayerBody->SetRelativeScale3D(FVector(0.02f, 0.02f, 0.02f));
	PlayerBody->SetupAttachment(PlayerBodyCollision);

	ConstructorHelpers::FObjectFinder<UStaticMesh>PlayerBodyMesh(TEXT("/Script/Engine.StaticMesh'/Game/spaceship-cb2/source/StaticMesh.StaticMesh'"));

	if (PlayerBodyMesh.Succeeded())
	{
		PlayerBody->SetStaticMesh(PlayerBodyMesh.Object);
	}

	PlayerBodyCollision->SetCollisionProfileName(TEXT("BlockAll"));

	PlayerBulletPool = CreateDefaultSubobject<UPlayerBulletPool>(TEXT("PlayerBulletPool"));

	PlayerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
	PlayerAttack = CreateDefaultSubobject<UPlayerAttack>(TEXT("PlayerAttack"));
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	FVector AlignLocation = GetActorLocation();
	AlignLocation.Z = 0;
	SetActorLocation(AlignLocation);

	GameManager = Cast<UGameManager>(GetGameInstance());

	LoadPlayerStat();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (isBoomCool)
	{
		coolTime -= DeltaTime;
	}
	else 
	{
		coolTime = 5.0f;
	}

	if (PlayerAttack->GetIsUlt())
	{
		UltCoolTime -= DeltaTime;
		if (UltCoolTime <= 0)
		{
			PlayerAttack->SetIsUlt(false);
			UltCoolTime = 20.0f;
		}
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerMove->SetupInputBinding(PlayerInputComponent);
	PlayerAttack->SetupInputBinding(PlayerInputComponent);



	PlayerInputComponent->BindAction(TEXT("Boom"), IE_Pressed, this, &AMyPlayer::Boom);
	PlayerInputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &AMyPlayer::Pause);


}



void AMyPlayer::Boom()
{
	if (PlayerBoomCount > 0 && !isBoomCool)
	{
		PlayerBoomEffect();

		isBoomCool = true;

		PlayerBoomCount -= 1;

		auto pool = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyBulletPool::StaticClass());

		if (pool)
		{
			AEnemyBulletPool* enemyBulletPool = Cast<AEnemyBulletPool>(pool);

			if (enemyBulletPool != nullptr)
			{
				enemyBulletPool->DeactiveAllBullets();
			}
		}

		FTimerHandle CanUseBoom;
		GetWorldTimerManager().SetTimer(CanUseBoom, this, &AMyPlayer::setCanUseBoom, 5.0f, false);
	}

}


float AMyPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!isHit)
	{
		isHit = true;

		this->PlayerHp -= damage;
		if (PlayerMove)
		{
			DestroyingPlayer();
		}


		if (PlayerHp <= 0)
		{
			PlayerMove->DestroyComponent();

			PlayerBodyCollision->SetSimulatePhysics(true);
			PlayerBodyCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			PlayerBodyCollision->SetMassOverrideInKg();

			FVector ImpulseDirection = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), -1);
			ImpulseDirection.Normalize();

			PlayerBodyCollision->AddForce(ImpulseDirection * 100000.0f);
		}

		FTimerHandle isHitTime;
		GetWorldTimerManager().SetTimer(isHitTime, this, &AMyPlayer::setCanHit,2.0f,false);
	}


	return 0.0f;
}



void AMyPlayer::LoadPlayerStat()
{
	FPlayerStats loadStat = GameManager->LoadPlayerStat();

	SetPlayerHp(loadStat.PlayerHp);
	SetBoomCount(loadStat.BoomCount);
	PlayerAttack->SetAttackDamage(loadStat.AttackDamage);
	PlayerAttack->SetAttackSpeed(loadStat.AttackSpeed);
	PlayerAttack->SetBulletCount(loadStat.BulletCount);
	PlayerAttack->SetMaxAngle(loadStat.MaxAngle);
}

void AMyPlayer::FireSound_Implementation()
{
}

void AMyPlayer::IncreasePlayerHp()
{
	if (this->PlayerHp < 3)
	{
		this->PlayerHp += 1;
	}
}

void AMyPlayer::IncreasePlayerBoomCount()
{
	if (this->PlayerBoomCount < 3)
	{
		this->PlayerBoomCount += 1;
	}
}



void AMyPlayer::DestroyingPlayer_Implementation()
{
}

void AMyPlayer::PlayerBoomEffect_Implementation()
{
}

void AMyPlayer::PlayerUltEffect_Implementation()
{
}

void AMyPlayer::Pause_Implementation()
{

}
