#pragma once

namespace neu {
	class LightComponent : public Component, GUI
	{
	public:
		CLASS_PROTOTYPE(LightComponent)

		void Update(float dt) override;
		void SetProgram(Program& program, const std::string& name, const glm::mat4& view);

		void Read(const serial_data_t& value) override;

	public:
		glm::vec3 color{ 1, 1, 1 };

		// Inherited via GUI
		void UpdateGUI() override;
	};
}