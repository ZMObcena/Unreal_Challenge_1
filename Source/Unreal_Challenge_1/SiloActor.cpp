// Fill out your copyright notice in the Description page of Project Settings.


#include "SiloActor.h"
#include "PlayerComponent.h"

// Sets default values
ASiloActor::ASiloActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsActive = false;
}

// Called when the game starts or when spawned
void ASiloActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASiloActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UPlayerComponent* thePlayer = PlayerRef->FindComponentByClass<UPlayerComponent>();
	int WoodAmount = thePlayer->GetWoodAmount();
	int MaxWoodAmount = thePlayer->GetMaxWoodAmount();

	if (this->TriggerVol->IsOverlappingActor(PlayerRef))
	{
		if (!bIsActive && WoodAmount >= 50)
		{
			thePlayer->BuySilo();
			bIsActive = true;
			thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() - 50);
		}
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(4, 5.0f, FColor::Red, FString::Printf(TEXT("Silo is already active or not enough wood.")));
		}
	}
}

