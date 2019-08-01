// Copyright Reece Flowers 2019

#include "EscapeRoom2.h"
#include "Grabber.h"

#define OUT
//does nothing but just a reminder

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. Turn this feature
	// off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	/// look for attached Physics Handle
	FindPhysicsHandleComponent();
	///Look for attached Input Component
	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		///Bind the Input Action	
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Input Component"), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Setup Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT(" ")), false, GetOwner());
	//Line trace (Ray Cast)
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);
	return Hit;
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Physics Handle Component"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() {
	//LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();  //gets the mesh
	auto Actorhit = HitResult.GetActor();
	//attach physics handle
	if (Actorhit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,  //Bones not needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You're grabbing at thin air."));
	}
}

void UGrabber::Release() {
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if physics handle is attached
	if (!PhysicsHandle)
	{
		return;
	}
		
	if (PhysicsHandle->GrabbedComponent)
	{
		//move the obejct holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}
FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotator);
	return PlayerViewPointLocation + (PlayerViewPointRotator.Vector() * Reach);
}
FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotator);
	return PlayerViewPointLocation;
}
