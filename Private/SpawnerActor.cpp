// Fill out your copyright notice in the Description page of Project Settings.
#include "SpawnerActor.h"

#include "Engine/World.h"

// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    StaticMeshComp->SetupAttachment(RootComponent);

    bIsActorsLocated = false;
}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();
    // SpawnActorWithComponent();
}

// Called every frame
void ASpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 클릭시 생성, 사라짐 반복 생성 될떄마다 랜덤으로 값 적용
void ASpawnerActor::TriggerBeginEvent()
{
    OnBeginEvent.Broadcast();

    UE_LOG(LogTemp, Warning, TEXT("TriggerBeginEvent!"));

    if (bIsActorsLocated)
    {
        bIsActorsLocated = false;
        DestroySpawnedActors();
    }
    else
    {
        bIsActorsLocated = true;
        SpawnActorWithComponent();
    }
}

void ASpawnerActor::SpawnActorWithComponent()
{
    int32 NumActors = 5;

    for (int32 i = 0; i < NumActors; i++)
    {
        if (UWorld* World = GetWorld())
        {
            FVector SpawnLocation = GetActorLocation() + FVector(200, i * 100, 0);
            Spawnlocations.Add(SpawnLocation);
            FRotator SpawnRotation = FRotator::ZeroRotator;

            // StaticClass()는 언리얼 엔진의 RTTI (런타임 타입 정보) 기능.
            ACPP_RandomFloor* SpawnedActor = World->SpawnActor<ACPP_RandomFloor>(ACPP_RandomFloor::StaticClass(), SpawnLocation, SpawnRotation);

            if (SpawnedActor)
            {
                SpawnedActors.Add(SpawnedActor);

                UMoveActionComponent* MoveComp = SpawnedActor->FindComponentByClass<UMoveActionComponent>();
                if (MoveComp)
                {
                    UE_LOG(LogTemp, Warning, TEXT("MoveActionComponent found on %s"), *SpawnedActor->GetName());
                    MoveComp->StartMove();
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("MoveActionComponent NOT found on %s"), *SpawnedActor->GetName());
                }
            }
        }
    }
}

void ASpawnerActor::DestroySpawnedActors()
{
    for (ACPP_RandomFloor* Actor : SpawnedActors)
    {
        if (Actor && Actor->IsValidLowLevel())
        {
            Actor->Destroy();
        }
    }

    SpawnedActors.Empty();
}
