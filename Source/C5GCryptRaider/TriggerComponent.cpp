// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	Triggered = false;
}


void UTriggerComponent::SetMover(UMover* mover)
{
	Mover = mover;
}

bool UTriggerComponent::IsTriggered() const
{
	return Triggered;
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* actor = GetAcceptableActor();
	if (actor != nullptr)
	{
		auto component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component != nullptr)
		{
			component->SetSimulatePhysics(false);
		}
		actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		if (Mover)
			Mover->SetSHouldMove(true);
		Triggered = true;
	}
	else
	{
		if (Mover)
			Mover->SetSHouldMove(false);
		Triggered = false;
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);

	for (auto& actor : actors)
	{

		if (actor->ActorHasTag(AcceptableActorTag) && !actor->ActorHasTag("Grabbed"))
			return actor;
	}

	return nullptr;
}
