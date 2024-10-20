#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkerActor.generated.h"

UCLASS()
class UNREAL_CHALLENGE_1_API AWorkerActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWorkerActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void InitializeStats();

    void ActivateWorker();

    void GatherResources();

    void LevelUp();

    bool GetIsActive();

private:
    int WoodGatherRate;
    int StoneGatherRate;
    int LevelCost;

    UPROPERTY(EditAnywhere, Category = "RootSceneComponent")
    USceneComponent* RootSceneComponent;

    UPROPERTY(EditAnywhere, Category = "WorkerMesh")
    USkeletalMeshComponent* WorkerMesh;

    UPROPERTY(EditAnywhere, Category = "ResourceTarget")
    FVector ResourcePoint; 

    UPROPERTY(EditAnywhere, Category = "BaseTarget")
    FVector BasePoint;

    FVector CurrentTarget;

    UPROPERTY(EditAnywhere, Category = "MovementSpeed");
    float MovementSpeed;

    // Worker stats
    UPROPERTY(EditAnywhere, Category = "ResourceType");
    bool bResourceType;

    UPROPERTY(EditAnywhere, Category = "ResourceType");
    bool bActivateAtStart;

    int Level;
    bool bIsActive;

    void AddResources();
};