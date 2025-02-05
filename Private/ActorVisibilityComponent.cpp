// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorVisibilityComponent.h"

// Sets default values for this component's properties
UActorVisibilityComponent::UActorVisibilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default Setting
	VisibilityDuration = 5.0f;
	ReappearanceDuration = 3.0f;
	bRepeatVisibilityCycle = false;
	bVisible = true;
}

// Called when the game starts
void UActorVisibilityComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();

	if (OwnerActor)
	{
		if (bVisible)
		{
			ShowActor();
		}
		else
		{
			HideActor();
		}

		// 반복 여부에 따라 사이클 시작
		if (bRepeatVisibilityCycle)
		{
			StartVisibilityCycle();
		}
	}
}

// Called every frame
void UActorVisibilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// 액터를 숨기는 함수
void UActorVisibilityComponent::HideActor()
{
	if (OwnerActor)
	{
		OwnerActor->SetActorHiddenInGame(true);
		OwnerActor->SetActorTickEnabled(false);
	}

	if (bRepeatVisibilityCycle)
	{
		GetWorld()->GetTimerManager().SetTimer(ReappearanceTimerHandle, this, &UActorVisibilityComponent::ShowActor, ReappearanceDuration, false);
	}
}

void UActorVisibilityComponent::ShowActor()
{
	if (OwnerActor)
	{
		OwnerActor->SetActorHiddenInGame(false); 
		OwnerActor->SetActorTickEnabled(true); 
	}

	if (bRepeatVisibilityCycle)
	{
		GetWorld()->GetTimerManager().SetTimer(VisibilityTimerHandle, this, &UActorVisibilityComponent::HideActor, VisibilityDuration, false);
	}
}

void UActorVisibilityComponent::StartVisibilityCycle()
{
	if (bRepeatVisibilityCycle)
	{
		if (bVisible)
		{
			GetWorld()->GetTimerManager().SetTimer(VisibilityTimerHandle, this, &UActorVisibilityComponent::HideActor, VisibilityDuration, false);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(VisibilityTimerHandle, this, &UActorVisibilityComponent::ShowActor, VisibilityDuration, false);
		}
	}
	else
	{
		ShowActor();
	}
}