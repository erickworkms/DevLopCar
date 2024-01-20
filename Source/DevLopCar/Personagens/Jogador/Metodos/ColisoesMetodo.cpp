#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::AdicionaCarro(AActor* Carro)
{
	Veiculo = Carro;
	PermiteEntrarCarro = true;
	PermiteSairCarro = false;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"PASSOU POR AQUI");
}

void AJogador_Base::RemoverCarro()
{
	Veiculo = nullptr;
	PermiteEntrarCarro = false;
	PermiteSairCarro = false;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"SAIU");
}