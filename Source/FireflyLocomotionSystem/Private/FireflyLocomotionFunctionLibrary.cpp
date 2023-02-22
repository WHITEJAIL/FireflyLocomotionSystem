// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyLocomotionFunctionLibrary.h"

#include "FireflyCharacterMovementComponent.h"

UCharacterMovementComponent* UFireflyLocomotionFunctionLibrary::GetCharacterMovement(APawn* InPawn)
{
	if (!IsValid(InPawn))
	{
		return nullptr;
	}

	UActorComponent* Comp = InPawn->GetComponentByClass(UCharacterMovementComponent::StaticClass());
	if (IsValid(Comp))
	{
		return Cast<UCharacterMovementComponent>(Comp);
	}

	return nullptr;
}

UFireflyCharacterMovementComponent* UFireflyLocomotionFunctionLibrary::GetFireflyCharacterMovement(APawn* InPawn)
{
	if (!IsValid(InPawn))
	{
		return nullptr;
	}

	UActorComponent* Comp = InPawn->GetComponentByClass(UFireflyCharacterMovementComponent::StaticClass());
	if (IsValid(Comp))
	{
		return Cast<UFireflyCharacterMovementComponent>(Comp);
	}

	return nullptr;
}

EFireflyLocomotionDirectionType UFireflyLocomotionFunctionLibrary::SelectLocomotionDirectionFromAngle(float Angle,
	EFireflyLocomotionDirectionMethod DirectionMethod)
{
	float AbsAngle = FMath::Abs<float>(Angle);
	EFireflyLocomotionDirectionType Result = EFireflyLocomotionDirectionType::Forward;

	switch (DirectionMethod)
	{
	case EFireflyLocomotionDirectionMethod::TwoDirection:
		{
			if (AbsAngle <= 75.f)
			{
				Result = EFireflyLocomotionDirectionType::Forward;
			}
			else if (AbsAngle >= 115.f)
			{
				Result = EFireflyLocomotionDirectionType::Backward;
			}
			else if (AbsAngle > 75.f && AbsAngle <= 115.f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::Right
					: EFireflyLocomotionDirectionType::Left;
			}
			else
			{
				Result = EFireflyLocomotionDirectionType::Forward;
			}
			break;
		}
	case EFireflyLocomotionDirectionMethod::FourDirection:
		{
			if (AbsAngle <= 45.f)
			{
				Result = EFireflyLocomotionDirectionType::Forward;
			}
			else if (AbsAngle >= 135.f)
			{
				Result = EFireflyLocomotionDirectionType::Backward;
			}
			else if (AbsAngle > 45.f && AbsAngle <= 135.f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::Right
					: EFireflyLocomotionDirectionType::Left;
			}
			else
			{
				Result = EFireflyLocomotionDirectionType::Forward;
			}
			break;
		}
	case EFireflyLocomotionDirectionMethod::SixDirection:
		{
			if (AbsAngle <= 30.f)
			{
				Result = EFireflyLocomotionDirectionType::Forward;
			}
			else if (AbsAngle >= 150.f)
			{
				Result = EFireflyLocomotionDirectionType::Backward;
			}
			else if (AbsAngle > 30.f && AbsAngle <= 90.f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::FwdRight
					: EFireflyLocomotionDirectionType::FwdLeft;
			}
			else if (AbsAngle > 90.f && AbsAngle <= 150.f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::BwdRight
					: EFireflyLocomotionDirectionType::BwdLeft;
			}
			else
			{
				Result = EFireflyLocomotionDirectionType::Forward;
			}
			break;
		}
	case EFireflyLocomotionDirectionMethod::EightDirection:
		{
			if (AbsAngle <= 22.5f)
			{
				Result = EFireflyLocomotionDirectionType::Forward;
			}
			else if (AbsAngle >= 157.5f)
			{
			Result = EFireflyLocomotionDirectionType::Backward;
			}
			else if (AbsAngle > 22.5f && AbsAngle <= 67.5f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::FwdRight
					: EFireflyLocomotionDirectionType::FwdLeft;
			}
			else if (AbsAngle > 67.5f && AbsAngle <= 112.5f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::Right
					: EFireflyLocomotionDirectionType::Left;
			}
			else
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::BwdRight
					: EFireflyLocomotionDirectionType::BwdLeft;
			}
			break;
		}
	}

	return Result;
}

EFireflyLocomotionDirectionType UFireflyLocomotionFunctionLibrary::GetOppositeCardinalDirection(
	EFireflyLocomotionDirectionType InDirection)
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
		case EFireflyLocomotionDirectionType::FwdRight:
		{
			Result = EFireflyLocomotionDirectionType::BwdLeft;
			break;
		}
		case EFireflyLocomotionDirectionType::BwdRight:
		{
			Result = EFireflyLocomotionDirectionType::FwdLeft;
			break;
		}
		case EFireflyLocomotionDirectionType::FwdLeft:
		{
			Result = EFireflyLocomotionDirectionType::BwdRight;
			break;
		}
		case EFireflyLocomotionDirectionType::BwdLeft:
		{
			Result = EFireflyLocomotionDirectionType::FwdRight;
			break;
		}
	}

	return Result;
}

UAnimSequenceBase* UFireflyLocomotionFunctionLibrary::GetAnimFromDirection(EFireflyLocomotionDirectionType Direction,
	const FFireflyLocomotionDirectionalAnimationSet& AnimSet)
{
	UAnimSequenceBase* OutAnim = nullptr;
	switch (Direction)
	{
	case EFireflyLocomotionDirectionType::Backward: OutAnim = AnimSet.Anim_Backward; break;
	case EFireflyLocomotionDirectionType::BwdLeft: OutAnim = AnimSet.Anim_BwdLeft; break;
	case EFireflyLocomotionDirectionType::BwdRight: OutAnim = AnimSet.Anim_BwdRight; break;
	case EFireflyLocomotionDirectionType::Forward: OutAnim = AnimSet.Anim_Forward; break;
	case EFireflyLocomotionDirectionType::FwdLeft: OutAnim = AnimSet.Anim_FwdLeft; break;
	case EFireflyLocomotionDirectionType::FwdRight: OutAnim = AnimSet.Anim_FwdRight; break;
	case EFireflyLocomotionDirectionType::Left: OutAnim = AnimSet.Anim_Left; break;
	case EFireflyLocomotionDirectionType::Right: OutAnim = AnimSet.Anim_Right; break;
	}

	return OutAnim;
}
