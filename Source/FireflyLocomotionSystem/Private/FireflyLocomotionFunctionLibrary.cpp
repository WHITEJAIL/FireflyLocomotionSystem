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