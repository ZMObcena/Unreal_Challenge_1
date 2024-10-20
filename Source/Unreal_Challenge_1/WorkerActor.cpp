#include "WorkerActor.h"
#include "PlayerComponent.h"
#include "PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWorkerActor::AWorkerActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Level = 1;
    bIsActive = false;
    
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;

    WorkerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WorkerMesh"));
    WorkerMesh->SetupAttachment(RootSceneComponent); 

    if (bActivateAtStart)
    {
        bIsActive = true;
    }

    InitializeStats();
}

// Called when the game starts or when spawned
void AWorkerActor::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AWorkerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsActive)
    {
        GatherResources();
    }
}

void AWorkerActor::InitializeStats()
{
    if (Level == 1)
    {
        WoodGatherRate = 10;
        StoneGatherRate = 4;
    }

    else if (Level == 2)
    {
        WoodGatherRate = 15;
        StoneGatherRate = 8;
    }

    else if (Level == 3)
    {
        WoodGatherRate = 20;
        StoneGatherRate = 12;
        MovementSpeed = MovementSpeed + (MovementSpeed * 0.05f);
    }

    else if (Level == 4)
    {
        WoodGatherRate = 25;
        StoneGatherRate = 16;
        MovementSpeed = MovementSpeed + (MovementSpeed * 0.1f);
    }

    else if (Level == 5)
    {
        WoodGatherRate = 30;
        StoneGatherRate = 20;
        MovementSpeed = MovementSpeed + (MovementSpeed * 0.15f);
    }
}

void AWorkerActor::ActivateWorker()
{
    UPlayerComponent* thePlayer = PlayerRef->FindComponentByClass<UPlayerComponent>();
    int WoodAmount = thePlayer->GetWoodAmount();
    int StoneAmount = thePlayer->GetStoneAmount();

    if (WoodAmount >= 20)
    {
        thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() - 20);
        bIsActive = true;
        CurrentTarget = BasePoint;
        if (GEngine)
        {
            if (bResourceType)
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Wood Worker Activated"));
            else
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Stone Worker Activated"));
            GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Player has %d Wood and %d Stone"), thePlayer->GetWoodAmount(), thePlayer->GetStoneAmount()));
        }
    }
}

void AWorkerActor::GatherResources()
{
    FVector CurrentLocation = GetActorLocation();
    FVector Distance = CurrentTarget - CurrentLocation;
    FVector NewLocation = CurrentLocation;
    float DistanceToTarget = Distance.Size();

    Distance.Normalize();

    NewLocation.Z = CurrentLocation.Z;
    NewLocation = CurrentLocation + Distance * MovementSpeed;
    SetActorLocation(NewLocation);

    if (DistanceToTarget <= 10.0f)
    {
        SetActorLocation(CurrentTarget);
        if (CurrentTarget == BasePoint)
        {
            CurrentTarget = ResourcePoint;
            AddResources();
        }
        else
        {
            CurrentTarget = BasePoint;
        }
    }
}

bool AWorkerActor::GetIsActive()
{
    return bIsActive;
}

void AWorkerActor::LevelUp()
{
    UPlayerComponent* thePlayer = Cast<UPlayerComponent>(GetWorld()->GetFirstPlayerController()->GetPawn());
    int WoodAmount = thePlayer->GetWoodAmount();
    int StoneAmount = thePlayer->GetStoneAmount();

    if (Level == 1)
    {
        if (WoodAmount >= 10 && StoneAmount >= 10)
        {
            Level++;
            InitializeStats();
            thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() - 10);
            thePlayer->SetStoneAmount(thePlayer->GetStoneAmount() - 10);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("Worker Level: %d"), Level));
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Wood Amount: %d/%d"), thePlayer->GetWoodAmount(), thePlayer->GetMaxWoodAmount()));
                GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Green, FString::Printf(TEXT("Stone Amount: %d/%d"), thePlayer->GetStoneAmount(), thePlayer->GetMaxStoneAmount()));
            }
        }
    }

    else if (Level == 2)
    {
        if (WoodAmount >= 15 && StoneAmount >= 10)
        {
            Level++;
            InitializeStats();
            thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() - 15);
            thePlayer->SetStoneAmount(thePlayer->GetStoneAmount() - 10);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("Worker Level: %d"), Level));
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Wood Amount: %d/%d"), thePlayer->GetWoodAmount(), thePlayer->GetMaxWoodAmount()));
                GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Green, FString::Printf(TEXT("Stone Amount: %d/%d"), thePlayer->GetStoneAmount(), thePlayer->GetMaxStoneAmount()));
            }
        }
    }

    else if (Level == 3)
    {
        if (WoodAmount >= 20 && StoneAmount >= 15)
        {
            Level++;
            InitializeStats();
            thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() - 30);
            thePlayer->SetStoneAmount(thePlayer->GetStoneAmount() - 20);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("Worker Level: %d"), Level));
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Wood Amount: %d/%d"), thePlayer->GetWoodAmount(), thePlayer->GetMaxWoodAmount()));
                GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Green, FString::Printf(TEXT("Stone Amount: %d/%d"), thePlayer->GetStoneAmount(), thePlayer->GetMaxStoneAmount()));
            }
        }
    }

    else if (Level == 4)
    {
        if (WoodAmount >= 30 && StoneAmount >= 20)
        {
            Level++;
            InitializeStats();
            thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() - 30);
            thePlayer->SetStoneAmount(thePlayer->GetStoneAmount() - 20);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("Worker Level: %d"), Level));
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Wood Amount: %d/%d"), thePlayer->GetWoodAmount(), thePlayer->GetMaxWoodAmount()));
                GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Green, FString::Printf(TEXT("Stone Amount: %d/%d"), thePlayer->GetStoneAmount(), thePlayer->GetMaxStoneAmount()));
            }
        }
    }
}

void AWorkerActor::AddResources()
{
    APlayerPawn* thePlayer = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (bResourceType)
    {
        if (thePlayer->CheckMaxWood(thePlayer->GetWoodAmount() + WoodGatherRate))
        {
            thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() + WoodGatherRate);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Wood Worker: +%d Wood"), WoodGatherRate));
                GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Player has %d/%d Wood"), thePlayer->GetWoodAmount(), thePlayer->GetMaxWoodAmount()));
            }
        }
    }
    else
    {
        if (thePlayer->CheckMaxStone(thePlayer->GetStoneAmount() + StoneGatherRate))
        {
            thePlayer->SetStoneAmount(thePlayer->GetStoneAmount() + StoneGatherRate);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Stone Worker: +%d Stone"), StoneGatherRate));
                GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Player has %d/%d Stone"), thePlayer->GetStoneAmount(), thePlayer->GetMaxStoneAmount()));
            }
        }
    }
}