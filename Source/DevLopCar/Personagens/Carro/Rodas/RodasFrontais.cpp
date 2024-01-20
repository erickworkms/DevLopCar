// Fill out your copyright notice in the Description page of Project Settings.


#include "RodasFrontais.h"

#include "CarroRodaConfig.h"
#include "TireConfig.h"
#include "UObject/ConstructorHelpers.h"

URodasFrontais::URodasFrontais()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		RodaContainer(
			TEXT("StaticMesh'/Engine/EngineMeshes/Cylinder.Cylinder'"));
	if (RodaContainer.Succeeded())
	{
		CollisionMesh = RodaContainer.Object;
	}

	Offset = FVector(-65, 0, 0);
	ShapeRadius = 30;
	ShapeWidth = 10;
	Mass = 20;
	DampingRate = 0.25;
	bAffectedByHandbrake = false;
	
	UCarroRodaConfig* RodaConfigInstance = NewObject<UCarroRodaConfig>();

	//Configuração angulo roda
	SteerAngle = 30;
	TireConfig = RodaConfigInstance;
	LatStiffMaxLoad = 5;
	LatStiffValue = 1000;
	LongStiffValue = 1000;


	//Suspensão
	SuspensionForceOffset = 0;
	SuspensionMaxDrop = 20;
	SuspensionMaxRaise = 40;
	SuspensionNaturalFrequency = 10;
	SuspensionDampingRatio = 1.1;
	SweepType = EWheelSweepType::SimpleAndComplex;


	//Quantidade de torque
	MaxBrakeTorque = 100;
	MaxHandBrakeTorque = 300;
}
