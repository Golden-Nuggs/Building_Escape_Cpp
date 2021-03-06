// Copyright © Golden Nuggs Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_CPP_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Init_InputComponent();

	void Init_PhysicsHandle();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FHitResult GetFirstPhysicsBodyInReach() const;

private:
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;
	class UInputComponent* InputComponent = nullptr;
	struct FTwoVectors GetLineTraceVectors() const;

	// Grab physicsbody objects using linetrace 
	void Grab();

	bool bGrabPressed = false;

};
