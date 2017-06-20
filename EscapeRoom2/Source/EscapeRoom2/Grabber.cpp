// Copyright Reece Flowers 2017

#include "EscapeRoom2.h"
#include "Grabber.h"

#define OUT
//does nothing but just a reminder

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
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//get player viewpoint every tick	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotator);
	UE_LOG(LogTemp, Warning, TEXT("Player Location: %s View Location: %s"), *PlayerViewPointLocation.ToString(),*PlayerViewPointRotator.ToString());
	//Ray-cast out to reach distance  and need a reach distance
	//see what we hit

	// ...
}

