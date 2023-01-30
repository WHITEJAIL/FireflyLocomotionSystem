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
	/** 动画实例的拥有者携带的角色运动组件实例 */
	UPROPERTY(BlueprintReadOnly, Category = "FireflyLocomotionSystem")
	UCharacterMovementComponent* OwnerCharacterMovement;

#pragma endregion


#pragma region LocationData

protected:
	virtual void UpdateLocationData(float DeltaSeconds);

protected:
	/** 动画实例的拥有者当前和上次更新的位移距离差 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomotionSystem|LocationData")
	float DisplacementSinceLastUpdate = 0.f;

	/** 动画实例的拥有者当前在世界坐标系中的位置 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomotionSystem|LocationData")
	FVector WorldLocation = FVector::ZeroVector;

	/** 动画实例的拥有者当前的位移速度值 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomotionSystem|LocationData")
	float DisplacementSpeed = 0.f;	

#pragma endregion


#pragma region RotationData

protected:
	virtual void UpdateRotationData();

protected:
	/** 动画实例的拥有者当前世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RotationData")
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

	/** 动画实例的拥有者当前速度矢量相对于自身坐标系的角度 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	float LocalVelocityDirectionAngle = 0.f;

#pragma endregion


#pragma region AccelerationData

protected:
	virtual void UpdateAccelerationData();

protected:
	/** 动画实例的拥有者当前是否拥有加速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	uint8 bHasAcceleration : 1;

	/** 动画实例的拥有者当前世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	FVector WorldAcceleration = FVector::ZeroVector;

	/** 动画实例的拥有者当前本地坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	FVector LocalAcceleration = FVector::ZeroVector;

	/** 动画实例的拥有者当前的回转方向矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	FVector PivotDirection = FVector::ZeroVector;

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

private:
	/** 当前更新是否是第一次更新是否 */
	bool bIsFirstUpdate = true;

#pragma endregion
};
