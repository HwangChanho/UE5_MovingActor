#include "MoveActionComponent.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY(LogDaniel);

UMoveActionComponent::UMoveActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MoveSpeed = 50.0f;
	MaxRange = 500.0f;
	bReturnAfterMove = false;
	bMovingForward = true;
	bIsMoving = false;
	bUseDelay = false;
	bIsRandom = false;
	TimerInterval = 1.0f; 
}

void UMoveActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Test for GameMode
	if (bIsRandom)
	{
		MoveSpeed = FMath::RandRange(100.0f, 300.0f);
		MaxRange = FMath::RandRange(500.0f, 1000.0f);
	}

	StartLocation = GetOwner()->GetActorLocation();
	StartMove();
}

void UMoveActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsMoving)
	{
		HandleMovement(DeltaTime);
	}
}

void UMoveActionComponent::StartMove()
{
	if (bUseDelay)
	{
		StartMoveTimer();
	}
	else
	{
		bIsMoving = true;
	}
}

void UMoveActionComponent::StartMoveTimer()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UMoveActionComponent::OnMoveTimerEnd, TimerInterval, true);
}

void UMoveActionComponent::OnMoveTimerEnd()
{
	bIsMoving = true;
}

void UMoveActionComponent::HandleMovement(float DeltaTime)
{
	AActor* Owner = GetOwner();
	if (!Owner || MoveSpeed == 0.0f) return;

	FVector CurrentLocation = Owner->GetActorLocation();
	float MoveStep = MoveSpeed * DeltaTime;

	if (bMovingForward)
	{
		CurrentLocation += MoveDirection.GetSafeNormal() * MoveStep;
	}
	else
	{
		if (bReturnAfterMove) 
		{
			CurrentLocation -= MoveDirection.GetSafeNormal() * MoveStep;
		}
	}

	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	if (DistanceMoved >= MaxRange)
	{
		bMovingForward = !bMovingForward;
		StartLocation = CurrentLocation;
	}

	Owner->SetActorLocation(CurrentLocation);
}
