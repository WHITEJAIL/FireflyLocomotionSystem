// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyAnimInstance.h"

#include "FireflyLocomotionFunctionLibrary.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UFireflyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UFireflyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UFireflyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!IsValid(TryGetPawnOwner()))
	{
		return;
	}

	OwnerCharacterMovement = UFireflyLocomotionFunctionLibrary::GetCharacterMovement(TryGetPawnOwner());
	if (!IsValid(OwnerCharacterMovement))
	{
		return;
	}

	UpdateLocationData(DeltaSeconds);
	UpdateRotationData();
	UpdateVelocityData();
	UpdateAccelerationData();
	UpdateCharacterState();

	bIsFirstUpdate = false;
}

void UFireflyAnimInstance::UpdateLocationData(float DeltaSeconds)
{
	DisplacementSinceLastUpdate = (GetOwningActor()->GetActorLocation() - WorldLocation).Size();
	WorldLocation = GetOwningActor()->GetActorLocation();
	DisplacementSpeed = (DeltaSeconds != 0.0f) ? (DisplacementSinceLastUpdate / DeltaSeconds) : 0.0f;

	if (bIsFirstUpdate)
	{
		DisplacementSinceLastUpdate = 0.f;
		DisplacementSpeed = 0.f;
	}
}

void UFireflyAnimInstance::UpdateRotationData()
{
	WorldRotation = TryGetPawnOwner()->GetActorRotation();
}

void UFireflyAnimInstance::UpdateVelocityData()
{
	bool bWasMovingLastUpdate = !LocalVelocity.IsZero();

	WorldVelocity = TryGetPawnOwner()->GetVelocity();
	LocalVelocity = WorldRotation.UnrotateVector(WorldVelocity);
	bHasVelocity = !FMath::IsNearlyEqual(LocalVelocity.SizeSquared2D(), 0.f, 1.e-6);
	LocalVelocityDirectionAngle = UKismetAnimationLibrary::CalculateDirection(WorldVelocity, WorldRotation);	
}

void UFireflyAnimInstance::UpdateAccelerationData()
{
	WorldAcceleration = OwnerCharacterMovement->GetCurrentAcceleration();
	LocalAcceleration = WorldRotation.UnrotateVector(WorldAcceleration);
	bHasAcceleration = !FMath::IsNearlyEqual(LocalAcceleration.SizeSquared2D(), 0.f, 1.e-6);
	PivotDirection = UKismetMathLibrary::Normal(UKismetMathLibrary::VLerp(PivotDirection, UKismetMathLibrary::Normal(WorldAcceleration), 0.5f));
}

void UFireflyAnimInstance::UpdateCharacterState()
{
	bIsCrouching = OwnerCharacterMovement->IsCrouching();

	bIsJumpingToApex = false;
	bIsFallingToGround = false;
	if (OwnerCharacterMovement->MovementMode == MOVE_Falling)
	{
		WorldVelocity.Z > 0.f ? bIsJumpingToApex = true : bIsFallingToGround = true;
	}
}
