// Copyright © Golden Nuggs Games 2020


#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "Components/PrimitiveComponent.h"

#define OUT

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
	

}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate)
	{
		if (GetCurrentWeightOnPlate() > PressurePlateWeightTolerance)
		{
			DoorOpen();
			DoorCloseTimer = 0.f;
		}
		else
		{
			DoorCloseTimer += DeltaTime;
			if (DoorCloseTimer >= DoorCloseDelay)
			{
				DoorClose();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate is null on object: %s"), *Owner->GetName());
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

float UDoorOpener::GetCurrentWeightOnPlate()
{
	float TotalMass = 0;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Iterate through them and add mass to total
	for (AActor* Element : OverlappingActors)
	{
		float ObjectMass = Element->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += ObjectMass;
		UE_LOG(LogTemp, Warning, TEXT("%s has mass of %f. Total Mass currently: %f"), *Element->GetName(), ObjectMass, TotalMass);
		
		
	}

	return TotalMass;
}

