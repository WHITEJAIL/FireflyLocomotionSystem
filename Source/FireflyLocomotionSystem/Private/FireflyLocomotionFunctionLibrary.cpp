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

FTransform UFireflyLocomotionFunctionLibrary::ExtractBoneTransformFromAnimation(const UAnimSequence* Animation,
	FName BoneName, float Time, bool bComponentSpace)
{
	USkeleton* Skeleton = Animation->GetSkeleton();
	if (Skeleton == nullptr)
	{
		UE_LOG(LogAnimation, Error, TEXT("MotionExtractorModifier failed. Reason: Animation with invalid Skeleton. Animation: %s"),
			*GetNameSafe(Animation));

		return FTransform::Identity;
	}

	const int32 BoneIndex = Skeleton->GetReferenceSkeleton().FindBoneIndex(BoneName);
	if (BoneIndex == INDEX_NONE)
	{
		UE_LOG(LogAnimation, Error, TEXT("MotionExtractorModifier failed. Reason: Invalid Bone Index. BoneName: %s Animation: %s Skeleton: %s"),
			*BoneName.ToString(), *GetNameSafe(Animation), *GetNameSafe(Skeleton));

		return FTransform::Identity;
	}

	TArray<FBoneIndexType> RequiredBones;
	RequiredBones.Add(BoneIndex);
	Skeleton->GetReferenceSkeleton().EnsureParentsExistAndSort(RequiredBones);

	FBoneContainer BoneContainer(RequiredBones, false, *Skeleton);
	const FCompactPoseBoneIndex CompactPoseBoneIndex = BoneContainer.MakeCompactPoseIndex(FMeshPoseBoneIndex(BoneIndex));

	FCompactPose Pose;
	Pose.SetBoneContainer(&BoneContainer);

	FBlendedCurve Curve;
	Curve.InitFrom(BoneContainer);

	FAnimExtractContext Context(Time, false);
	UE::Anim::FStackAttributeContainer Attributes;
	FAnimationPoseData AnimationPoseData(Pose, Curve, Attributes);

	Animation->GetBonePose(AnimationPoseData, Context, true);

	check(Pose.IsValidIndex(CompactPoseBoneIndex));

	if (bComponentSpace)
	{
		FCSPose<FCompactPose> ComponentSpacePose;
		ComponentSpacePose.InitPose(Pose);

		return ComponentSpacePose.GetComponentSpaceTransform(CompactPoseBoneIndex);
	}

	return Pose[CompactPoseBoneIndex];
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