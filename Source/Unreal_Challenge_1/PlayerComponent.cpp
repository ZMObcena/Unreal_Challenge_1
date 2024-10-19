
#include "PlayerComponent.h"

// Sets default values for this component's properties
UPlayerComponent::UPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	SiloCount = 1;
	StoneAmount = 0;
	WoodAmount = 100;

	MaxStoneAmount = 25;
	MaxWoodAmount = 100;
}


// Called every frame
void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerComponent::SetStoneAmount(int Amount)
{
	StoneAmount = Amount;
}

int UPlayerComponent::GetStoneAmount()
{
	return StoneAmount;
}

void UPlayerComponent::SetWoodAmount(int Amount)
{
	WoodAmount = Amount;
}

int UPlayerComponent::GetWoodAmount()
{
	return WoodAmount;
}

void UPlayerComponent::BuySilo()
{
	MaxStoneAmount += 25;
	MaxWoodAmount += 100;
	SiloCount++;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Blue, FString::Printf(TEXT("Maximum Wood Amount Increased: %d/%d Wood"), WoodAmount, MaxWoodAmount));
		GEngine->AddOnScreenDebugMessage(4, 5.0f, FColor::Blue, FString::Printf(TEXT("Maximum Stone Amount Increased: %d/%d Stone"), StoneAmount, MaxStoneAmount));
		GEngine->AddOnScreenDebugMessage(5, 5.0f, FColor::Blue, FString::Printf(TEXT("Silo Count: %d"), SiloCount));
	}
}

int UPlayerComponent::GetMaxStoneAmount()
{
	return MaxStoneAmount;
}

int UPlayerComponent::GetMaxWoodAmount()
{
	return MaxWoodAmount;
}

bool UPlayerComponent::CheckMaxStone(int Stone)
{
	if (Stone > MaxStoneAmount)
	{
		StoneAmount = MaxStoneAmount;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Maximum Stone Amount Reached: %d Stone"), StoneAmount));
		return false;
	}
	return true;
}

bool UPlayerComponent::CheckMaxWood(int Wood)
{
	if (Wood > MaxWoodAmount)
	{
		WoodAmount = MaxWoodAmount;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Maximum Wood Amount Reached: %d Wood"), WoodAmount));
		return false;
	}
	return true;
}

