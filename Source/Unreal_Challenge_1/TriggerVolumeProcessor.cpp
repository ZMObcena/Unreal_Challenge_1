// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolumeProcessor.h"
#include "TimerManager.h"
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

	APlayerPawn* thePlayer = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	AWorkerActor* OwnerActor = Cast<AWorkerActor>(GetOwner());

    if (bCanInteract && this->TriggerVol->IsOverlappingActor(thePlayer))
	{
		if (!OwnerActor->GetIsActive())
		{
			UE_LOG(LogTemp, Warning, TEXT("Worker Activated"));
			OwnerActor->ActivateWorker();
			bCanInteract = false;
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UTriggerVolumeProcessor::ResetCooldown, 5.0f, false);
		}
		else
		{
			OwnerActor->LevelUp();
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UTriggerVolumeProcessor::ResetCooldown, 5.0f, false);
		}
    }
}

void UTriggerVolumeProcessor::ResetCooldown()
{
	bCanInteract = true;
}