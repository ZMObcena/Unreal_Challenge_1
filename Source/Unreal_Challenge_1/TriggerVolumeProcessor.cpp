// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolumeProcessor.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "PlayerPawn.h"
#include "WorkerActor.h"

// Sets default values for this component's properties
UTriggerVolumeProcessor::UTriggerVolumeProcessor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerVolumeProcessor::BeginPlay()
{
	Super::BeginPlay();

	bCanInteract = true;
}

void UTriggerVolumeProcessor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AWorkerActor* OwnerActor = Cast<AWorkerActor>(GetOwner());

    if (bCanInteract && this->TriggerVol->IsOverlappingActor(PlayerRef))
	{
		if (!OwnerActor->GetIsActive())
		{
			OwnerActor->ActivateWorker();
			bCanInteract = false;
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UTriggerVolumeProcessor::ResetCooldown, 5.0f, false);
		}
		else
		{
			OwnerActor->LevelUp();
			bCanInteract = false;
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UTriggerVolumeProcessor::ResetCooldown, 5.0f, false);
		}
    }
}

void UTriggerVolumeProcessor::ResetCooldown()
{
	bCanInteract = true;
}