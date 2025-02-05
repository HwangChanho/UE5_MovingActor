// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_RandomFloor.h"

// Sets default values
ACPP_RandomFloor::ACPP_RandomFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialAsset(TEXT("/Game/LevelPrototyping/Materials/MI_Solid_Blue.MI_Solid_Blue"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	SetActorScale3D(FVector(1.0f, 1.0f, 0.2f));

	MoveComponent = CreateDefaultSubobject<UMoveActionComponent>(TEXT("MoveActionComponent"));
	// RotateComponent = CreateDefaultSubobject<URotateActionComponent>(TEXT("RotateActionComponent"));

	MoveComponent->bIsRandom = true;
	MoveComponent->bReturnAfterMove = true;
	// RotateComponent->bIsRandom = true;
}

// Called when the game starts or when spawned
void ACPP_RandomFloor::BeginPlay()
{
	Super::BeginPlay();

	MoveComponent->StartMove();
}

// Called every frame
void ACPP_RandomFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

