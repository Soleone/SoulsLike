// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/TraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/Fighter.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector StartSocketLocation{ SkeletalComp->GetSocketLocation(StartSocketName) };
	FVector EndSocketLocation{ SkeletalComp->GetSocketLocation(EndSocketName) };
	FQuat ShapeRotation{ SkeletalComp->GetSocketQuaternion(SocketRotation) };

	TArray<FHitResult> HitResults;
	double WeaponLength{ FVector::Distance(StartSocketLocation, EndSocketLocation) };
	FVector WeaponDimensions{ WeaponWidth, WeaponHeight, WeaponLength };
	FCollisionQueryParams IgnoreParams{
		FName { TEXT("Ignore Collision Params") },
		false,
		GetOwner()
	};
	FCollisionShape Box{ FCollisionShape::MakeBox(WeaponDimensions / 2) };

	bool bHasFoundTarget{ GetWorld()->SweepMultiByChannel(
		HitResults,
		StartSocketLocation,
		EndSocketLocation,
		ShapeRotation,
		ECollisionChannel::ECC_GameTraceChannel1,
		Box,
		IgnoreParams
	) };

	if (bDebugMode)
	{
		FVector CenterPoint{
			UKismetMathLibrary::VLerp(
				StartSocketLocation, EndSocketLocation, 0.5f
			)
		};
		FLinearColor Color = bHasFoundTarget ? FLinearColor::Green : FLinearColor::Red;

		UKismetSystemLibrary::DrawDebugBox(
			GetWorld(),
			CenterPoint,
			Box.GetExtent(),
			Color,
			ShapeRotation.Rotator(),
			0.1f,
			0.5f
		);
	}

	if (HitResults.Num() == 0) {
		return;
	}

	float CharacterDamage{ 0.0f };
	IFighter* Fighter{ Cast<IFighter>(GetOwner()) };
	if (Fighter) {
		CharacterDamage = Fighter->GetDamage();
	}

	FDamageEvent DamageEvent;

	for (const FHitResult& Hit : HitResults) {
		AActor* TargetActor{ Hit.GetActor() };

		if (TargetsToIgnore.Contains(TargetActor)) {
			continue;
		}

		TargetActor->TakeDamage(
			CharacterDamage,
			DamageEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
		);

		TargetsToIgnore.Add(TargetActor);
	}
}

void UTraceComponent::HandlAttackComplete()
{
	TargetsToIgnore.Empty();
}

