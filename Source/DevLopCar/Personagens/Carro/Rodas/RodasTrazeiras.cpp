// Fill out your copyright notice in the Description page of Project Settings.


#include "RodasTrazeiras.h"

#include "CarroRodaConfig.h"
#include "UObject/ConstructorHelpers.h"

URodasTrazeiras::URodasTrazeiras()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		RodaContainer(
			TEXT("StaticMesh'/Engine/EngineMeshes/Cylinder.Cylinder'"));
	if (RodaContainer.Succeeded())
	{
		CollisionMesh = RodaContainer.Object;
	}
	UCarroRodaConfig* RodaConfigInstance = NewObject<UCarroRodaConfig>();
	Offset = FVector(65, 0, 0);
	ShapeRadius = 30;
	ShapeWidth = 10;
	Mass = 20;
	DampingRate = 0.25;
	bAffectedByHandbrake = true;
	

	//Configuração angulo roda
	SteerAngle=0;
	
	TireConfig = RodaConfigInstance;
	LatStiffMaxLoad = 4;
	LatStiffValue = 200;
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
