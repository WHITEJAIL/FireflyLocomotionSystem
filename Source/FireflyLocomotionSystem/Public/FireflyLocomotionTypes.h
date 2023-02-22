// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireflyLocomotionTypes.generated.h"

/** 方向判定的方法 */
UENUM(BlueprintType)
enum class EFireflyLocomotionDirectionMethod : uint8
{
	TwoDirection,
	FourDirection,
	SixDirection,
	EightDirection
};

/** 八方向的枚举类型 */
UENUM(BlueprintType)
enum class EFireflyLocomotionDirectionType : uint8
{
	Forward,	
	Backward,
	Left,
	Right,
	FwdLeft,
	FwdRight,
	BwdLeft,
	BwdRight,
};

/** 动画系统选择的根骨骼航向角偏移更新的计算方式 */
UENUM(BlueprintType)
enum class EFireflyRootYawOffsetModeType : uint8
{
	BlendOut,
	Hold,
	Accumulate
};

/** 速度混合数据 */
USTRUCT(BlueprintType)
struct FFireflyVelocityBlendData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Forward = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Backward = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Left = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Right = 0.f;

	FFireflyVelocityBlendData() {}

	FFireflyVelocityBlendData(float InForward, float InBackward, float InLeft, float InRight)
		: Forward(InForward), Backward(InBackward), Left(InLeft), Right(InRight) {}
};

/** 八方向对应的动画序列 */
USTRUCT(BlueprintType)
struct FFireflyLocomotionDirectionalAnimationSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Forward;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Backward;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Left;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Right;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_FwdLeft;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_FwdRight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_BwdLeft;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_BwdRight;
};
