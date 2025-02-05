// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_RandomFloor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

UCLASS()
class ASSIGNMENT_6_7_API ASpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnActorWithComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UFUNCTION(CallInEditor)
	void TriggerBeginEvent();

	/*
	블루프린트에서 바인딩 가능 (BlueprintAssignable과 함께 사용)
	여러 개의 리스너(바인딩된 함수)에게 이벤트를 브로드캐스트 가능
	UObject 기반 클래스에서만 사용 가능 (즉, AActor, UActorComponent 등에서 사용 가능)
	*/
	// UE5에서 사용할 수 있는 동적 멀티캐스트 델리게이트(Dynamic Multicast Delegate) 선언 매크로
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginEvent);

	// 블루프린트 에서도 연결 가능
	UPROPERTY(BlueprintAssignable, Category = "Spawner")
	FOnBeginEvent OnBeginEvent;

private:
	void DestroySpawnedActors();

	TArray<ACPP_RandomFloor*> SpawnedActors;
	TArray<FVector> Spawnlocations;

	bool bIsActorsLocated;
};
