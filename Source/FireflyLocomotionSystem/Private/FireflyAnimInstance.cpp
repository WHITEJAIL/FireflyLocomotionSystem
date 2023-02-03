// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyAnimInstance.h"

#include "FireflyLocomotionFunctionLibrary.h"
#include "KismetAnimationLibrary.h"
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

	UpdateLocationData();
	UpdateRotationData();
	UpdateVelocityData();
	UpdateAccelerationData();
	UpdateDirectionData();
	UpdateCharacterState();

	bIsFirstUpdate = false;
}

void UFireflyAnimInstance::UpdateLocationData_Implementation()
{
	DisplacementSinceLastUpdate = (GetOwningActor()->GetActorLocation() - WorldLocation).Size();
	WorldLocation = GetOwningActor()->GetActorLocation();
	DisplacementSpeed = (GetDeltaSeconds() != 0.0f) ? (DisplacementSinceLastUpdate / GetDeltaSeconds()) : 0.0f;

	if (bIsFirstUpdate)
	{
		DisplacementSinceLastUpdate = 0.f;
		DisplacementSpeed = 0.f;
	}
}

void UFireflyAnimInstance::UpdateRotationData_Implementation()
{
	YawDeltaSinceLastUpdate = TryGetPawnOwner()->GetActorRotation().Yaw - WorldRotation.Yaw;
	YawDeltaSpeed = UKismetMathLibrary::SafeDivide(YawDeltaSinceLastUpdate, GetDeltaSeconds());
	WorldRotation = TryGetPawnOwner()->GetActorRotation();

	if (bIsFirstUpdate)
	{
		YawDeltaSinceLastUpdate = 0.f;
	}
}

void UFireflyAnimInstance::UpdateVelocityData_Implementation()
{
	bool bWasMovingLastUpdate = !LocalVelocity.IsZero();

	WorldVelocity = TryGetPawnOwner()->GetVelocity();
	LocalVelocity = WorldRotation.UnrotateVector(WorldVelocity);
	bHasVelocity = !FMath::IsNearlyEqual(LocalVelocity.SizeSquared2D(), 0.f, 1.e-6);

	LocalVelocityDirectionAngleLastUpdate = LocalVelocityDirectionAngle;
	LocalVelocityDirectionAngleWithOffsetLastUpdate = LocalVelocityDirectionAngleWithOffset;

	LocalVelocityDirectionAngle = UKismetAnimationLibrary::CalculateDirection(WorldVelocity, WorldRotation);
	LocalVelocityDirectionAngleWithOffset = LocalVelocityDirectionAngle - RootYawOffset;

	if (bIsFirstUpdate)
	{
		LocalVelocityDirectionAngleLastUpdate = 0.f;
		LocalVelocityDirectionAngleWithOffsetLastUpdate = 0.f;
	}
}

void UFireflyAnimInstance::UpdateAccelerationData_Implementation()
{
	WorldAcceleration = OwnerCharacterMovement->GetCurrentAcceleration();
	LocalAcceleration = WorldRotation.UnrotateVector(WorldAcceleration);
	bHasAcceleration = !FMath::IsNearlyEqual(LocalAcceleration.SizeSquared2D(), 0.f, 1.e-6);
	PivotDirection = UKismetMathLibrary::Normal(UKismetMathLibrary::VLerp(
		PivotDirection, UKismetMathLibrary::Normal(WorldAcceleration), 0.5f));
}

void UFireflyAnimInstance::UpdateDirectionData_Implementation()
{
	LocalVelocityDirectionLastUpdate = LocalVelocityDirection;
	LocalVelocityDirectionNoOffsetLastUpdate = LocalVelocityDirectionNoOffset;

	LocalVelocityDirection = SelectLocomotionDirectionFromAngle(LocalVelocityDirectionAngleWithOffset);
	LocalVelocityDirectionNoOffset = SelectLocomotionDirectionFromAngle(LocalVelocityDirectionAngle);

	PivotDirectionFromAcceleration = GetOppositeCardinalDirection(SelectLocomotionDirectionFromAngle(
		UKismetAnimationLibrary::CalculateDirection(PivotDirection, WorldRotation)));

	if (bIsFirstUpdate)
	{
		LocalVelocityDirectionLastUpdate = EFireflyLocomotionDirectionType::Forward;
		LocalVelocityDirectionNoOffsetLastUpdate = EFireflyLocomotionDirectionType::Forward;
	}
}

EFireflyLocomotionDirectionType UFireflyAnimInstance::SelectLocomotionDirectionFromAngle(float Angle)
{
	float AbsAngle = FMath::Abs<float>(Angle);

	if (AbsAngle <= 22.5f)
	{
		return EFireflyLocomotionDirectionType::Forward;
	}
	else if (AbsAngle >= 157.5f)
	{
		return EFireflyLocomotionDirectionType::Backward;
	}
	else if (AbsAngle > 22.5f && AbsAngle <= 67.5f)
	{
		return Angle > 0.f ? EFireflyLocomotionDirectionType::RightForward
			: EFireflyLocomotionDirectionType::LeftForward;
	}
	else if (AbsAngle > 67.5f && AbsAngle <= 112.5f)
	{
		return Angle > 0.f ? EFireflyLocomotionDirectionType::Right
			: EFireflyLocomotionDirectionType::Left;
	}
	else
	{
		return Angle > 0.f ? EFireflyLocomotionDirectionType::RightBackward
			: EFireflyLocomotionDirectionType::LeftBackward;
	}
}

EFireflyLocomotionDirectionType UFireflyAnimInstance::GetOppositeCardinalDirection(EFireflyLocomotionDirectionType InDirection)
{
	EFireflyLocomotionDirectionType Result = EFireflyLocomotionDirectionType::Forward;
	switch (InDirection)
	{
		case EFireflyLocomotionDirectionType::Forward:
		{
			Result = EFireflyLocomotionDirectionType::Backward;
			break;
		}
		case EFireflyLocomotionDirectionType::Backward:
		{
			Result = EFireflyLocomotionDirectionType::Forward;
			break;
		}
		case EFireflyLocomotionDirectionType::Right:
		{
			Result = EFireflyLocomotionDirectionType::Left;
			break;
		}
		case EFireflyLocomotionDirectionType::Left:
		{
			Result = EFireflyLocomotionDirectionType::Right;
			break;
		}
		case EFireflyLocomotionDirectionType::RightForward:
		{
			Result = EFireflyLocomotionDirectionType::LeftBackward;
			break;
		}
		case EFireflyLocomotionDirectionType::RightBackward:
		{
			Result = EFireflyLocomotionDirectionType::LeftForward;
			break;
		}
		case EFireflyLocomotionDirectionType::LeftForward:
		{
			Result = EFireflyLocomotionDirectionType::RightBackward;
			break;
		}
		case EFireflyLocomotionDirectionType::LeftBackward:
		{
			Result = EFireflyLocomotionDirectionType::RightForward;
			break;
		}
	}

	return Result;
}

void UFireflyAnimInstance::UpdateCharacterState_Implementation()
{
	const bool bWasCrouchingLastUpdate = bIsCrouching;
	bIsCrouching = OwnerCharacterMovement->IsCrouching();
	bCrouchStateChange = bIsCrouching != bWasCrouchingLastUpdate;

	bIsJumpingToApex = false;
	bIsFallingToGround = false;
	if (OwnerCharacterMovement->MovementMode == MOVE_Falling)
	{
		WorldVelocity.Z > 0.f ? bIsJumpingToApex = true : bIsFallingToGround = true;
	}

	bIsRunningIntoWall = LocalAcceleration.Size2D() > 0.1f && LocalVelocity.Size2D() < 200.f
		&&UKismetMathLibrary::InRange_FloatFloat(FVector::DotProduct(
			LocalAcceleration.GetSafeNormal(1e-4), LocalVelocity.GetSafeNormal(1e-4)),
			-0.6, 0.6);
}

void UFireflyAnimInstance::UpdateRootYawOffset_Implementation()
{
}

void UFireflyAnimInstance::SetRootYawOffset_Implementation(float InRootYawOffset)
{
}