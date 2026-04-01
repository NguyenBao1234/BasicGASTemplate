// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitiesSystem/Character/BaseGASCharacter.h"

#include "GameplayAbilitiesSystem/AttributeSet/BasicAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
// Sets default values
ABaseGASCharacter::ABaseGASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(ASReplicationMode);

	BasicAttributesSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributesSet"));
}

// Called when the game starts or when spawned
void ABaseGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComp != nullptr)
	{
		AbilitySystemComp->InitAbilityActorInfo(this,this);
	}
	GrantAbilities(DefaultStartAbilities);
}

void ABaseGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (AbilitySystemComp != nullptr)
	{
		AbilitySystemComp->InitAbilityActorInfo(this,this);
	}
}

// Called every frame
void ABaseGASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TArray<FGameplayAbilitySpecHandle> ABaseGASCharacter::GrantAbilities(
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitySystemComp) return TArray<FGameplayAbilitySpecHandle>();
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;

	for (TSubclassOf<UGameplayAbility> AToGrant : AbilitiesToGrant)
	{
		auto GAspec = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(AToGrant, 1, 0));
		GrantedAbilities.Add(GAspec);
	}
	SendAbilitiesChangeEvent();
	return GrantedAbilities;
}

void ABaseGASCharacter::RevokeAbilities(TArray<FGameplayAbilitySpecHandle> AbilitiesToRevoke)
{
	if (!AbilitySystemComp) return;

	for (auto AToRevoke : AbilitiesToRevoke)
	{
		AbilitySystemComp->ClearAbility(AToRevoke);
	}
	SendAbilitiesChangeEvent();
}

void ABaseGASCharacter::SendAbilitiesChangeEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Abilities.Changed"));
	EventData.Instigator = this;
	EventData.Target = this;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

