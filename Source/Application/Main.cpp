
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize scene

    SDL_Event e;
    bool quit = false;

    auto scene = std::make_unique<neu::Scene>();
    scene->Load("scenes/scene01.json");


    // models
    auto model3d = std::make_shared<neu::Model>();
    model3d->Load("models/cow.obj");

    //textures

	neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("Textures/cow.png");

    struct Vertex {
                neu::vec3 position;
				neu::vec3 color;
				neu::vec2 textcoords;
    };

    //material
    auto material = neu::Resources().Get<neu::Material>("materials/spot.mat");

    // shader program
    auto program = neu::Resources().Get<neu::Program>("Shaders/basic_lit.prong");
    
    material->program->Use();

    // lights
    material->program->SetUniform("u_ambient_light", glm::vec3{ 0.5f });
    neu::Transform light{{ 2,4,3 }};
    glm::vec3 lightColor{ 1 };

   //transforms
	glm::vec3 eye{ 0, 0, 5 };
    neu::Transform camera{ { 0, 0, 5 } };
    neu::Transform transform{ { 0, 0, 0 } };

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            ImGui_ImplSDL3_ProcessEvent(&e);
        }
        // update
        neu::GetEngine().Update();
        float dt = neu::GetEngine().GetTime().GetDeltaTime();
        neu::vec3 color{ 0, 0, 0 };
        // transform.rotation.y += 90 * dt;
        float angle = neu::GetEngine().GetTime().GetTime() * 50;
        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
        scene->Update(dt);
	
        // draw

        // start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // set ImGui
        ImGui::Begin("Editor");
        ImGui::DragFloat3("Position", glm::value_ptr(light.position), 0.1f);
        ImGui::ColorEdit3("Color", glm::value_ptr(lightColor));
        //light.UpdateGUI();
        transform.UpdateGUI();
        material->UpdateGUI();
        ImGui::End();
        

        glm::mat4 model = glm::mat4(1.0f);

        // model matrix
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        material->program->SetUniform("u_model", model);

        //view matrix

        float speed = 10.0f;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) camera.position.x -= speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) camera.position.x += speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) camera.position.y += speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) camera.position.y -= speed * dt;

        glm::mat4 view = glm::lookAt(camera.position, camera.position + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
        material->program->SetUniform("u_view", view);

        material->program->SetUniform("u_light.position", (glm::vec3)(view * glm::vec4(light.position, 1)));
        light.position.x = neu::math::sin(neu::GetEngine().GetTime().GetTime() * 2) * 30;
        material->program->SetUniform("u_light.color", lightColor);


        //projection matrix

	    float aspect = (float)neu::GetEngine().GetRenderer().GetWidth() / (float)neu::GetEngine().GetRenderer().GetHeight();
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, 0.01f, 100.0f);
        material->program->SetUniform("u_projection", projection);


        neu::GetEngine().GetRenderer().Clear();

        material->Bind();
        model3d->Draw(GL_TRIANGLES);

        scene->Draw(neu::GetEngine().GetRenderer());
        // draw ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        neu::GetEngine().GetRenderer().Present();
    }
    neu::GetEngine().Shutdown();

    return 0;
}
