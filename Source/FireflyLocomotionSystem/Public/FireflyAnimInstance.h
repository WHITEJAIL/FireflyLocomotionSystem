// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FireflyAnimInstance.generated.h"

class UCharacterMovementComponent;

/**  */
UCLASS()
class FIREFLYLOCOMOTIONSYSTEM_API UFireflyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

#pragma region AnimInstance

public:
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;

	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	// for linked anim instances, only called when the hosting node(s) are relevant
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

#pragma endregion


#pragma region CharacterMovement

protected:
	virtual void UpdateRotationData();

protected:
	/** 动画实例的拥有者携带的角色运动组件实例 */
	UPROPERTY(BlueprintReadOnly, Category = "FireflyLocomotionSystem")
	UCharacterMovementComponent* OwnerCharacterMovement;

#pragma endregion


#pragma region RotationData

protected:
	/** 动画实例的拥有者当前世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	FRotator WorldRotation = FRotator::ZeroRotator;

#pragma endregion


#pragma region VelocityData

protected:
	virtual void UpdateVelocityData();

protected:
	/** 动画实例的拥有者当前是否拥有速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	uint8 bHasVelocity : 1;

	/** 动画实例的拥有者当前世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	FVector WorldVelocity = FVector::ZeroVector;

	/** 动画实例的拥有者当前本地坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	FVector LocalVelocity = FVector::ZeroVector;

	/** 动画实例的拥有者当前是否拥有加速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	uint8 bHasAcceleration : 1;

	/** 动画实例的拥有者当前世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	FVector WorldAcceleration = FVector::ZeroVector;

	/** 动画实例的拥有者当前本地坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	FVector LocalAcceleration = FVector::ZeroVector;

#pragma endregion


#pragma region CharacterState

protected:
	virtual void UpdateCharacterState();

protected:
	/** 动画实例的拥有者是否在蹲伏中 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsCrouching : 1;

	/** 动画实例的拥有者是否处于跳跃上升状态 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsJumpingToApex : 1;

	/** 动画实例的拥有者是否处于空中下落状态 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsFallingToGround : 1;

#pragma endregion
};
