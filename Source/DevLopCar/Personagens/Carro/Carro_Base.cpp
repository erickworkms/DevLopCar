// Fill out your copyright notice in the Description page of Project Settings.


#include "Carro_Base.h"

#include "WheeledVehicle.h"

#include "WheeledVehicleMovementComponent4W.h"
#include "WheeledVehicleMovementComponent.h"
#include "NavAreas/NavArea_Null.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Rodas/RodasFrontais.h"
#include "Rodas/RodasTrazeiras.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS

ACarro_Base::ACarro_Base()
{
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);
	PadroesVeiculo();
}

void ACarro_Base::PadroesVeiculo()
{
	AbrirPorta = false;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(
			TEXT("SkeletalMesh'/Game/Personagens/Carro/Brasilia.Brasilia'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	}
	//Blueprints de animação
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		SedanContainer(TEXT(
			"AnimBlueprint'/Game/Personagens/Carro/Brasilia_AnimBlueprint.Brasilia_AnimBlueprint'"));
	if (SedanContainer.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(SedanContainer.Object->GeneratedClass);
	}
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECC_Vehicle);
	GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ReferenciaContainer(
			TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (ReferenciaContainer.Succeeded())
	{
		LocalPorta = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Referencia"));
		LocalPorta->SetStaticMesh(ReferenciaContainer.Object);
		LocalPorta->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LocalPorta->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Root");
		LocalPorta->SetRelativeLocation(FVector(-28,-125,100), false, nullptr,
										ETeleportType::None);
		LocalPorta->SetRelativeRotation(FRotator(0.000000, 90, 0), false, nullptr, ETeleportType::None);
		LocalPorta->SetHiddenInGame(true);
	}
	GetMesh()->bNavigationRelevant = true;
	GetMesh()->SetCanEverAffectNavigation(true);
	LimpaNavMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("LimpaNavMesh"));
	LimpaNavMesh->SetCanEverAffectNavigation(true);
	LimpaNavMesh->SetWorldScale3D(FVector(7.048013,2.168754,4.817287));
	LimpaNavMesh->SetRelativeLocation(FVector(-15.000000,3.000000,142.000000));
	LimpaNavMesh->AreaClass = UNavArea_Null::StaticClass();
	LimpaNavMesh->bDynamicObstacle = true;
	LimpaNavMesh->bFillCollisionUnderneathForNavmesh = true;
	LimpaNavMesh->SetupAttachment(GetMesh());
	ConfigFisicaVeiculo();
	
	DetectaPersonagem = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectaColisao"));
	DetectaPersonagem->SetCanEverAffectNavigation(true);
	DetectaPersonagem->SetWorldScale3D(FVector(1.25,2.75,1.5));
	DetectaPersonagem->SetRelativeLocation(FVector(5,-47.000000,80));
	DetectaPersonagem->SetRelativeRotation(FRotator(0,0,0));
	DetectaPersonagem->SetupAttachment(GetMesh());
	DetectaPersonagem->bHiddenInGame = false;
	DetectaPersonagem->OnComponentBeginOverlap.AddDynamic(this, &ACarro_Base::InicioColisaoEntrada);
	DetectaPersonagem->OnComponentEndOverlap.AddDynamic(this, &ACarro_Base::FimColisaoEntrada);

	DetectaDanoFrente = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectaDanoFrente"));
	DetectaDanoFrente->SetCanEverAffectNavigation(false);
	DetectaDanoFrente->SetWorldScale3D(FVector(1.75,2.55,1.5));
	DetectaDanoFrente->SetRelativeLocation(FVector(190,10,80));
	DetectaDanoFrente->SetRelativeRotation(FRotator(0,0,0));
	DetectaDanoFrente->SetupAttachment(GetMesh());
	DetectaDanoFrente->bHiddenInGame = false;
	DetectaDanoFrente->OnComponentBeginOverlap.AddDynamic(this, &ACarro_Base::InicioDanoColisao);

	DetectaDanoAtras = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectaDanoAtras"));
	DetectaDanoAtras->SetCanEverAffectNavigation(false);
	DetectaDanoFrente->SetWorldScale3D(FVector(1.75,2.55,1.5));
	DetectaDanoAtras->SetRelativeLocation(FVector(-180,10,80));
	DetectaDanoAtras->SetRelativeRotation(FRotator(0,0,0));
	DetectaDanoAtras->SetupAttachment(GetMesh());
	DetectaDanoAtras->bHiddenInGame = false;
	DetectaDanoAtras->OnComponentBeginOverlap.AddDynamic(this, &ACarro_Base::InicioDanoColisao);
}

void ACarro_Base::ConfigFisicaVeiculo()
{
	UWheeledVehicleMovementComponent4W* veiculoConfig = Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	veiculoConfig->WheelSetups.SetNum(4);
	veiculoConfig->bReverseAsBrake = true;
	veiculoConfig->bDeprecatedSpringOffsetMode = true;
	veiculoConfig->Mass = 10000;

	veiculoConfig->ApplyWorldOffset(FVector(0,0,-20),true);
	
	veiculoConfig->DragCoefficient = 0;
	veiculoConfig->ChassisWidth = 180;
	veiculoConfig->ChassisHeight = 140;
	
	veiculoConfig->MinNormalizedTireLoad = 0;
	veiculoConfig->MinNormalizedTireLoadFiltered = 0.23;
	veiculoConfig->MaxNormalizedTireLoad = 3;
	veiculoConfig->MaxNormalizedTireLoadFiltered = 6;
	veiculoConfig->ThresholdLongitudinalSpeed = 5;
	veiculoConfig->LowForwardSpeedSubStepCount = 3;
	veiculoConfig->HighForwardSpeedSubStepCount = 1;

	FRuntimeFloatCurve ControleCurvaTorque;
	FRichCurve* CurvasTorque = ControleCurvaTorque.GetRichCurve();
	CurvasTorque->AddKey(50.823479,840.000000);
	CurvasTorque->AddKey(1890.000000,1500.000000);
	CurvasTorque->AddKey(5746.000000,840.000000);
	CurvasTorque->AddKey(50.823479,840.000000);
	
	veiculoConfig->MaxEngineRPM = 10000;
	veiculoConfig->EngineSetup.TorqueCurve = ControleCurvaTorque;
	veiculoConfig->EngineSetup.MaxRPM = 10000;
	veiculoConfig->EngineSetup.MOI = 1;
	veiculoConfig->EngineSetup.DampingRateFullThrottle = 0.15;
	veiculoConfig->EngineSetup.DampingRateZeroThrottleClutchDisengaged = 2;
	veiculoConfig->EngineSetup.DampingRateZeroThrottleClutchEngaged = 0.35;
	

	veiculoConfig->WheelSetups[0].WheelClass = URodasFrontais::StaticClass();
	veiculoConfig->WheelSetups[0].BoneName = "RodaFrenteEsquerda";
	veiculoConfig->WheelSetups[0].AdditionalOffset = FVector(60, 0, 0);
	veiculoConfig->WheelSetups[0].bDisableSteering = false;

	veiculoConfig->WheelSetups[1].WheelClass = URodasFrontais::StaticClass();
	veiculoConfig->WheelSetups[1].BoneName = "RodaFrenteDireita";
	veiculoConfig->WheelSetups[1].AdditionalOffset = FVector(60, 0, 0);
	veiculoConfig->WheelSetups[1].bDisableSteering = false;

	veiculoConfig->WheelSetups[2].WheelClass = URodasTrazeiras::StaticClass();
	veiculoConfig->WheelSetups[2].BoneName = "RodatrazEsquerda";
	veiculoConfig->WheelSetups[2].AdditionalOffset = FVector(-70, 0, 0);
	veiculoConfig->WheelSetups[2].bDisableSteering = true;

	veiculoConfig->WheelSetups[3].WheelClass = URodasTrazeiras::StaticClass();
	veiculoConfig->WheelSetups[3].BoneName = "RodaTrazDireita";
	veiculoConfig->WheelSetups[3].AdditionalOffset = FVector(-70, 0, 0);
	veiculoConfig->WheelSetups[3].bDisableSteering = true;
	
	veiculoConfig->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_RearDrive;
	veiculoConfig->DifferentialSetup.FrontRearSplit = 0.75;
	veiculoConfig->DifferentialSetup.FrontLeftRightSplit = 0.5;
	veiculoConfig->DifferentialSetup.RearLeftRightSplit = 0.5;
	veiculoConfig->DifferentialSetup.CentreBias = 1.3;
	veiculoConfig->DifferentialSetup.FrontBias = 1.3;
	veiculoConfig->DifferentialSetup.RearBias = 1.3;

	veiculoConfig->TransmissionSetup.bUseGearAutoBox = true;
	veiculoConfig->TransmissionSetup.GearSwitchTime = 0.25;
	veiculoConfig->TransmissionSetup.GearAutoBoxLatency = 2;
	veiculoConfig->TransmissionSetup.FinalRatio = 4;
	veiculoConfig->TransmissionSetup.ReverseGearRatio = -3.0f;

	FVehicleInputRate ThrottleInputRate;
	ThrottleInputRate.RiseRate = 6.0f;
	ThrottleInputRate.FallRate = 10.0f;
	
	veiculoConfig->SetThrottleInput(2);
	veiculoConfig->SetBrakeInput(2);
	veiculoConfig->SetSteeringInput(2);
	
	FVehicleInputRate BrakeInputRate;
	BrakeInputRate.RiseRate = 6.0f;
	BrakeInputRate.FallRate = 10.0f;

	FVehicleInputRate HandBrakeInputRate;
	HandBrakeInputRate.RiseRate = 12.0f;
	HandBrakeInputRate.FallRate = 12.0f;

	FVehicleInputRate SteeringInputRate;
	SteeringInputRate.RiseRate = 2.0f;
	SteeringInputRate.FallRate = 5.0f;  

	// TArray<FVehicleGearData> MarchaConfig;
	// MarchaConfig.SetNum(6);

	// MarchaConfig[0].Ratio = 6.0f;
	// MarchaConfig[0].DownRatio = 0.5f;
	// MarchaConfig[0].UpRatio = 0.8f;
	//
	// veiculoConfig->TransmissionSetup.ForwardGears.Add(MarchaConfig[0]);
	//
	// MarchaConfig[1].Ratio = 2.0f;
	// MarchaConfig[1].DownRatio = 0.5f;
	// MarchaConfig[1].UpRatio = 0.8f;
	//
	// veiculoConfig->TransmissionSetup.ForwardGears.Add(MarchaConfig[1]);
	//
	// MarchaConfig[2].Ratio = 1.5f;
	// MarchaConfig[2].DownRatio = 0.5f;
	// MarchaConfig[2].UpRatio = 0.8f;
	//
	// veiculoConfig->TransmissionSetup.ForwardGears.Add(MarchaConfig[2]);
	//
	// MarchaConfig[3].Ratio = 1.2f;
	// MarchaConfig[3].DownRatio = 0.5f;
	// MarchaConfig[3].UpRatio = 0.8f;
	//
	// veiculoConfig->TransmissionSetup.ForwardGears.Add(MarchaConfig[3]);
	//
	// MarchaConfig[4].Ratio = 1.1f;
	// MarchaConfig[4].DownRatio = 0.5f;
	// MarchaConfig[4].UpRatio = 0.8f;
	//
	// veiculoConfig->TransmissionSetup.ForwardGears.Add(MarchaConfig[4]);
	//
	// MarchaConfig[5].Ratio = 1.0f;
	// MarchaConfig[5].DownRatio = 0.5f;
	// MarchaConfig[5].UpRatio = 0.8f;
	//
	// veiculoConfig->TransmissionSetup.ForwardGears.Add(MarchaConfig[5]);

	FRuntimeFloatCurve ControleCurvaSteering;
	FRichCurve* CurvasSteering = ControleCurvaSteering.GetRichCurve();
	CurvasSteering->AddKey(70,0.7);
	CurvasSteering->AddKey(110,0.5);
	CurvasSteering->AddKey(150,0.25);
	veiculoConfig->SteeringCurve = ControleCurvaSteering;

	veiculoConfig->AckermannAccuracy = 0.9f;
	veiculoConfig->TransmissionSetup.ClutchStrength = 10;
}

void ACarro_Base::MudancaConfigFisicaVeiculo()
{
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaEsquerdaJoint",1,false,true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaDireitaJoint",1,false,true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaTrazBase",1,false,true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("TampaCarro",1,false,true);
}

void ACarro_Base::MovimentaVeiculoFrente()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	GetVehicleMovementComponent()->SetThrottleInput(0.5);
}

void ACarro_Base::PararVeiculo()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
	GetVehicleMovementComponent()->SetThrottleInput(0);
}

void ACarro_Base::MovimentaVeiculoRe()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	GetVehicleMovementComponent()->SetThrottleInput(-0.5);
}

void ACarro_Base::MovimentaVeiculoDirecao(float Direcao)
{
	GetVehicleMovementComponent()->SetSteeringInput(Direcao);
}

void ACarro_Base::BeginPlay()
{
	Super::BeginPlay();
}

bool ACarro_Base::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation,
	int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible,
	int32* UserData) const
{
	OutSeenLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+70);
	IgnoreActor = false;
	return true;
}
