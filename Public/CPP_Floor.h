// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Floor.generated.h"

UCLASS()
class ASSIGNMENT_6_7_API ACPP_Floor : public ABaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Floor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
