#include "RandomPlatformGameMode.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "RotateActionComponent.h"
#include "MoveActionComponent.h"
#include "Math/UnrealMathUtility.h" // FMath ���� �Լ���

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
	const int32 PlatformCount = 10; // ������ �÷����� ����

	// �÷��� Ŭ���� �迭
	TArray<TSubclassOf<AActor>> PlatformClasses = { RotatingPlatformClass, MovingPlatformClass };

	for (int32 i = 0; i < PlatformCount; i++)
	{
		// ������ ��ġ (X, Y ����: -500 ~ 500, Z ����: 0 ~ 1000)
		FVector RandomPosition(FMath::RandRange(-500.0f, 500.0f), FMath::RandRange(-500.0f, 500.0f), FMath::RandRange(0.0f, 1000.0f));

		// ������ ȸ�� (Yaw ����: 0 ~ 360)
		FRotator RandomRotation(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		// ���Ƿ� �÷��� ���� ����
		TSubclassOf<AActor> ChosenPlatform = PlatformClasses[FMath::RandRange(0, PlatformClasses.Num() - 1)];

		// �÷��� ����
		AActor* SpawnedPlatform = GetWorld()->SpawnActor<AActor>(ChosenPlatform, RandomPosition, RandomRotation);

		// ȸ�� ������ ��� �Ӽ� ����
		if (ChosenPlatform == RotatingPlatformClass)
		{
			URotateActionComponent* RotateComponent = SpawnedPlatform->FindComponentByClass<URotateActionComponent>();
			if (RotateComponent)
			{
				RotateComponent->RotationSpeed = FMath::RandRange(30.0f, 150.0f); // ���� �ӵ�
				RotateComponent->RotationAxis = ERotationAxis(FMath::RandRange(0, 2)); // ���� ��
			}
		}

		// �̵� �÷����� ��� �Ӽ� ����
		if (ChosenPlatform == MovingPlatformClass)
		{
			UMoveActionComponent* MoveComponent = SpawnedPlatform->FindComponentByClass<UMoveActionComponent>();
			if (MoveComponent)
			{
				MoveComponent->MoveSpeed = FMath::RandRange(100.0f, 300.0f); // ���� �̵� �ӵ�
				MoveComponent->MaxRange = FMath::RandRange(500.0f, 1000.0f); // ���� �ִ� ����
			}
		}
	}
}
