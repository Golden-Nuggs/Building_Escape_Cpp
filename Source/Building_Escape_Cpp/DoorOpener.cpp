// Copyright © Golden Nuggs Games 2020


#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"

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
	RotOpen = RotClosed;
	RotOpen.Yaw += OpeningDegrees;

	UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s"), *Owner->GetName(), *Owner->GetActorRotation().ToString());

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		{
			DoorOpen();
		}
		else
		{
			DoorClose();
		}
	}

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

void UDoorOpener::DoorOpen()
{
	Owner->SetActorRotation(RotOpen);
}

void UDoorOpener::DoorClose()
{
	Owner->SetActorRotation(RotClosed);
}

