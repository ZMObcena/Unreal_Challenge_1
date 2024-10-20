#include "WorkerActor.h"
#include "PlayerPawn.h"
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
    }

    else if (Level == 4)
    {
        WoodGatherRate = 25;
        StoneGatherRate = 16;
    }

    else
    {
        WoodGatherRate = 30;
        StoneGatherRate = 20;
    }
}

void AWorkerActor::ActivateWorker()
{
    bIsActive = true;
    CurrentTarget = BasePoint;
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
    APlayerPawn* thePlayer = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    int WoodAmount = thePlayer->GetWoodAmount();
    int StoneAmount = thePlayer->GetStoneAmount();

    if (Level == 1)
    {
        if (WoodAmount == 10 && StoneAmount == 10)
        {
            Level++;
            InitializeStats();

        }
    }

    else if (Level == 2)
    {
        if (WoodAmount == 15 && StoneAmount == 10)
        {
            Level++;
            InitializeStats();
        }
    }

    else if (Level == 3)
    {
        if (WoodAmount == 20 && StoneAmount == 15)
        {
            Level++;
            InitializeStats();
        }
    }

    else
    {
        if (WoodAmount == 30 && StoneAmount == 20)
        {
            Level++;
            InitializeStats();
        }
    }
}

void AWorkerActor::AddResources(bool bType)
{
    APlayerPawn* thePlayer = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (bType)
    {
        if(thePlayer->CheckMaxWood(thePlayer->GetWoodAmount() + WoodGatherRate))
            thePlayer->SetWoodAmount(thePlayer->GetWoodAmount() + WoodGatherRate);
    }
    else
    {
        if (thePlayer->CheckMaxStone(thePlayer->GetStoneAmount() + StoneGatherRate))
            thePlayer->SetWoodAmount(thePlayer->GetStoneAmount() + StoneGatherRate);
    }
}