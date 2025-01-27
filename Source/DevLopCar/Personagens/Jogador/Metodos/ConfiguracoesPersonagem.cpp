//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DevLopCar/Personagens/Carro/Carro_Base.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"


void AJogador_Base::DefinePadroes()
{
	MeshesPlayer.Init("4", 4);
	AnimacaoPlayer.Init("4", 4);

	MeshesPlayer[0] = TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'");
	MeshesPlayer[1] = TEXT("SkeletalMesh'/Game/Personagens/Pleno/Sporty_Granny.Sporty_Granny'");
	MeshesPlayer[2] = TEXT("SkeletalMesh'/Game/Personagens/Senior/Swat.Swat'");
	MeshesPlayer[3] = TEXT("SkeletalMesh'/Game/Personagens/Chefe/The_Boss.The_Boss'");
	
	AnimacaoPlayer[0] = TEXT(
		"AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint_C'");
	AnimacaoPlayer[1] = TEXT("AnimBlueprint'/Game/Personagens/Pleno/Pleno_AnimBlueprint.Pleno_AnimBlueprint_C'");
	AnimacaoPlayer[2] = TEXT("AnimBlueprint'/Game/Personagens/Senior/Senior_AnimBlueprint.Senior_AnimBlueprint_C'");
	AnimacaoPlayer[3] = TEXT("AnimBlueprint'/Game/Personagens/Chefe/Chefe_AnimBlueprint.Chefe_AnimBlueprint_C'");


	Estagiario_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[0]));
	Pleno_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[1]));
	Senior_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[2]));
	Chefe_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[3]));

	GetCharacterMovement()->AirControl = 1;
	GetCharacterMovement()->AirControlBoostMultiplier = 10;
	GetCharacterMovement()->AirControlBoostVelocityThreshold = 100;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AJogador_Base::VerificaMeshPersonagem(float Index)
{
	if (IsValid(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index]))))
	{
		GetMesh()->SetSkeletalMesh(
			Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index])));
	}
}

void AJogador_Base::LocalAttachPersonagemVeiculo()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
	GetCharacterMovement()->MovementMode = MOVE_Flying;
	if (IsValid(Veiculo))
	{
		AttachToComponent(Cast<ACarro_Base>(Veiculo)->LocalPorta, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Root");
	}
}

void AJogador_Base::DetachPersonagemVeiculo()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Block);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GetCharacterMovement()->MovementMode = MOVE_Walking;
	SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw,0));
}

void AJogador_Base::CriaPersonagemConfig()
{
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);

	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -75));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	}

	//AnimBlueprint
	static ConstructorHelpers::FObjectFinder<UClass> AnimacaoEncontrada(
		TEXT("AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint_C'"));
	GetMesh()->SetAnimInstanceClass(AnimacaoEncontrada.Object);
}
