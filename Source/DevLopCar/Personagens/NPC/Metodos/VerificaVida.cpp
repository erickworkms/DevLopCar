//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopCar/Personagens/Enums/Lista_Enums.h"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::VerificaVida()
{
	if (Vida <= 0)
	{
		IA_Comportamento = Morto_NPC;
		Acao = Morto;
	}
}
