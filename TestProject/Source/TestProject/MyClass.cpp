// Fill out your copyright notice in the Description page of Project Settings.


#include "MyClass.h"

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}



void MyClass::SoundPlay3D(FTransform transform)
{

	//사운드가 단발성인 경우 매번 인스턴스가 생성됬다가 사운드가 종료되면 인스턴스가 없어진다.
	//사운드가 연속적이면 Relesase하지 않는이상 사운드가 계속 출력 되면서 인스턴스가 남아있음
	//인스턴스가 남아있어야 사운드의 값을 변경 가능하므로 단발성일 경우 사운드가 출력되기전 값을 적용시킨후 출력
	//사운드가 연속적일경우 사운드 출력도중 사운드를 변경 가능 
	
	//사운드 인스턴스를 만듬 
	Instance = UFMODBlueprintStatics::PlayEventAtLocation(World, Event, transform, false);
	//사운드의 파라미터가 해당하는 파라미터가 있을시 파라미터 변경
	UFMODBlueprintStatics::EventInstanceSetParameter(Instance, Parameter, ParameterValue);
	//사운드 볼륨 조절
	UFMODBlueprintStatics::EventInstanceSetVolume(Instance, Volume);
	//사운드 플레이
	UFMODBlueprintStatics::EventInstancePlay(Instance);
}


void MyClass::SoundPlay2D()
{
	Instance = UFMODBlueprintStatics::PlayEvent2D(World, Event, true);

	
}

void MyClass::SoundStop()
{
	//사운드 종료
	Instance.Instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);//FadeOut종료
	Instance.Instance->release();
}



void MyClass::SetTransform(FTransform transform)
{
	//사운드가 나타나는 위치 조절
	UFMODBlueprintStatics::EventInstanceSetTransform(Instance, transform);
}

void MyClass::SetVolume(float Vol)
{
	//사운드의 볼륨 조절

	//사운드가 단발성이면 값을 저장했다가 다음 사운드 출력때 사용
	Volume = Vol;
	//사운드가 연속적이면 볼륨을바로 조절
	if (Instance.Instance->isValid()) {
		UFMODBlueprintStatics::EventInstanceSetVolume(Instance, Volume);
	}
}

void MyClass::SetParameter(FString parameter,float Value)
{
	
	//사운드의 파라미터값 설정
	//사운드가 단발성이면 값을 저장했다가 다음 사운드 출력때 사용
	this->Parameter = FName(parameter);
	this->ParameterValue = Value;
	if (Instance.Instance->isValid()) {
		
		UFMODBlueprintStatics::EventInstanceSetParameter(Instance, Parameter, ParameterValue);
	}


}
