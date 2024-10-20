// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "TriggerVolumeProcessor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_CHALLENGE_1_API UTriggerVolumeProcessor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerVolumeProcessor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FTimerHandle CooldownTimerHandle;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerVol;

private:
	bool bCanInteract;

	void ResetCooldown();
};
