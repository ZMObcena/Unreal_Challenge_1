// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	WorkerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorkerMesh"));
	WorkerMesh->SetupAttachment(RootSceneComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SiloCount = 1;
	StoneAmount = 0;
	WoodAmount = 100;

	MaxStoneAmount = 25;
	MaxWoodAmount = 100;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::SetStoneAmount(int Amount)
{
	StoneAmount = Amount;
}

int APlayerPawn::GetStoneAmount() 
{
	return StoneAmount;
}

void APlayerPawn::SetWoodAmount(int Amount)
{
	WoodAmount = Amount;
}

int APlayerPawn::GetWoodAmount()
{
	return WoodAmount;
}

void APlayerPawn::BuySilo()
{
	MaxStoneAmount += 25;
	MaxWoodAmount += 100;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Maximum Wood Amount Increased: %d/%d Wood"), WoodAmount, MaxWoodAmount));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Maximum Stone Amount Increased: %d/%d Stone"), StoneAmount, MaxStoneAmount));
	}
}

int APlayerPawn::GetMaxStoneAmount()
{
	return MaxStoneAmount;
}

int APlayerPawn::GetMaxWoodAmount()
{
	return MaxWoodAmount;
}

bool APlayerPawn::CheckMaxStone(int Stone)
{
	if (Stone > MaxStoneAmount)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Maximum Stone Amount Reached: %d Stone"), StoneAmount));
		return false;
	}
	return true;
}

bool APlayerPawn::CheckMaxWood(int Wood)
{
	if (Wood > MaxWoodAmount)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Maximum Wood Amount Reached: %d Wood"), WoodAmount));
		return false;
	}
	return true;
}



