// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerPawn::APlayerPawn()
	:
	TouchMoveSensivity(1.f),
	MoveLimit(FVector2D(500.f, 600.f))
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	SetRootComponent(PawnCollision);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(RootComponent);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
}

void APlayerPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);	
}

void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);
	TouchDeltaMove *=  TouchMoveSensivity;
	FVector NewLocation = GetActorLocation();

	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X*-1.f, -MoveLimit.X, MoveLimit.X);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}
