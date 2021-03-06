// Copyright © Golden Nuggs Games 2020

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TwoVectors.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Init_PhysicsHandle();
	Init_InputComponent();
}

void UGrabber::Init_InputComponent()
{
	InputComponent = GetOwner()->InputComponent;
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found."));

		/// Bind the input actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Grab);
	}
}
void UGrabber::Init_PhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Error in object %s. PhysicsHandle is null."), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle)
	{
		FVector LineEnd = GetLineTraceVectors().v2;
		if (PhysicsHandle->GetGrabbedComponent())
		{
			PhysicsHandle->SetTargetLocation(LineEnd);
		}
	}

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector LineTraceEnd = GetLineTraceVectors().v1;
	FVector ViewPointLoc = GetLineTraceVectors().v2;
	FCollisionObjectQueryParams TraceObjectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewPointLoc, LineTraceEnd, TraceObjectParams, TraceParams);

	// Report if a physicsbody is hit
	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s in reach."), *Hit.GetActor()->GetName());
	}

	return Hit;
}

void UGrabber::Grab()
{
	bGrabPressed = !bGrabPressed;

	if (bGrabPressed)
	{
		UE_LOG(LogTemp, Warning, TEXT("GRAB PRESSED"));

		// Check if any physicsbody is in reach
	 	UPrimitiveComponent* HitComponent = GetFirstPhysicsBodyInReach().GetComponent();

		// if we find a physicsbody, then attach to it physics handle
		AActor* HitActor = GetFirstPhysicsBodyInReach().GetActor();
		if (HitActor)
		{
			PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitActor->GetActorLocation(), HitActor->GetActorRotation());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GRAB RELEASED"));

		// release the physics handle
		PhysicsHandle->ReleaseComponent();
	}
}

FTwoVectors UGrabber::GetLineTraceVectors() const
{
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPointLoc, OUT ViewPointRot);

	FVector LineTraceEnd;
	LineTraceEnd = ViewPointLoc + (ViewPointRot.Vector() * Reach);

	return FTwoVectors(ViewPointLoc, LineTraceEnd);
}