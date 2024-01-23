//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "WheeledVehicle.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "WheeledVehicleMovementComponent.h"
#include "DevLopCar/Personagens/Carro/Carro_Base.h"
#include "DevLopCar/Personagens/Carro/Rodas/RodasFrontais.h"
#include "DevLopCar/Personagens/Carro/Rodas/RodasTrazeiras.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS

void ACarro_Base::ConfigFisicaVeiculo()
{
	UWheeledVehicleMovementComponent4W* veiculoConfig = Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	veiculoConfig->WheelSetups.SetNum(4);
	veiculoConfig->bReverseAsBrake = true;
	veiculoConfig->bDeprecatedSpringOffsetMode = true;
	veiculoConfig->Mass = 1500;

	veiculoConfig->ApplyWorldOffset(FVector(0, 0, -20), true);

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
	CurvasTorque->AddKey(50.823479, 840.000000);
	CurvasTorque->AddKey(1890.000000, 1500.000000);
	CurvasTorque->AddKey(5746.000000, 840.000000);
	CurvasTorque->AddKey(50.823479, 840.000000);

	veiculoConfig->MaxEngineRPM = 5000;
	veiculoConfig->EngineSetup.TorqueCurve = ControleCurvaTorque;
	veiculoConfig->EngineSetup.MaxRPM = 5000;
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
	CurvasSteering->AddKey(70, 0.7);
	CurvasSteering->AddKey(110, 0.5);
	CurvasSteering->AddKey(150, 0.25);
	veiculoConfig->SteeringCurve = ControleCurvaSteering;

	veiculoConfig->AckermannAccuracy = 0.9f;
	veiculoConfig->TransmissionSetup.ClutchStrength = 10;
}

void ACarro_Base::MudancaConfigFisicaVeiculo()
{
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaEsquerdaJoint", 1, false, true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaDireitaJoint", 1, false, true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaTrazBase", 1, false, true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("TampaCarro", 1, false, true);
}