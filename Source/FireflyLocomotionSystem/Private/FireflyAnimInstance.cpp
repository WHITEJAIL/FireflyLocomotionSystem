// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyAnimInstance.h"

#include "FireflyCharacterMovementComponent.h"
#include "FireflyLocomotionFunctionLibrary.h"
#include "KismetAnimationLibrary.h"

void UFireflyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerFireflyCharacterMovement = UFireflyLocomotionFunctionLibrary::GetFireflyCharacterMovement(TryGetPawnOwner());
	MovementGait = EFireflyMovementGait::Jog;
	TargetGait = EFireflyMovementGait::Jog;
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
	
	if (!IsValid(OwnerFireflyCharacterMovement))
	{
		return;
	}

	UpdateLocationData();
	UpdateRotationData();
	UpdateVelocityData();
	UpdateAccelerationData();
	UpdateDirectionData();
	UpdateCharacterState();
	UpdateRootYawOffset();

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

	WorldVelocityLastUpdate = WorldVelocity;
	WorldVelocity = TryGetPawnOwner()->GetVelocity();	
	LocalVelocity = WorldRotation.UnrotateVector(WorldVelocity);
	bHasVelocity = !FMath::IsNearlyEqual(LocalVelocity.SizeSquared2D(), 0.f, 1.e-6);
	const float NewMovementSpeedRate = UKismetMathLibrary::SafeDivide(LocalVelocity.X, OwnerFireflyCharacterMovement->MaxNaturalMovementSpeed);
	MovementSpeedLeanRate = UKismetMathLibrary::Lerp(MovementSpeedLeanRate, NewMovementSpeedRate, GetDeltaSeconds() * LeanCalculationLerpSpeed);
	
	LocalVelocityDirectionAngle = UKismetAnimationLibrary::CalculateDirection(WorldVelocity, WorldRotation);
	LocalVelocityDirectionAngleWithOffset = LocalVelocityDirectionAngle - RootYawOffset;	
}

void UFireflyAnimInstance::UpdateAccelerationData_Implementation()
{
	WorldInputAcceleration = OwnerFireflyCharacterMovement->GetCurrentAcceleration();
	WorldVelocityAcceleration = UKismetMathLibrary::Divide_VectorFloat(WorldVelocity - WorldVelocityLastUpdate, GetDeltaSeconds());
	LocalAcceleration = WorldRotation.UnrotateVector(WorldInputAcceleration);
	bHasAcceleration = !FMath::IsNearlyEqual(LocalAcceleration.SizeSquared2D(), 0.f, 1.e-6);
	RelativeAccelerationAmount = CalculateRelativeAccelerationAmount();
}

void UFireflyAnimInstance::UpdateDirectionData_Implementation()
{
	LocomotionDirection_4Way = UFireflyLocomotionFunctionLibrary::SelectLocomotionDirectionFromAngle(
		LocalVelocityDirectionAngle, EFireflyLocomotionDirectionMethod::FourDirection);
	LocomotionDirection_8Way = UFireflyLocomotionFunctionLibrary::SelectLocomotionDirectionFromAngle(
		LocalVelocityDirectionAngle, EFireflyLocomotionDirectionMethod::EightDirection);

	VelocityBlendData = SmoothVelocityBlendData(VelocityBlendData, 
		CalculateVelocityBlendData(), GetDeltaSeconds(), 15.f);
		
	LeanAmountData = SmoothLeanAmountData(LeanAmountData,
		FFireflyLeanAmountData(RelativeAccelerationAmount.X, RelativeAccelerationAmount.Y),
		GetDeltaSeconds(), LeanCalculationLerpSpeed);
}

FFireflyVelocityBlendData UFireflyAnimInstance::SmoothVelocityBlendData(FFireflyVelocityBlendData Current,
	FFireflyVelocityBlendData Target, float DeltaSeconds, float InterpSpeed)
{
	return FFireflyVelocityBlendData(
		UKismetMathLibrary::FInterpTo(Current.Forward, Target.Forward, DeltaSeconds, InterpSpeed),
		UKismetMathLibrary::FInterpTo(Current.Backward, Target.Backward, DeltaSeconds, InterpSpeed),
		UKismetMathLibrary::FInterpTo(Current.Left, Target.Left, DeltaSeconds, InterpSpeed),
		UKismetMathLibrary::FInterpTo(Current.Right, Target.Right, DeltaSeconds, InterpSpeed)
	);
}

FFireflyVelocityBlendData UFireflyAnimInstance::CalculateVelocityBlendData() const
{
	const FVector LocalVelocityUnit = UKismetMathLibrary::Normal(LocalVelocity);

	const float LocalVelocityUnitX = LocalVelocityUnit.X;
	const float LocalVelocityUnitY = LocalVelocityUnit.Y;
	const float LocalVelocityUnitZ = LocalVelocityUnit.Z;

	const float LocalSum = FMath::Abs<float>(LocalVelocityUnitX) + FMath::Abs<float>(LocalVelocityUnitY)
		+ FMath::Abs<float>(LocalVelocityUnitZ);

	const FVector LocalRelativeDirection = FVector(
		UKismetMathLibrary::SafeDivide(LocalVelocityUnitX, LocalSum),
		UKismetMathLibrary::SafeDivide(LocalVelocityUnitY, LocalSum),
		UKismetMathLibrary::SafeDivide(LocalVelocityUnitZ, LocalSum));

	return FFireflyVelocityBlendData(
		UKismetMathLibrary::FClamp(LocalRelativeDirection.X, 0.f, 1.f),
		-UKismetMathLibrary::FClamp(LocalRelativeDirection.X, -1.f, 0.f),
		-UKismetMathLibrary::FClamp(LocalRelativeDirection.Y, -1.f, 0.f),
		UKismetMathLibrary::FClamp(LocalRelativeDirection.Y, 0.f, 1.f));
}

FFireflyLeanAmountData UFireflyAnimInstance::SmoothLeanAmountData(FFireflyLeanAmountData Current,
	FFireflyLeanAmountData Target, float DeltaSeconds, float InterpSpeed)
{
	return FFireflyLeanAmountData(
		UKismetMathLibrary::Lerp(Current.ForwardDirection, Target.ForwardDirection, DeltaSeconds * InterpSpeed),
		UKismetMathLibrary::Lerp(Current.RightDirection, Target.RightDirection, DeltaSeconds * InterpSpeed)
	);
}

FVector UFireflyAnimInstance::CalculateRelativeAccelerationAmount()
{
	if (UKismetMathLibrary::Dot_VectorVector(WorldVelocityAcceleration, WorldVelocity) > 0.f)
	{
		const float MaxAcceleration = OwnerFireflyCharacterMovement->GetMaxAcceleration();
		return TryGetPawnOwner()->GetActorRotation().UnrotateVector(UKismetMathLibrary::Divide_VectorFloat(
			WorldVelocityAcceleration.GetClampedToMaxSize(MaxAcceleration), MaxAcceleration == 0.f ? 1.f : MaxAcceleration));
	}

	const float MaxBrakingDeceleration = OwnerFireflyCharacterMovement->GetMaxBrakingDeceleration();
	return TryGetPawnOwner()->GetActorRotation().UnrotateVector(UKismetMathLibrary::Divide_VectorFloat(
		WorldVelocityAcceleration.GetClampedToMaxSize(MaxBrakingDeceleration), MaxBrakingDeceleration == 0.f ? 1.f : MaxBrakingDeceleration));
}

void UFireflyAnimInstance::UpdateCharacterState_Implementation()
{
	const bool bWasCrouchingLastUpdate = bIsCrouching;
	bIsCrouching = OwnerFireflyCharacterMovement->IsCrouching();
	bCrouchStateChange = bIsCrouching != bWasCrouchingLastUpdate;

	bIsJumpingToApex = false;
	bIsFallingToGround = false;
	if (OwnerFireflyCharacterMovement->MovementMode == MOVE_Falling)
	{
		WorldVelocity.Z > 0.f ? bIsJumpingToApex = true : bIsFallingToGround = true;
	}

	bIsRunningIntoWall = LocalAcceleration.Size2D() > 0.1f && LocalVelocity.Size2D() < 200.f
		&&UKismetMathLibrary::InRange_FloatFloat(FVector::DotProduct(
			LocalAcceleration.GetSafeNormal(1e-4), LocalVelocity.GetSafeNormal(1e-4)),
			-0.6, 0.6);
	
	MovementGait = OwnerFireflyCharacterMovement->GetCurrentMovementGait();
	TargetGait = OwnerFireflyCharacterMovement->GetTargetMovementGait();
	bIsAnyMontagePlaying = IsAnyMontagePlaying();
}

void UFireflyAnimInstance::UpdateRootYawOffset_Implementation()
{
	if (RootYawOffsetMode == EFireflyRootYawOffsetModeType::Accumulate)
	{
		SetRootYawOffset(RootYawOffset - YawDeltaSinceLastUpdate);
	}

	if (RootYawOffsetMode == EFireflyRootYawOffsetModeType::BlendOut)
	{
		SetRootYawOffset(UKismetMathLibrary::FloatSpringInterp(RootYawOffset, 0.f, RootYawOffsetSpringState, 
			80.f, 1.f, GetDeltaSeconds(), 1.f, 0.5f));
	}

	RootYawOffsetMode = EFireflyRootYawOffsetModeType::BlendOut;
}

void UFireflyAnimInstance::SetRootYawOffset_Implementation(float InRootYawOffset)
{
	if (!bEnableRootYawOffset)
	{
		RootYawOffset = 0.f;
	}

	// We clamp the offset because at large offsets the character has to aim too far backwards, which over twists the spine.
	// The turn in place animations will usually keep up with the offset, but this clamp will cause the feet to slide if the user rotates the camera too quickly.
	// If desired, this clamp could be replaced by having aim animations that can go up to 180 degrees or by triggering turn in place animations more aggressively.

	FVector2D CurrentRange = bIsCrouching ? RootYawOffsetAngleRangeCrouched : RootYawOffsetAngleRange;
	RootYawOffset = CurrentRange.X != CurrentRange.Y ? UKismetMathLibrary::ClampAngle(FRotator::NormalizeAxis(InRootYawOffset),
		CurrentRange.X, CurrentRange.Y) : FRotator::NormalizeAxis(InRootYawOffset);
}