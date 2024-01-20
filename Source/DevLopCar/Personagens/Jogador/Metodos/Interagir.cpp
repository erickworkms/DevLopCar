//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::Interagir_Pressionado()
{
	if (IsValid(Veiculo) && Acao != Dirigir && PermiteEntrarCarro == true)
	{
		Acao = Dirigir;
	}
	else if (IsValid(Veiculo) && Acao == Dirigir && PermiteSairCarro == true)
	{
		Acao = Nada;
	}
}

void AJogador_Base::Interagir_Solto()
{
}