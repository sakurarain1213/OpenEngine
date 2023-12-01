#pragma once

namespace OpenEngine::Setting {
	struct WindowDeviceSetting {
		/*
		* OpenGL Major Version
		*/
		uint16_t contextVersionMajor = 3;
		/*
		* OpenGL Minor Version
		*/
		uint16_t contextVersionMinor = 2;
		/*
		* Defines the amount of samples to use (Requiered for multi-sampling)
		*/
		uint16_t samples = 4;
	};
}