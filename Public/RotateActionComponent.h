// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "RotateActionComponent.generated.h"

UENUM(BlueprintType)
enum class ERotationAxis : uint8 // �޸� ����ȭ, Ÿ�� ������, �ڵ� ������, ��Ʈ ���� Ȱ��
{
	None UMETA(DisplayName = "None"),   // ȸ�� ����
	X     UMETA(DisplayName = "X-Pitch"), // X�� ȸ��
	Y     UMETA(DisplayName = "Y-Yaw"), // Y�� ȸ��
	Z     UMETA(DisplayName = "Z-Roll")  // Z�� ȸ��
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
