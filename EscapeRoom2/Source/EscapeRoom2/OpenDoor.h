// Copyright Reece Flowers 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM2_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Return total Mass of Actors on Plate
	float GetTotalMassOfActorsOnPlate();

private:
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = -80.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate =nullptr;
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 2.f;

		float LastDoorOpenTime;
		float CurrentTime;

		AActor *Owner =nullptr; //the owning door
};
