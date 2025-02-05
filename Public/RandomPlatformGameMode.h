// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RandomPlatformGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_6_7_API ARandomPlatformGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARandomPlatformGameMode();

protected:
	virtual void BeginPlay() override;

private:
	// �÷��� Ŭ������
	UPROPERTY(EditAnywhere, Category = "Platform")
	TSubclassOf<AActor> RotatingPlatformClass;

	UPROPERTY(EditAnywhere, Category = "Platform")
	TSubclassOf<AActor> MovingPlatformClass;

	// �÷��� ���� �Լ�
	void SpawnPlatforms();
};
