// Copyright © Golden Nuggs Games 2020


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"

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
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error in object %s. InputComponent is null."), *GetOwner()->GetName());
	}
}

void UGrabber::Init_PhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error in object %s. PhysicsHandle is null."), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Raycast for physicsbody objects
	LineTracePhysicsBodyObjects();
}

void UGrabber::LineTracePhysicsBodyObjects()
{
	// Get player viewpoint
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPointLoc, OUT ViewPointRot);

	// Check for Hits of certain object type (PhysicsBody). Set Params to simple and ignore Owner
	FVector LineTraceEnd = ViewPointLoc + (ViewPointRot.Vector() * Reach);
	FColor DebugLineColor = FColor(255.f, 125.f, 125.f, 10.f);
	DrawDebugLine(GetWorld(), ViewPointLoc, LineTraceEnd, DebugLineColor.WithAlpha(40), false, -1.f, 0.f, 5.f);

	FCollisionObjectQueryParams TraceObjectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewPointLoc, LineTraceEnd, TraceObjectParams, TraceParams);

	// Report if a physicsbody is hit
	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s in reach."), *Hit.GetActor()->GetName());
	}
}

void UGrabber::Grab()
{
	bGrabPressed = !bGrabPressed;

	if (bGrabPressed)
	{
		UE_LOG(LogTemp, Warning, TEXT("GRAB PRESSED"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GRAB RELEASED"));
	}


}

