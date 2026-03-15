// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitiesSystem/Character/BaseGASCharacter.h"

// Sets default values
ABaseGASCharacter::ABaseGASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");

	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(ASReplicationMode);
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

