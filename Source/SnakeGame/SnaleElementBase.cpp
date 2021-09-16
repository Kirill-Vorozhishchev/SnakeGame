// Fill out your copyright notice in the Description page of Project Settings.


#include "SnaleElementBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Sets default values
ASnaleElementBase::ASnaleElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MehComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ASnaleElementBase::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnaleElementBase::HandleBeginOverLap);
}
// Called every frame
void ASnaleElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnaleElementBase::SetFirstElementType_Implementation()
{

}

void ASnaleElementBase::Interact(AActor* Interactor)
{

}

void ASnaleElementBase::HandleBeginOverLap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
	}
}

