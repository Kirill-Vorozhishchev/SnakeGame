// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnaleElementBase.h"
#include "Interactable.h"
#include "Food.h"
#include "random"
#include "Wall.h"


// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementsSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementsSpeed);
	AddSnakeElement(5);
	CreateFoodActor();
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num()*ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnaleElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnaleElementBase>(SnaleElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
		}
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);
	
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
		
	}
	
	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
		//(123+)
		SnakeElements[i]->ToggleVisible();
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
	//(123+)
	SnakeElements[0]->ToggleVisible();
}

void ASnakeBase::SnakeElementOverlap(ASnaleElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);

		}
	}
}

//Рандомное появление актора в пределах поля!
void ASnakeBase::CreateFoodActor()
{
	const int Height = (-400, 400);
	const int Width = (-950, 950);
	int x, y;
	x = rand() % 800 + (-400);	//предел поля от -400 до 400!
	y = rand() % 1900 + (-950);	//Предел поля от -950 до 950!
	FVector NewPosition;
	//Если появление Еды(Food) выподает на эти координаты, то Spawn не происходит!
	false;
	{
		NewPosition.X = x =  100;
		NewPosition.Y = y = -720;
	}
	false;
	{
		NewPosition.X = x = 330;
		NewPosition.Y = y = -200;
	}
	false;
	{
		NewPosition.X = x = 320;
		NewPosition.Y = y = -480;
	}
	false;
	{
		NewPosition.X = x = -170;
		NewPosition.Y = y = 100;
	}
	false;
	{
		NewPosition.X = x = 150;
		NewPosition.Y = y = 480;
	}
	false;
	{
		NewPosition.X = x = -280;
		NewPosition.Y = y = 740;
	}
	NewPosition.X = x = rand() % 800 + (-400);
	NewPosition.Y = y = rand() % 1900 + (-950);
	FTransform NewTransform(NewPosition);
	FoodActor = GetWorld()->SpawnActor<AFood>(FoodActorClass, FTransform(NewPosition));
	MovementsSpeed = -1;
}
