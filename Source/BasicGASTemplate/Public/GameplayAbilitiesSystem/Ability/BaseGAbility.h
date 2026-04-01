// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGAbility.generated.h"

/**
 * 
 */
UCLASS()
class BASICGASTEMPLATE_API UBaseGAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	FName AbilityName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	bool bDisplayInAbilityBar = false;
};
