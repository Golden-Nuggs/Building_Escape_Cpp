// Copyright © Golden Nuggs Games 2020


#include "Position_Reporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPosition_Reporter::UPosition_Reporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UPosition_Reporter::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is positioned at %s"), *ObjectName, *ObjectPosition);
	
}


// Called every frame
void UPosition_Reporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

