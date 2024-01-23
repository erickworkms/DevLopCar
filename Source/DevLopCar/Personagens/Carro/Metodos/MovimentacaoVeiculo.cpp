//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "WheeledVehicle.h"
#include "WheeledVehicleMovementComponent.h"
#include "DevLopCar/Personagens/Carro/Carro_Base.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void ACarro_Base::VerificaVelocidadeCarro(float valor)
{
	Velocidade = GetMesh()->GetComponentVelocity().GetAbs().X
		+ GetMesh()->GetComponentVelocity().GetAbs().Y;
	Velocidade = FMath::FInterpTo(GetMesh()->GetComponentVelocity().Size(),
								  Velocidade, valor, 10.f);
	Jogador->ValorAceleracao = Velocidade;
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