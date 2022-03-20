// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnaleElementBase.h"
#include "Interactable.h"
#include "Food.h"
#include "random"
#include "Wall.h"

using namespace std;
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
	CreateFoodActor(0);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(); 
	float TickInterval = -1;
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
			//��������� �������� ���� ����� �������� ��� 
			SetActorTickInterval(MovementsSpeed+=-0.005); UE_LOG(LogTemp, Warning, TEXT("SnakeSpeedBoost: %f"), MovementsSpeed);
		}
	}
}

//��������� ��������� ������ ��� � �������� ����!
void ASnakeBase::CreateFoodActor(float value)
{
	const int Height = (-400, 400);
	const int Width = (-950, 950);
	int x, y;
	FVector NewPosition;
	NewPosition.X = x = rand() % 250 + (-125); //������ ���� �� -400 �� 400!
	NewPosition.Y = y = rand() % 250 + (-125); //������ ���� �� -950 �� 950!
	NewPosition.Z = 0.f;
	FTransform NewTransform(NewPosition);
	NewSpawn(0, 1);
	FoodActor = GetWorld()->SpawnActor<AFood>(FoodActorClass, FTransform(NewPosition));
	
}

//���� ��� ������������� � ������������, �� ���(���) ������������ � �������� � ����� ����� 
void ASnakeBase::NewSpawn(ASnaleElementBase* NewSnakeElem, float value)
{
	if (SnakeElements.Num())
	{
		FVector NewPPosition;
		NewPPosition.X = SnakeElements.Num();
		NewPPosition.Y = SnakeElements.Num();
		if (value > 0 && FoodActor)
		{
			float x, y;
			FVector NewPosition;
			NewPosition.X = rand() % 250 + (-125);
			NewPosition.Y = rand() % 250 + (-125);
			x,y = (NewPosition.X + NewPPosition.X) - (NewPosition.Y + NewPPosition.Y);
			if (x,y >= 80 + (-80))
			{
				FTransform NewTransform(NewPosition); UE_LOG(LogTemp, Warning, TEXT("Distance x: %f"), x);
				                                      UE_LOG(LogTemp, Warning, TEXT("Distance y: %f"), y)
												      UE_LOG(LogTemp, Warning, TEXT("NewSpawn"));
			}
		}
		else if (value < 0 && FoodActor)
		{
			FVector NewPosition;
			FTransform NewTransform(NewPosition);
			UE_LOG(LogTemp, Warning, TEXT("Spawn"));
		}
	}
}	