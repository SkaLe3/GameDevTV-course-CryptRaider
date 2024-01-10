// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
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

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr)
		return;

	if (physicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TragetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		physicsHandle->SetTargetLocationAndRotation(TragetLocation, GetComponentRotation());

	}

	
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (!physicsHandle)
		return;


	FHitResult hitResult;
	if (GetGrabbableInReach(hitResult))
	{
		auto* hitComponent = hitResult.GetComponent();
		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();
		AActor* hitActor = hitResult.GetActor();
		hitActor->Tags.Add("Grabbed");
		hitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		physicsHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
	}

}

void UGrabber::Release()
{
	auto* physicsHandle = GetPhysicsHandle();
	if (!physicsHandle)
		return;
	if (physicsHandle->GetGrabbedComponent())
	{
		physicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		physicsHandle->ReleaseComponent();
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{

	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult hitResult;

	bool hasHit = GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);
	if (hasHit)
		OutHitResult = hitResult;
	return hasHit;

}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	auto* result =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!result)
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	return result;
}

