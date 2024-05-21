// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyMovingPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	FindEnemyInnerMovingPoints();
	FindEnemyLeftMovingPoints();
	FindEnemyRightMovingPoints();
	FindEnemyBottomMovingPoints();
	FindEnemyTopMovingPoints();

	auto InnerNameCompare = [this](const AActor& A, const AActor& B)
		{
			FString NameA = A.GetName();
			FString NameB = B.GetName();

			int32 NumA = ExtractNumberFromName(NameA,"BP_EnemyInnerMovingPoint_C_");
			int32 NumB = ExtractNumberFromName(NameB,"BP_EnemyInnerMovingPoint_C_");

			return NumA < NumB;
		};

	auto LeftNameCompare = [this](const AActor& A, const AActor& B)
		{
			FString NameA = A.GetName();
			FString NameB = B.GetName();

			int32 NumA = ExtractNumberFromName(NameA, "BP_EnemyLeftMovingPoint_C_");
			int32 NumB = ExtractNumberFromName(NameB, "BP_EnemyLeftMovingPoint_C_");

			return NumA < NumB;
		};

	auto RightNameCompare = [this](const AActor& A, const AActor& B)
		{
			FString NameA = A.GetName();
			FString NameB = B.GetName();

			int32 NumA = ExtractNumberFromName(NameA, "BP_EnemyRightMovingPoint_C_");
			int32 NumB = ExtractNumberFromName(NameB, "BP_EnemyRightMovingPoint_C_");

			return NumA < NumB;
		};

	auto TopNameCompare = [this](const AActor& A, const AActor& B)
		{
			FString NameA = A.GetName();
			FString NameB = B.GetName();

			int32 NumA = ExtractNumberFromName(NameA, "BP_EnemyTopMovingPoint_C_");
			int32 NumB = ExtractNumberFromName(NameB, "BP_EnemyTopMovingPoint_C_");

			return NumA < NumB;
		};

	auto BottomNameCompare = [this](const AActor& A, const AActor& B)
		{
			FString NameA = A.GetName();
			FString NameB = B.GetName();

			int32 NumA = ExtractNumberFromName(NameA, "BP_EnemyBottomMovingPoint_C_");
			int32 NumB = ExtractNumberFromName(NameB, "BP_EnemyBottomMovingPoint_C_");

			return NumA < NumB;
		};
	InnerMovingPoints.Sort(InnerNameCompare);
	LeftMovingPoints.Sort(LeftNameCompare);
	RightMovingPoints.Sort(RightNameCompare);
	BottomMovingPoints.Sort(BottomNameCompare);
	TopMovingPoints.Sort(TopNameCompare);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::FindEnemyInnerMovingPoints()
{
	TArray<AActor*>allActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	for (auto movingP : allActors)
	{
		if (movingP->GetName().Contains(TEXT("BP_EnemyInnerMovingPoint")))
		{
			InnerMovingPoints.Add(movingP);

		}
	}

}

void AEnemyManager::FindEnemyLeftMovingPoints()
{
	TArray<AActor*>allActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	for (auto movingP : allActors)
	{
		if (movingP->GetName().Contains(TEXT("BP_EnemyLeftMovingPoint")))
		{
			LeftMovingPoints.Add(movingP);
		}
	}
}

void AEnemyManager::FindEnemyRightMovingPoints()
{
	TArray<AActor*>allActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	for (auto movingP : allActors)
	{
		if (movingP->GetName().Contains(TEXT("BP_EnemyRightMovingPoint")))
		{
			RightMovingPoints.Add(movingP);
		}
	}
}

void AEnemyManager::FindEnemyBottomMovingPoints()
{
	TArray<AActor*>allActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	for (auto movingP : allActors)
	{
		if (movingP->GetName().Contains(TEXT("BP_EnemyBottomMovingPoint")))
		{
			BottomMovingPoints.Add(movingP);
		}
	}
}

void AEnemyManager::FindEnemyTopMovingPoints()
{
	TArray<AActor*>allActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	for (auto movingP : allActors)
	{
		if (movingP->GetName().Contains(TEXT("BP_EnemyTopMovingPoint")))
		{
			TopMovingPoints.Add(movingP);
		}
	}
}

FVector AEnemyManager::GetRandomInnerMovingPoint()
{
	static int LastRandomIndex = -1;

	if (InnerMovingPoints.Num() > 0)
	{
		int randomMovingPointIndex = FMath::RandRange(0, InnerMovingPoints.Num()-1);

		while (randomMovingPointIndex == LastRandomIndex)
		{
			randomMovingPointIndex = FMath::RandRange(0, InnerMovingPoints.Num() - 1);
		}

		LastRandomIndex = randomMovingPointIndex;

		auto randomMovingPoint = InnerMovingPoints[randomMovingPointIndex];

		if (randomMovingPoint)
		{
			AEnemyMovingPoint* MovingPoint = Cast<AEnemyMovingPoint>(randomMovingPoint);

			if (MovingPoint != nullptr)
			{
				FVector randomMovingPointLocation = MovingPoint->GetMovingPointLocation();
				return randomMovingPointLocation;
			}
		}
	}
	return FVector::ZeroVector;
}

TArray<class AActor*> AEnemyManager::GetRandomPatrolMovingPoint()
{
	int NumMovingPoints = InnerMovingPoints.Num();
	if (NumMovingPoints == 0)
	{
		return TArray<AActor*>();
	}

	int firstRandomMovingPointIndex = FMath::RandRange(0, NumMovingPoints - 1);
	int secondRandomMovingPointIndex = firstRandomMovingPointIndex;

	while (secondRandomMovingPointIndex == firstRandomMovingPointIndex)
	{
		secondRandomMovingPointIndex = FMath::RandRange(0, NumMovingPoints - 1);
	}

	TArray<AActor*> tempArr;
	tempArr.Add(InnerMovingPoints[firstRandomMovingPointIndex]);
	tempArr.Add(InnerMovingPoints[secondRandomMovingPointIndex]);

	return tempArr;
}

AActor* AEnemyManager::GetFixedMovingPoint()
{
	int RandomMovingPointIndex = FMath::RandRange(0, InnerMovingPoints.Num() - 1);


	return InnerMovingPoints[RandomMovingPointIndex];
}

AActor* AEnemyManager::GetFixedMovingPoint(int index)
{
	return InnerMovingPoints[index];
}

AActor* AEnemyManager::GetLeftMovingPoint()
{
	int RandomMovingPointIndex = FMath::RandRange(0, LeftMovingPoints.Num() - 1);


	return LeftMovingPoints[RandomMovingPointIndex];
}

AActor* AEnemyManager::GetLeftMovingPoint(int index)
{
	return LeftMovingPoints[index];
}

AActor* AEnemyManager::GetRightMovingPoint()
{
	int RandomMovingPointIndex = FMath::RandRange(0, RightMovingPoints.Num() - 1);


	return RightMovingPoints[RandomMovingPointIndex];
}

AActor* AEnemyManager::GetRightMovingPoint(int index)
{
	return RightMovingPoints[index];
}

AActor* AEnemyManager::GetBottomMovingPoint()
{
	int RandomMovingPointIndex = FMath::RandRange(0, BottomMovingPoints.Num() - 1);


	return BottomMovingPoints[RandomMovingPointIndex];
}

AActor* AEnemyManager::GetBottomMovingPoint(int index)
{
	return BottomMovingPoints[index];
}

AActor* AEnemyManager::GetTopMovingPoint()
{
	int RandomMovingPointIndex = FMath::RandRange(0, TopMovingPoints.Num() - 1);


	return TopMovingPoints[RandomMovingPointIndex];
}

AActor* AEnemyManager::GetTopMovingPoint(int index)
{
	return TopMovingPoints[index];
}


int32 AEnemyManager::ExtractNumberFromName(const FString& Name,FString Prefix)
{

	// Ensure the name starts with the prefix
	if (Name.StartsWith(Prefix))
	{
		// Extract the numeric part
		FString NumberString = Name.Mid(Prefix.Len());
		return FCString::Atoi(*NumberString);
	}

	// Return a default value if the name does not match the expected format
	return 0;
}