// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class C5GCRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UTriggerComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* mover);

	UFUNCTION(BlueprintCallable)
	bool IsTriggered() const;

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
private:
	AActor* GetAcceptableActor() const;
private:

	UMover* Mover;
	bool Triggered;
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;


};
