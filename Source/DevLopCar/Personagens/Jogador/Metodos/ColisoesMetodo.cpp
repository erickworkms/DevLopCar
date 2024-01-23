#include "DevLopCar/Personagens/Carro/Carro_Base.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::AdicionaCarro(AActor* Carro)
{
	Veiculo = Carro;
	ACarro_Base* VerificaCarro = Cast<ACarro_Base>(Carro);
	if (IsValid(VerificaCarro))
	{
		VerificaCarro->Jogador = this;
	}
	PermiteEntrarCarro = true;
	PermiteSairCarro = false;
}

void AJogador_Base::RemoverCarro()
{
	ACarro_Base* VerificaCarro = Cast<ACarro_Base>(Veiculo);
	if (IsValid(VerificaCarro))
	{
		VerificaCarro->Jogador = nullptr;
	}
	Veiculo = nullptr;
	PermiteEntrarCarro = false;
	PermiteSairCarro = false;
}