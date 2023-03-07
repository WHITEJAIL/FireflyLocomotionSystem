// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FireflyLocomotionTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "FireflyAnimInstance.generated.h"

enum class EFireflyMovementGait : uint8;
class UFireflyCharacterMovementComponent;

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

protected:
	/** 当前更新是否是第一次更新是否 */
	bool bIsFirstUpdate = true;

#pragma endregion


#pragma region CharacterMovement

protected:
	/** 动画实例的拥有者携带的角色运动组件实例 */
	UPROPERTY(BlueprintReadOnly, Category = "FireflyLocomotionSystem")
	UFireflyCharacterMovementComponent* OwnerFireflyCharacterMovement;

#pragma endregion


#pragma region LocationData

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void UpdateLocationData();
	virtual void UpdateLocationData_Implementation();

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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void UpdateRotationData();
	virtual void UpdateRotationData_Implementation();

protected:
	/** 动画实例的拥有者当前世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RotationData")
	FRotator WorldRotation = FRotator::ZeroRotator;

	/** 动画实例的拥有者当前航向角和上一次更新的插值 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RotationData")
	float YawDeltaSinceLastUpdate = 0.f;

	/** 动画实例的拥有者当前航向角插值更新的速度 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RotationData")
	float YawDeltaSpeed = 0.f;

#pragma endregion


#pragma region VelocityData

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void UpdateVelocityData();
	virtual void UpdateVelocityData_Implementation();

protected:
	/** 动画实例的拥有者当前是否拥有速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	uint8 bHasVelocity : 1;

	/** 动画实例的拥有者当前世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	FVector WorldVelocity = FVector::ZeroVector;

	/** 动画实例的拥有者上次更新的世界坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	FVector WorldVelocityLastUpdate = FVector::ZeroVector;

	/** 动画实例的拥有者当前本地坐标系的速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	FVector LocalVelocity = FVector::ZeroVector;

	/** 动画实例的拥有者当前速度值和其最大自然移动速度的比率 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	float MovementSpeedRate = 0.f;

	/** 动画实例的拥有者当前速度矢量相对于自身坐标系的角度 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	float LocalVelocityDirectionAngle = 0.f;

	/** 动画实例的拥有者当前速度矢量相对于自身坐标系的角度（考虑角色航向角的偏移） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	float LocalVelocityDirectionAngleWithOffset = 0.f;

	/** 动画实例的拥有者当前速度矢量相对于自身坐标系的角度（上一次更新） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	float LocalVelocityDirectionAngleLastUpdate = 0.f;

	/** 动画实例的拥有者当前速度矢量相对于自身坐标系的角度（考虑角色航向角的偏移）（上一次更新） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	float LocalVelocityDirectionAngleWithOffsetLastUpdate = 0.f;

#pragma endregion


#pragma region AccelerationData

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void UpdateAccelerationData();
	virtual void UpdateAccelerationData_Implementation();

protected:
	/** 动画实例的拥有者当前是否拥有加速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationDate")
	uint8 bHasAcceleration : 1;

	/** 动画实例的拥有者当前角色在世界坐标系的加速度矢量（基于输入） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationDate")
	FVector WorldInputAcceleration = FVector::ZeroVector;

	/** 动画实例的拥有者当前角色在世界坐标系的加速度矢量（基于速度） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationDate")
	FVector WorldVelocityAcceleration = FVector::ZeroVector;

	/** 动画实例的拥有者当前本地坐标系的加速度矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationDate")
	FVector LocalAcceleration = FVector::ZeroVector;

	/** 动画实例的拥有者当前的期望运动方向矢量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationDate")
	FVector PivotDirection = FVector::ZeroVector;

	/** 动画实例的拥有者当前的加速度比率 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationDate")
	FVector RelativeAccelerationAmount;

#pragma endregion


#pragma region DirectionData

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void UpdateDirectionData();
	virtual void UpdateDirectionData_Implementation();

	virtual FFireflyVelocityBlendData SmoothVelocityBlendData(FFireflyVelocityBlendData Current,
		FFireflyVelocityBlendData Target, float DeltaSeconds, float InterpSpeed);

	virtual FFireflyVelocityBlendData CalculateVelocityBlendData() const;

	virtual FFireflyLeanAmountData SmoothLeanAmountData(FFireflyLeanAmountData Current,
		FFireflyLeanAmountData Target, float DeltaSeconds, float InterpSpeed);

	virtual FVector CalculateRelativeAccelerationAmount();

protected:
	/** 动画实例的拥有者当前的速度方向 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionData")
	EFireflyLocomotionDirectionMethod DirectionMethod;

	/** 动画实例的拥有者开始移动时的方向 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionData")
	EFireflyLocomotionDirectionType StartDirection;

	/** 动画实例的拥有者当前的速度方向 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionData")
	EFireflyLocomotionDirectionType LocalVelocityDirection;

	/** 动画实例的拥有者当前的速度方向（不考虑角色航向角的偏移） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionData")
	EFireflyLocomotionDirectionType LocalVelocityDirectionNoOffset;

	/** 动画实例的拥有者当前的速度方向（上一次更新） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionData")
	EFireflyLocomotionDirectionType LocalVelocityDirectionLastUpdate;

	/** 动画实例的拥有者当前的速度方向（不考虑角色航向角的偏移）（上一次更新） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionData")
	EFireflyLocomotionDirectionType LocalVelocityDirectionNoOffsetLastUpdate;

	/** 动画实例的拥有者当前的加速度方向的回转方向（用于回转运动） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionData")
	EFireflyLocomotionDirectionType PivotDirectionFromAcceleration;

	/** 动画实例的拥有者当前速度混合数据 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionDate")
	FFireflyVelocityBlendData VelocityBlendData;

	/** 动画实例的拥有者当前倾斜幅度 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|DirectionDate")
	FFireflyLeanAmountData LeanAmountData;

#pragma endregion


#pragma region CharacterState

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void UpdateCharacterState();
	virtual void UpdateCharacterState_Implementation();

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

	/** 动画实例的拥有者是否更改了下蹲状态（站起或蹲下） */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bCrouchStateChange : 1;

	/** 动画实例的拥有者是否正紧挨着并朝着阻挡物移动 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsRunningIntoWall : 1;

	/** 动画实例当前是否在播放蒙太奇 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsAnyMontagePlaying : 1;

	/** 动画实例的拥有者的当前移动步态 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	EFireflyMovementGait MovementGait;

	/** 动画实例的拥有者上次更新的移动步态 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	EFireflyMovementGait MovementGaitLastUpdate;

	/** 动画实例的拥有者的期望移动步态 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	EFireflyMovementGait TargetGait;

	/** 动画实例的拥有者上次更新的期望移动步态 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityData")
	EFireflyMovementGait TargetGaitLastUpdate;

#pragma endregion


#pragma region RootYawOffset

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void UpdateRootYawOffset();
	virtual void UpdateRootYawOffset_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FireflyLocomoitionSystem, Meta = (BlueprintThreadSafe = true))
	void SetRootYawOffset(float InRootYawOffset);
	virtual void SetRootYawOffset_Implementation(float InRootYawOffset);

protected:
	/** 动画实例的拥有者当前是否允许计算根航向的偏移 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "FireflyLocomoitionSystem|RootYawOffset")
	bool bEnableRootYawOffset = true;

	/** 动画实例的拥有者当前航向角的偏移量 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RootYawOffset")
	float RootYawOffset = 0.f;

	/** 动画实例的拥有者当前计算航向角偏移量的浮点值弹跳状态 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RootYawOffset")
	FFloatSpringState RootYawOffsetSpringState;

	/** 动画实例的拥有者当前航向角偏移相关的曲线最终值 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RootYawOffset")
	float RootYawCurveValue = 0.f;

	/** 动画实例的拥有者当前航向角偏移的计算方式 */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RootYawOffset")
	EFireflyRootYawOffsetModeType RootYawOffsetMode;

	/** 动画实例的拥有者当前航向角偏移的范围 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "FireflyLocomoitionSystem|RootYawOffset", Meta = (ClampMin = -180, ClampMax = 180, UIMin = -180, UIMax = 180))
	FVector2D RootYawOffsetAngleRange = FVector2D(-120.f, 100.f);

	/** 动画实例的拥有者当前蹲伏时航向角偏移的范围 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "FireflyLocomoitionSystem|RootYawOffset", Meta = (ClampMin = -180, ClampMax = 180, UIMin = -180, UIMax = 180))
	FVector2D RootYawOffsetAngleRangeCrouched = FVector2D(-90.f, 80.f);

#pragma endregion
};
