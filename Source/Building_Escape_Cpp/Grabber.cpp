// Copyright © Golden Nuggs Games 2020


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	// Get player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPointLoc, ViewPointRot);

	//UE_LOG(LogTemp, Warning, TEXT("Grabber Loc/Rot %s / %s"), *ViewPointLoc.ToString(), *ViewPointRot.ToString());

	FVector LineTraceEnd = ViewPointLoc + (ViewPointRot.Vector() * Reach);
	FColor DebugLineColor = FColor(255.f, 125.f, 125.f, 10.f);

	DrawDebugLine(GetWorld(), ViewPointLoc, LineTraceEnd, DebugLineColor.WithAlpha(40), false, -1.f, 0.f, 5.f);
}

