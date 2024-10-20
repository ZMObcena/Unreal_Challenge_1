// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_CHALLENGE_1_API UPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
};
