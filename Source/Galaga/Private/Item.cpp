// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "MyPlayer.h"
#include "PlayerAttack.h"
#include "Components/BoxComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemBodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemBodyCollision"));
	RootComponent = ItemBodyCollision;
	ItemBodyCollision->SetRelativeScale3D(FVector(2, 2, 2));
	ItemBodyCollision->SetCollisionProfileName("OverlapAll");

	ItemBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemBody"));
	ItemBody->SetupAttachment(ItemBodyCollision);
	ItemBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemBody->SetRelativeRotation(FRotator(0, 90, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>ItemBodyMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube'"));

	if (ItemBodyMesh.Succeeded())
	{
		ItemBody->SetStaticMesh(ItemBodyMesh.Object);
	}

	ItemBodyCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnComponentBeginOverlap);


}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ChangeTypeTimerHandle, this, &AItem::ChangeType, 2.5f, true);
	GetWorldTimerManager().SetTimer(ChangeScaleTimerHandle, this, &AItem::SetTargetScale, 0.5f, true);

	int dirX = FMath::RandRange(0, 1) == 0 ? -1 : 1;
	int dirY = FMath::RandRange(0, 1) == 0 ? -1 : 1;

	Direction = FVector(dirX, dirY, 0);

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChangeScale();
	ItemMove(DeltaTime);
}

void AItem::ItemEffect_Implementation(EItemType type)
{
}

void AItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Player"))
	{
		AMyPlayer* player = Cast<AMyPlayer>(OtherActor);

		if (player)
		{
			ItemEffect(itemType);

			switch (itemType)
			{
			case EItemType::Damage:
				player->PlayerAttack->IncreaseBulletDamage();
				break;
			case EItemType::Speed:
				player->PlayerAttack->IncreaseAttackSpeed();
				break;
			case EItemType::Count:
				player->PlayerAttack->IncreaseBulletCount();
				break;
			case EItemType::Boom:
				player->IncreasePlayerBoomCount();
				break;
			case EItemType::Hp:
				player->IncreasePlayerHp();
				break;
			default:
				break;
			}


			DestroyItem();
		}
	}
	else if (OtherActor->ActorHasTag("Edge"))
	{
		if (boundCount > 0)
		{
			if (OtherComp->ComponentHasTag("TopEdge"))
			{
				int rand = FMath::RandRange(0, 1) == 0 ? -1 : 1;
				Direction = FVector(-Direction.X, rand, 0);
			}
			else if (OtherComp->ComponentHasTag("BottomEdge"))
			{
				int rand = FMath::RandRange(0, 1) == 0 ? -1 : 1;
				Direction = FVector(-Direction.X, rand, 0);

			}
			else if (OtherComp->ComponentHasTag("LeftEdge"))
			{
				int rand = FMath::RandRange(0, 1) == 0 ? -1 : 1;

				Direction = FVector(rand, -Direction.Y, 0);
			}
			else if (OtherComp->ComponentHasTag("RightEdge"))
			{
				int rand = FMath::RandRange(0, 1) == 0 ? -1 : 1;

				Direction = FVector(rand, -Direction.Y, 0);
			}
			boundCount -= 1;
		}
		else
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AItem::DestroyItem, 1.5f, false);
		}
	}
}

void AItem::ItemMove(float DeltaTime)
{
	FVector dir = Direction;
	dir.Normalize();
	FVector P = GetActorLocation() + DeltaTime * 1000 * dir;

	SetActorLocation(P);
}

void AItem::ChangeType_Implementation()
{
}

void AItem::ChangeScale()
{
	// 0.5초를 기준으로 아이템의 크기를 InterpTo를 사용하여 변경
	FVector CurrentScale = ItemBody->GetComponentScale();
	FVector NewScale = FMath::VInterpTo(CurrentScale, TargetScale, GetWorld()->GetDeltaSeconds(), 2.0f);
	ItemBody->SetWorldScale3D(NewScale);
}

void AItem::SetTargetScale()
{
	if (isSmall)
	{
		TargetScale = FVector(1.5f, 1.5f, 1.5f);
		isSmall = false;
	}
	else {
		TargetScale = FVector(2, 2, 2);
		isSmall = true;
	}
}

void AItem::DestroyItem()
{
	this->Destroy();
}