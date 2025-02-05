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
	�������Ʈ���� ���ε� ���� (BlueprintAssignable�� �Բ� ���)
	���� ���� ������(���ε��� �Լ�)���� �̺�Ʈ�� ��ε�ĳ��Ʈ ����
	UObject ��� Ŭ���������� ��� ���� (��, AActor, UActorComponent ��� ��� ����)
	*/
	// UE5���� ����� �� �ִ� ���� ��Ƽĳ��Ʈ ��������Ʈ(Dynamic Multicast Delegate) ���� ��ũ��
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginEvent);

	// �������Ʈ ������ ���� ����
	UPROPERTY(BlueprintAssignable, Category = "Spawner")
	FOnBeginEvent OnBeginEvent;

private:
	void DestroySpawnedActors();

	TArray<ACPP_RandomFloor*> SpawnedActors;
	TArray<FVector> Spawnlocations;

	bool bIsActorsLocated;
};
