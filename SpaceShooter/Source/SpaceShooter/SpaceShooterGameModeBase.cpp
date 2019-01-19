// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterGameModeBase.h"

ASpaceShooterGameModeBase::ASpaceShooterGameModeBase()
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));

}
