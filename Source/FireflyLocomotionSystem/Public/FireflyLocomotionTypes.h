// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireflyLocomotionTypes.generated.h"

/** 八方向的枚举类型 */
UENUM(BlueprintType)
enum class EFireflyLocomotionDirectionType : uint8
{
	Forward,
	Backward,
	Right,
	Left,
	RightForward,
	RightBackward,
	LeftForward,
	LeftBackward
};

/** 动画系统选择的根骨骼航向角偏移更新的计算方式 */
UENUM(BlueprintType)
enum class EFireflyRootYawOffsetModeType : uint8
{
	BlendOut,
	Hold,
	Accumulate
};