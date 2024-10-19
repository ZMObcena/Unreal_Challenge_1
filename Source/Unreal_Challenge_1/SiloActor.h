// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "SiloActor.generated.h"

UCLASS()
class UNREAL_CHALLENGE_1_API ASiloActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASiloActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bIsActive;
	
	UPROPERTY(EditAnywhere, Category = "PlayerReference")
	AActor* PlayerRef;

	UPROPERTY(EditAnywhere, Category = "SiloTrigger")
	ATriggerVolume* TriggerVol;
};
