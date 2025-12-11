#include "PostProcessComponent.h"

namespace neu {
	FACTORY_REGISTER(PostProcessComponent)

	void PostProcessComponent::Update(float dt)	{
		time += dt;
	}

	void PostProcessComponent::Apply(Program& program) {
		program.SetUniform("u_parameters", (uint32_t)parameters);
		program.SetUniform("u_colorTint", colorTint);
		program.SetUniform("u_intensity", intensity);

		program.SetUniform("u_time", time);
	}

	void PostProcessComponent::Read(const serial_data_t& value) {
		Object::Read(value);
	}

	void PostProcessComponent::UpdateGUI() {
		ImGui::Text("Post Process");

		auto toggle = [&](Parameters flag, const char* label) {
			bool enabled = (static_cast<uint32_t>(parameters) & static_cast<uint32_t>(flag)) != 0;
			if (ImGui::Checkbox(label, &enabled)) {
				if (enabled)
					parameters = static_cast<Parameters>(static_cast<uint32_t>(parameters) | static_cast<uint32_t>(flag));
				else
					parameters = static_cast<Parameters>(static_cast<uint32_t>(parameters) & ~static_cast<uint32_t>(flag));
			}
			};

		toggle(Parameters::Grayscale, "Grayscale");
		toggle(Parameters::ColorTint, "Color Tint");
		toggle(Parameters::ScanLine, "Scanline");
		toggle(Parameters::Invert, "Invert");
		toggle(Parameters::Grain, "Grain");
		toggle(Parameters::Distort, "Distort");

		ImGui::ColorEdit3("Color Tint", &colorTint[0]);
		ImGui::SliderFloat("Intensity", &intensity, 0.0f, 2.0f);

	}
}
