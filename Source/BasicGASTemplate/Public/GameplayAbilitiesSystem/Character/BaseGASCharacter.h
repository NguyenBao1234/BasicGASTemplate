// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <AbilitySystemInterface.h>
#include "AbilitySystemComponent.h"

#include "BaseGASCharacter.generated.h"

UCLASS()
class BASICGASTEMPLATE_API ABaseGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseGASCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|Abilities")
		UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|Abilities")
		class UBasicAttributeSet* BasicAttributesSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Abilities")
		EGameplayEffectReplicationMode ASReplicationMode = EGameplayEffectReplicationMode::Mixed;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Abilities")
		TArray<TSubclassOf<UGameplayAbility>> DefaultStartAbilities;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Grant, Give, Ability"))
		TArray<FGameplayAbilitySpecHandle> GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Revoke, Remove,Delete,Clear, Ability"))
		void RevokeAbilities(TArray<FGameplayAbilitySpecHandle> AbilitiesToRevoke);
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Send, Event, Ability"))
		void SendAbilitiesChangeEvent();
};
