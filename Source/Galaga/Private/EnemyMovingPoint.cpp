// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovingPoint.h"
#include "EnemyBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyMovingPoint::AEnemyMovingPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointBodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PointBodyCollision"));
	RootComponent = PointBodyCollision;
	PointBodyCollision->SetCollisionProfileName("OverlapAll");
	PointBodyCollision->SetRelativeScale3D(FVector(3, 3, 3));
	//PointBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointBody"));
	//PointBody->SetupAttachment(PointBodyCollision);
	//ConstructorHelpers::FObjectFinder<UStaticMesh>PointBodyMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	//if (PointBodyMesh.Succeeded())
	//{
	//	PointBody->SetStaticMesh(PointBodyMesh.Object);
	//}

	PointBodyCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyMovingPoint::OnComponentBeginOverlap);
}

// Called when the game starts or when spawned
void AEnemyMovingPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyMovingPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AEnemyMovingPoint::GetMovingPointLocation()
{
	FVector MovingPoint = this->GetActorLocation();
	return MovingPoint;
}

void AEnemyMovingPoint::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->ActorHasTag("Enemy"))
	{
		AEnemyBase* enemy = Cast<AEnemyBase>(OtherActor);
		if (enemy != nullptr)
		{
			switch (enemy->GetMType())
			{
			case EEnemyType::Suiside:
				break;
			case EEnemyType::Patrol:
			{
				if (CheckTargetMovingPoint(enemy))
				{
					enemy->GetFSM()->SetIsMoving(false);
					break;
				}
			}
			case EEnemyType::Fixed:
			{
				if (CheckTargetMovingPoint(enemy))
				{
					enemy->GetFSM()->SetIsMoving(false);
				}
				break;
			}
			case EEnemyType::PassBy:
			{
				if (CheckTargetMovingPoint(enemy))
				{
					enemy->Destroy();
				}
				break;
			}
			case EEnemyType::Random:
				enemy->GetFSM()->SetIsMoving(false);
				break;
			case EEnemyType::InOut:
			{
				if (CheckTargetMovingPoint(enemy))
				{
					if (enemy->GetFSM()->isIn)
					{
						enemy->GetFSM()->SetIsMoving(false);
						enemy->GetFSM()->isIn = false;
					}
					break;
				}
			}
			default:
				break;
			}
		}
	}
}

bool AEnemyMovingPoint::CheckTargetMovingPoint(AEnemyBase* enemy)
{
	auto targetP = enemy->GetTargetMovingPointByIndex(enemy->GetEnemyTargetMovingPointIndex());

	if (targetP)
	{
		AEnemyMovingPoint* targetMovingPoint = Cast<AEnemyMovingPoint>(targetP);
		if (targetMovingPoint != nullptr)
		{
			if (targetMovingPoint == this)
			{
				return true;
			}
		}
	}
	return false;
}

