// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "ActorVisibilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT_6_7_API UActorVisibilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorVisibilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	float VisibilityDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	float ReappearanceDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	bool bRepeatVisibilityCycle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	bool bVisible;

private:
	FTimerHandle VisibilityTimerHandle;
	FTimerHandle ReappearanceTimerHandle;

	void HideActor();
	void ShowActor();
	void StartVisibilityCycle();

	AActor* OwnerActor;
};
