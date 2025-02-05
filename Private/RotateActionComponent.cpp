#include "RotateActionComponent.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

URotateActionComponent::URotateActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	RotationSpeed = 50.0f;
	TimerInterval = 0.1f;
	bIsRotating = false;
	bIsRandom = false;
	RotationAxis = ERotationAxis::None;
}

void URotateActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Test for GameMode
	if (bIsRandom)
	{
		RotationSpeed = FMath::RandRange(50.0f, 200.0f);
		RotationAxis = ERotationAxis(FMath::RandRange(0, 2));
	}

	if (TimerInterval > 0.0f)
	{
		StartRotationTimer();
	}
	else
	{
		bIsRotating = true;
	}
}

void URotateActionComponent::StartRotationTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RotationTimerHandle, this, &URotateActionComponent::OnRotationTimerEnd, TimerInterval, true);
}

void URotateActionComponent::OnRotationTimerEnd()
{
	bIsRotating = true;
}

void URotateActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsRotating)
	{
		HandleRotation(DeltaTime);
	}
}

void URotateActionComponent::HandleRotation(float DeltaTime)
{
	AActor* Owner = GetOwner();

	if (Owner)
	{
		ApplyRotation(Owner, DeltaTime);
	}
}

void URotateActionComponent::ApplyRotation(AActor* Owner, float DeltaTime)
{
	FRotator CurrentRotation = Owner->GetActorRotation();

	FQuat RotationQuat = FQuat::Identity;

	switch (RotationAxis)
	{
	case ERotationAxis::X:
		RotationQuat = FQuat(FVector(1, 0, 0), FMath::DegreesToRadians(RotationSpeed * DeltaTime)); // X축 회전
		break;
	case ERotationAxis::Y:
		RotationQuat = FQuat(FVector(0, 1, 0), FMath::DegreesToRadians(RotationSpeed * DeltaTime)); // Y축 회전
		break;
	case ERotationAxis::Z:
		RotationQuat = FQuat(FVector(0, 0, 1), FMath::DegreesToRadians(RotationSpeed * DeltaTime)); // Z축 회전
		break;
	default:
		break;
	}

	Owner->AddActorLocalRotation(RotationQuat);
}

