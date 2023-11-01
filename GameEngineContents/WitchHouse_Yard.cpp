#include "PreCompile.h"
#include "WitchHouse_Yard.h"


#include "BackDrop_WitchHouse_Yard.h"
#include "CameraControler.h"
#include "Ellie.h"

#include "SkyLerp.h"


WitchHouse_Yard::WitchHouse_Yard() 
{
}

WitchHouse_Yard::~WitchHouse_Yard() 
{
}


void WitchHouse_Yard::Start()
{
	PlayLevel::Start();

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Fix);
	}

	m_SkyLerp = CreateActor<SkyLerp>(EUPDATEORDER::Sky);
	m_SkyLerp->Init();
}

void WitchHouse_Yard::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadActor();


	SetEllieLevelChangeLocation(_NextLevel);

	CameraSetting();
}

void WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);

	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#pragma region LoadRes
void WitchHouse_Yard::LoadTexture()
{
	std::vector<GameEngineDirectory> Dirs = GlobalUtils::GetAllDirInPath("Resources\\PlayContents\\WitchHouse_Yard");
	for (GameEngineDirectory& Dir : Dirs)
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
}


void WitchHouse_Yard::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_WitchHouse_Yard>(EUPDATEORDER::Objects);
	}

	m_BackDrop->Init();
}


// 레벨전환시 앨리의 시작위치를 지정해줍니다.
void WitchHouse_Yard::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	float4 SpawnPosition = float4::ZERO;

	float4 HWinScale = GlobalValue::GetWindowScale().Half();

	if (_NextLevel->GetName() == "Field_Center")
	{
		SpawnPosition = { HWinScale.X , -450.0f };
	}
	else
	{
		SpawnPosition = { HWinScale.X , -450.0f };
	}

	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("앨리를 생성하지 않았습니다.");
		return;
	}
	m_Ellie->Transform.SetLocalPosition(SpawnPosition);
}

void WitchHouse_Yard::CameraSetting()
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (GlobalValue::g_CameraControler != m_LevelCameraControler)
		{
			MsgBoxAssert("현재 카메라 매니저가 아닙니다.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();
		HWinScale.Y *= -1.0f;

		GlobalValue::g_CameraControler->SetLocalPostion(HWinScale);
	}
}

#pragma endregion 

#pragma region ReleaseRes

void WitchHouse_Yard::ReleaseTexture()
{
	std::vector<GameEngineDirectory> Dirs = GlobalUtils::GetAllDirInPath("Resources\\PlayContents\\WitchHouse_Yard");
	for (GameEngineDirectory& Dir : Dirs)
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineTexture::Release(File.GetFileName());
		}
	}
}

#pragma endregion