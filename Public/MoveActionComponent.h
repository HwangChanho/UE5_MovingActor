#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "MoveActionComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDaniel, Warning, All);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASSIGNMENT_6_7_API UMoveActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMoveActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector MoveDirection = FVector(1, 0, 0);

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bReturnAfterMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int MaxRange;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bUseDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TimerInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsRandom;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StartMove();

	void HandleMovement(float DeltaTime);

private:
	bool bMovingForward;
	FTimerHandle MoveTimerHandle;

	void StartMoveTimer();
	void OnMoveTimerEnd();
};
