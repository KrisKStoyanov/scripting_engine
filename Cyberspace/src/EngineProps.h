#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

//This file is used to set the properties of the game/application
//through multiple different settings for each individual API integrated in the engine

namespace Cyberspace {
	
	//Resolution Display Format (e.g. 1600x900)
	struct ResDisplayFormat {
		std::string DisplayFormat;
		int ResX;
		int ResY;
	};

	//Graphics Properties
	struct GraphicsProps {
		std::string m_WinTitle;
		ResDisplayFormat m_DisFormat;
		bool m_Fullscreen;
		bool m_BrdrlessFull;
		float m_FOV;
		bool m_EnCursor;
		bool m_MSAA;
		bool m_VSync;
		bool m_Defaults;
		std::vector<ResDisplayFormat> m_AvDisFormats;
		GraphicsProps(
			std::string _title = "Cyberspace",
			ResDisplayFormat _disFormat = { "1600x900", 1600, 900 },
			bool _fullscreen = false, bool _brdrlessFull = false,
			float _fov = 60.0f, bool _enCursor = true,
			bool _msaa = true, bool _vsync = true,
			bool _defaults = false,
			std::vector<ResDisplayFormat> _displayFormats = std::vector<ResDisplayFormat>{
				{"1600x900", 1600, 900 },
				{ "1280x720", 1280, 720 },
				{ "800x600", 800, 600 }
			})
			:
			m_WinTitle(_title),
			m_DisFormat(_disFormat),
			m_Fullscreen(_fullscreen), 
			m_BrdrlessFull(_brdrlessFull),
			m_FOV(_fov), m_EnCursor(_enCursor),
			m_MSAA(_msaa), m_VSync(_vsync),
			m_Defaults(_defaults),
			m_AvDisFormats(_displayFormats)
		{
			m_DisFormat.DisplayFormat = std::to_string(m_DisFormat.ResX) + "x" + std::to_string(m_DisFormat.ResY);
		}
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

