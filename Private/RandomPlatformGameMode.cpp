#include "RandomPlatformGameMode.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "RotateActionComponent.h"
#include "MoveActionComponent.h"
#include "Math/UnrealMathUtility.h" // FMath 관련 함수들

ARandomPlatformGameMode::ARandomPlatformGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARandomPlatformGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlatforms();
}

void ARandomPlatformGameMode::SpawnPlatforms()
{
	const int32 PlatformCount = 10; // 생성할 플랫폼의 개수

	// 플랫폼 클래스 배열
	TArray<TSubclassOf<AActor>> PlatformClasses = { RotatingPlatformClass, MovingPlatformClass };

	for (int32 i = 0; i < PlatformCount; i++)
	{
		// 임의의 위치 (X, Y 범위: -500 ~ 500, Z 범위: 0 ~ 1000)
		FVector RandomPosition(FMath::RandRange(-500.0f, 500.0f), FMath::RandRange(-500.0f, 500.0f), FMath::RandRange(0.0f, 1000.0f));

		// 임의의 회전 (Yaw 범위: 0 ~ 360)
		FRotator RandomRotation(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		// 임의로 플랫폼 종류 선택
		TSubclassOf<AActor> ChosenPlatform = PlatformClasses[FMath::RandRange(0, PlatformClasses.Num() - 1)];

		// 플랫폼 생성
		AActor* SpawnedPlatform = GetWorld()->SpawnActor<AActor>(ChosenPlatform, RandomPosition, RandomRotation);

		// 회전 발판일 경우 속성 설정
		if (ChosenPlatform == RotatingPlatformClass)
		{
			URotateActionComponent* RotateComponent = SpawnedPlatform->FindComponentByClass<URotateActionComponent>();
			if (RotateComponent)
			{
				RotateComponent->RotationSpeed = FMath::RandRange(30.0f, 150.0f); // 랜덤 속도
				RotateComponent->RotationAxis = ERotationAxis(FMath::RandRange(0, 2)); // 랜덤 축
			}
		}

		// 이동 플랫폼일 경우 속성 설정
		if (ChosenPlatform == MovingPlatformClass)
		{
			UMoveActionComponent* MoveComponent = SpawnedPlatform->FindComponentByClass<UMoveActionComponent>();
			if (MoveComponent)
			{
				MoveComponent->MoveSpeed = FMath::RandRange(100.0f, 300.0f); // 랜덤 이동 속도
				MoveComponent->MaxRange = FMath::RandRange(500.0f, 1000.0f); // 랜덤 최대 범위
			}
		}
	}
}
