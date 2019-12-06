#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cyberspace/Entity.h"

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
		std::vector<ResDisplayFormat> m_AvDisFormats;
		GraphicsProps(
			std::string _title = "Cyberspace",
			ResDisplayFormat _disFormat = { "1600x900", 1600, 900 },
			bool _fullscreen = false,
			bool _brdrlessFull = false,
			float _fov = 60.0f, 
			bool _enCursor = true,
			bool _msaa = true, 
			bool _vsync = true,
			std::vector<ResDisplayFormat> _displayFormats = std::vector<ResDisplayFormat>{
				{ "800x600", 800, 600 },
				{ "1280x720", 1280, 720 },
				{"1600x900", 1600, 900 }
			})
			:
			m_WinTitle(_title),
			m_DisFormat(_disFormat),
			m_Fullscreen(_fullscreen), 
			m_BrdrlessFull(_brdrlessFull),
			m_FOV(_fov), m_EnCursor(_enCursor),
			m_MSAA(_msaa), m_VSync(_vsync),
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
			std::string _VehicleModelPath = "../resources/3D/Vehicle/vehicle_model.fbx",
			std::string _EnvironmentModelPath = "../resources/3D/Environment/environment_model.fbx",
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
		bool MutedBGM = false;
		bool MutedSFX = false;
		AudioProps(
			const char* _titleScreenBGMFilePath = "../resources/Audio/TitleScreenTrack.wav",
			float _masterVolume = 1.0f,
			float _musicVolume = 1.0f,
			float _soundVolume = 1.0f) :
			TitleScreenBGMFilePath(_titleScreenBGMFilePath),
			MasterVolume(_masterVolume), MusicVolume(_musicVolume), SoundVolume(_soundVolume)
		{}
	};

	struct GMProps {
		int m_PlayerID;
		int m_MapID;
		glm::vec3 m_SpawnPosition;
		std::string m_PlayerModelTag;
		std::string m_EnvironmentModelTag;
		std::unordered_map<int, Entity*> m_Entities;
		bool Paused = false;
		GMProps(int _playerID = 0, int _mapID = 0,
			glm::vec3 _spawnPosition = glm::vec3(0.0f, -5.f, -30.0f),
			std::string _playerModelTag = "Vehicle",
			std::string _envModelTag = "Environment")
			: 
			m_PlayerID(_playerID),
			m_MapID(_mapID),
			m_SpawnPosition(_spawnPosition),
			m_PlayerModelTag(_playerModelTag),
			m_EnvironmentModelTag(_envModelTag)
		{
		}
	};

	enum class ClientState : int
	{
		Disconnected = 0,
		Connected,		
		Connecting,
		Reconnecting,
		Disconnecting
	};

	struct NetworkProps {
		ClientState m_ClientState;
		std::unordered_map<int, glm::vec3> m_NetEntityPositions;
		NetworkProps(
			ClientState _state = ClientState::Disconnected) :
			m_ClientState(_state)
		{}
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

