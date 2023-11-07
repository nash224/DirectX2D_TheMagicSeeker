#include "PreCompile.h"
#include "TitleUI.h"


#include "NormalProp.h"

TitleUI::TitleUI() 
{
}

TitleUI::~TitleUI() 
{
}


void TitleUI::Start()
{
}

void TitleUI::Update(float _Delta)
{
	UpdateUI();
}

void TitleUI::Release()
{
}

void TitleUI::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void TitleUI::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void TitleUI::Init()
{
	ButtonSetting();
	StateSetting();
}


void TitleUI::ButtonSetting()
{
	std::shared_ptr<NormalProp> ZButton = GetLevel()->CreateActor<NormalProp>();
	ZButton->Transform.SetLocalPosition({100.0f, -480.0f, GlobalUtils::CalculateFixDepth(ETITLERENDERDEPTH::UI)});
	ZButton->Init();
	ZButton->m_Renderer->SetSprite("ButtonSet_Keyboard_Z_PressHold.png");


	std::shared_ptr<NormalProp> ArrowButton = GetLevel()->CreateActor<NormalProp>();
	ArrowButton->Transform.SetLocalPosition({ 270.0f, -480.0f, GlobalUtils::CalculateFixDepth(ETITLERENDERDEPTH::UI) });
	ArrowButton->Init();
	ArrowButton->m_Renderer->SetSprite("ButtonSet_Keyboard_Arrow_Vertical.png");
}

void TitleUI::StateSetting()
{
	//CreateStateParameter PressButtonState;
	//PressButtonState.Start = [=](GameEngineState* _Parent)
	//	{
	//		_Level->CreateActor<>
	//	};
}


/////////////////////////////////////////////////////////////////////////////////////

void TitleUI::UpdateUI()
{

}
