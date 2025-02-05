// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "RotateActionComponent.generated.h"

UENUM(BlueprintType)
enum class ERotationAxis : uint8 // 메모리 최적화, 타입 안전성, 코드 가독성, 비트 연산 활용
{
	None UMETA(DisplayName = "None"),   // 회전 없음
	X     UMETA(DisplayName = "X-Pitch"), // X축 회전
	Y     UMETA(DisplayName = "Y-Yaw"), // Y축 회전
	Z     UMETA(DisplayName = "Z-Roll")  // Z축 회전
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT_6_7_API URotateActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotateActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	ERotationAxis RotationAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float TimerInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	bool bIsRandom;

private:
	FTimerHandle RotationTimerHandle;

	void StartRotationTimer();
	void OnRotationTimerEnd();
	void HandleRotation(float DeltaTime);
	void ApplyRotation(AActor* Owner, float DeltaTime);

	bool bIsRotating;
};
