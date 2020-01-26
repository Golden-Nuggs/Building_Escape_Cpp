// Copyright © Golden Nuggs Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDING_ESCAPE_CPP_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorOpener();

	UPROPERTY(EditAnywhere)
	float OpeningDegrees;

	UPROPERTY(EditAnywhere)
	class ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay;

	UPROPERTY(EditAnywhere)
	float PressurePlateWeightTolerance = 120.f;

private:
	class AActor* Owner = nullptr;
	FRotator RotClosed;
	FRotator RotOpen;
	float DoorCloseTimer = 0.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DoorOpen();

	void DoorClose();

	float GetCurrentWeightOnPlate();

};