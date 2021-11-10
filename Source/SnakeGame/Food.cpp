// Fill out your copyright notice in the Description page of Project Settings.

#include "Food.h"
#include "SnakeBase.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(-350, 0, 0));
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AFood::RandomVector()
{
	const int Height = (-500, 500);
	const int Width = (-1100, 1100);
	int x, y;
	x = rand() % 500 + (-500);
	y = rand() % 1100 + (-1100);

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (i == x && j == y)
			{
				
			}
		}
	}
}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->AddSnakeElement();
			Destroy();
			auto Food = Cast<AFood>(Interactor);
		    if (IsValid(Food))
			{

			}
		}
	}
}