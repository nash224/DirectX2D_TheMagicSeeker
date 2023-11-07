#include "PreCompile.h"
#include "UI_MainMenu_Button.h"

#include "Tunnel.h"


UI_MainMenu_Button::UI_MainMenu_Button()
{
	GameEngineInput::AddInputObject(this);
}

UI_MainMenu_Button::~UI_MainMenu_Button()
{
}

void UI_MainMenu_Button::Update(float _Delta)
{
	UIState.Update(_Delta);
}

void UI_MainMenu_Button::Release()
{
	TitleButton_Press.Button_Font = nullptr;
}

void UI_MainMenu_Button::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_MainMenu_Button::Init()
{
	RendererSetting();
	StateSetting();

	UIState.ChangeState(MainMenuState::AnyPress);
}

void UI_MainMenu_Button::RendererSetting()
{
	static constexpr const int RenderOrder = 0;

	float4 FontPosition = float4(300.0f, -50.0f);


	TitleButton_Press.Button_Font = CreateComponent<GameEngineUIRenderer>(RenderOrder);
	TitleButton_Press.Button_Font->Transform.SetLocalPosition(FontPosition);
	TitleButton_Press.Button_Font->SetText(GlobalValue::Font_Sandoll, "Z 키를 누르세요", 16.0f, float4::WHITE, FW1_TEXT_FLAG::FW1_CENTER);
	TitleButton_Press.Button_Font->Off();
}

void UI_MainMenu_Button::StateSetting()
{
	CreateStateParameter AnyPressState;
	AnyPressState.Start = std::bind(&UI_MainMenu_Button::StartAnyPress, this, std::placeholders::_1);
	AnyPressState.Stay = std::bind(&UI_MainMenu_Button::UpdateAnyPress, this, std::placeholders::_1, std::placeholders::_2);
	AnyPressState.End = std::bind(&UI_MainMenu_Button::EndAnyPress, this, std::placeholders::_1);
	UIState.CreateState(MainMenuState::AnyPress, AnyPressState);

	CreateStateParameter NoneState;
	NoneState.Start = std::bind(&UI_MainMenu_Button::StartNone, this, std::placeholders::_1);
	UIState.CreateState(MainMenuState::None, NoneState);
}



void UI_MainMenu_Button::StartAnyPress(GameEngineState* _Parent)
{
	TitleButton_Press.Button_Font->On();
}

void UI_MainMenu_Button::StartNone(GameEngineState* _Parent)
{

}



void UI_MainMenu_Button::UpdateAnyPress(float _Delta, GameEngineState* _Parent)
{
	if (true == GameEngineInput::IsDown('Z', this))
	{
		std::shared_ptr<Tunnel> TunnelPtr = GetLevel()->CreateActor<Tunnel>(EUPDATEORDER::Fade);
		TunnelPtr->Init("WitchHouse_Yard");

		UIState.ChangeState(MainMenuState::None);
	}
}



void UI_MainMenu_Button::EndAnyPress(GameEngineState* _Parent)
{
	TitleButton_Press.Button_Font->Off();
}