#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Cyberspace {
	struct WindowProps {
		int Width;
		int Height;
		std::string Title;
		bool VSync;
		bool CursorEnabled;
		WindowProps(std::string _title = "Cyberspace",
			unsigned int _width = 1280,
			unsigned int _height = 720,
			bool _vsync = true,
			bool _cursorEnabled = true) :
			Width(_width), Height(_height), Title(_title),
			VSync(_vsync), CursorEnabled(_cursorEnabled)
		{}
	};

	struct GUIProps {

		GUIProps()
		{}
	};

	struct GraphicsProps {
		float FOV;
		WindowProps windowProps;
		GUIProps guiProps;
		GraphicsProps(
			float _fov = 60.0f,
			WindowProps _windowProps = WindowProps(), GUIProps _guiProps = GUIProps())
			: FOV(_fov)
			, windowProps(_windowProps), guiProps(_guiProps) {}
	};

	struct AMProps {
		std::string VehicleModelPath, EnvironmentModelPath, CharacterModelPath;
		std::string ModelVertexShaderPath, ModelFragmentShaderPath;
		std::string SkyboxVertexShaderPath, SkyboxFragmentShaderPath;
		AMProps(
			std::string _VehicleModelPath = "../resources/3D/Vehicle/SpaceCar.fbx",
			std::string _EnvironmentModelPath = "../resources/3D/Environment/CanyonEnvironment.fbx",
			std::string _CharacterModelPath = "",
			std::string _ModelVertexShaderPath = "../resources/Shaders/TextureVertexShader.glsl",
			std::string _ModelFragmentShaderPath = "../resources/Shaders/TextureFragmentShader.glsl",
			std::string _SkyboxVertexShaderPath = "../resources/Shaders/SkyboxVertexShader.glsl",
			std::string _SkyboxFragmentShaderPath = "../resources/Shaders/SkyboxFragmentShader.glsl") :
			VehicleModelPath(_VehicleModelPath), EnvironmentModelPath(_EnvironmentModelPath), CharacterModelPath(_CharacterModelPath),
			ModelVertexShaderPath(_ModelVertexShaderPath), ModelFragmentShaderPath(_ModelFragmentShaderPath),
			SkyboxVertexShaderPath(_SkyboxVertexShaderPath), SkyboxFragmentShaderPath(_SkyboxFragmentShaderPath)
		{}
	};

	struct AudioProps {
		const char* TitleScreenBGMFilePath;
		float MasterVolume;
		float MusicVolume;
		float SoundVolume;
		AudioProps(
			const char* _titleScreenBGMFilePath = "../resources/Audio/TitleScreenTrack.wav",
			float _masterVolume = 100.0f,
			float _musicVolume = 100.0f,
			float _soundVolume = 100.0f) :
			TitleScreenBGMFilePath(_titleScreenBGMFilePath),
			MasterVolume(_masterVolume), MusicVolume(_musicVolume), SoundVolume(_soundVolume)
		{}
	};

	struct GMProps {
		std::string PlayerTag;
		std::string VehicleTag;
		std::string EnvironmentTag;
		std::string StartMapTag;
		glm::vec3 PlayerSpawnPosition;
		float PlayerSpeed;
		GMProps(
			std::string _playerTag = "Vehicle",
			std::string _vehicleTag = "VehicleModel",
			std::string _environmentTag = "Canyon",
			std::string _startMapTag = "TitleScreen",
			glm::vec3 _playerSpawnPosition = glm::vec3(0.0f, 0.0f, -10.0f),
			float _playerSpeed = 5.0f) :
			PlayerTag(_playerTag),
			VehicleTag(_vehicleTag),
			EnvironmentTag(_environmentTag),
			StartMapTag(_startMapTag),
			PlayerSpawnPosition(_playerSpawnPosition),
			PlayerSpeed(_playerSpeed)
		{}
	};

	struct NetworkProps {
		NetworkProps() {};
	};

	struct PhysicsProps {
		PhysicsProps() {}
	};

	struct EngineProps {
		GraphicsProps m_GraphicsProps;
		PhysicsProps m_PhysicsProps;
		AudioProps m_AudioProps;
		NetworkProps m_NetProps;
		AMProps m_AMProps;
		GMProps m_GMProps;

		EngineProps(
			GraphicsProps _gProps = GraphicsProps(),
			PhysicsProps _pProps = PhysicsProps(),
			AudioProps _aProps = AudioProps(),
			NetworkProps _netProps = NetworkProps(),
			AMProps _amProps = AMProps(),
			GMProps _gmProps = GMProps()) :
			m_GraphicsProps(_gProps),
			m_PhysicsProps(_pProps),
			m_AudioProps(_aProps),
			m_NetProps(_netProps),
			m_AMProps(_amProps),
			m_GMProps(_gmProps) {}
	};
}

