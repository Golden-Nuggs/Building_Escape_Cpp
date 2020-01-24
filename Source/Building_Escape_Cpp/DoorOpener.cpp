// Copyright © Golden Nuggs Games 2020


#include "DoorOpener.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	RotClosed = Owner->GetActorRotation();
	RotOpen = Owner->GetActorRotation();
	RotOpen.Yaw += OpeningDegrees;

	UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s"), *Owner->GetName(), *Owner->GetActorRotation().ToString());
	
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDoorOpener::ToggleDoorOpen()
{
	if (Owner->GetActorRotation().Yaw == RotClosed.Yaw)
	{
		Owner->SetActorRotation(RotOpen);
	}
	else
	{
		Owner->SetActorRotation(RotClosed);
	}
}

