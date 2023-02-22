// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyLocomotionAnimSet.h"

UFireflyLocomotionAnimSet::UFireflyLocomotionAnimSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FPrimaryAssetId UFireflyLocomotionAnimSet::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("LocomotionAnimSet"), GetFName());
}
