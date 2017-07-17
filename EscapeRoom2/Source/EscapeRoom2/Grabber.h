// Copyright Reece Flowers 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM2_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 120.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-Cast and grab what is in reach	
	void Grab();
	// Called when grab is released
	void Release();
	
	// Find attached Physics
	void FindPhysicsHandleComponent();
	//Setup (assumed) attached Input Component
	void SetupInputComponent();
		
	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
