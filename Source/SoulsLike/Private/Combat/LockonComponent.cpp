// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponent.h"
#include "Interfaces/Enemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

// Sets default values for this component's properties
ULockonComponent::ULockonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
}


// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CurrentTargetActor)) { return; }

	PlayerLocation = OwnerRef->GetActorLocation();
	TargetLocation = CurrentTargetActor->GetActorLocation();

	if (HandleLockonBreak()) { return; }
	UpdateLockonRotation();
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		EndLockon();
	}
	else
	{
		StartLockon(Radius);
	}
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FCollisionShape Sphere{ FCollisionShape::MakeSphere(Radius) };
	FCollisionQueryParams IgnoreParams{
		FName { TEXT("Ignore Collision Params") },
		false,
		OwnerRef
	};

	bool bHasFoundTarget{ GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere,
		IgnoreParams
	) };

	if (!bHasFoundTarget) { return; }
	if (!OutResult.GetActor()->Implements<UEnemy>()) { return; }

	CurrentTargetActor = OutResult.GetActor();

	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;
	SpringArmComp->TargetOffset = FVector{ 0.0, 0.0, 100.0 };
	
	Controller->SetIgnoreLookInput(true);

	IEnemy::Execute_OnSelect(CurrentTargetActor);
	OnTargetChangedDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::EndLockon()
{
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	CurrentTargetActor = nullptr;

	MovementComp->bOrientRotationToMovement = true;
	MovementComp->bUseControllerDesiredRotation = false;
	SpringArmComp->TargetOffset = FVector::ZeroVector;
	
	Controller->ResetIgnoreLookInput();

	OnTargetChangedDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::UpdateLockonRotation()
{
	TargetLocation.Z -= 125;

	FRotator LookAtRotation{ UKismetMathLibrary::FindLookAtRotation(
		PlayerLocation, TargetLocation)
	};
	Controller->SetControlRotation(LookAtRotation);
}

bool ULockonComponent::HandleLockonBreak()
{	
	double DistanceToTarget{ FVector::Distance(PlayerLocation, TargetLocation) };
	if (DistanceToTarget > BreakDistance) {
		EndLockon();
		return true;
	}
	else {
		return false;
	}
}
