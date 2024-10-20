// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class UNREAL_CHALLENGE_1_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetStoneAmount(int Amount);
	int GetStoneAmount();

	void SetWoodAmount(int Amount);
	int GetWoodAmount();

	int StoneAmount;
	int WoodAmount;

	int SiloCount;

	int MaxStoneAmount;
	int GetMaxStoneAmount();

	int MaxWoodAmount;
	int GetMaxWoodAmount();

	void BuySilo();

	bool CheckMaxStone(int Stone);
	bool CheckMaxWood(int Wood);

private:
	UPROPERTY(EditAnywhere, Category = "RootSceneComponent")
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, Category = "PlayerMesh")
	UStaticMeshComponent* WorkerMesh;
};
