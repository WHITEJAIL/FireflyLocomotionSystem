// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyAnimInstance.h"

#include "FireflyLocomotionFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	UpdateVelocityData();
	UpdateCharacterState();
}

void UFireflyAnimInstance::UpdateRotationData()
{
	WorldRotation = TryGetPawnOwner()->GetActorRotation();
}

void UFireflyAnimInstance::UpdateVelocityData()
{
	WorldVelocity = TryGetPawnOwner()->GetVelocity();
	LocalVelocity = WorldRotation.UnrotateVector(WorldVelocity);
	bHasVelocity = !FMath::IsNearlyEqual(LocalVelocity.SizeSquared2D(), 0.f, 1.e-6);

	WorldAcceleration = OwnerCharacterMovement->GetCurrentAcceleration();
	LocalAcceleration = WorldRotation.UnrotateVector(WorldAcceleration);
	bHasAcceleration = !FMath::IsNearlyEqual(LocalAcceleration.SizeSquared2D(), 0.f, 1.e-6);
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
