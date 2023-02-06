// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyLocomotionFunctionLibrary.h"

#include "FireflyCharacterMovementComponent.h"

UCharacterMovementComponent* UFireflyLocomotionFunctionLibrary::GetCharacterMovement(APawn* InPawn)
{
	UActorComponent* Comp = InPawn->GetComponentByClass(UCharacterMovementComponent::StaticClass());
	if (IsValid(Comp))
	{
		return Cast<UCharacterMovementComponent>(Comp);
	}

	return nullptr;
}

UFireflyCharacterMovementComponent* UFireflyLocomotionFunctionLibrary::GetFireflyCharacterMovement(APawn* InPawn)
{
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
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::RightForward
					: EFireflyLocomotionDirectionType::LeftForward;
			}
			else if (AbsAngle > 90.f && AbsAngle <= 150.f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::RightBackward
					: EFireflyLocomotionDirectionType::LeftBackward;
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
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::RightForward
					: EFireflyLocomotionDirectionType::LeftForward;
			}
			else if (AbsAngle > 67.5f && AbsAngle <= 112.5f)
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::Right
					: EFireflyLocomotionDirectionType::Left;
			}
			else
			{
				Result = Angle > 0.f ? EFireflyLocomotionDirectionType::RightBackward
					: EFireflyLocomotionDirectionType::LeftBackward;
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