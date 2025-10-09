
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize scene


    SDL_Event e;
    bool quit = false;
    std::vector<neu::vec3> points;
    std::vector<neu::vec3> colors;

    //OPENGL init
    points.push_back(neu::vec3(0.3, 0.25, 0));
    points.push_back(neu::vec3(0.5, 0.1, 0));
    points.push_back(neu::vec3(0, 0, 3));
    colors.push_back(neu::vec3(1, 0, 0));
    colors.push_back(neu::vec3(0, 1, 0));
    colors.push_back(neu::vec3(0, 0, 1));


    GLuint vbo;
	glGenBuffers(1, &vbo);
    
	//vertex buffer position
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW );

    // vertex array
    GLuint vao;
    glGenVertexArrays(1, &vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // vertex shader
    std::string vs_source;
    neu::file::ReadTextFile("Shaders/basic.vert", vs_source);
    const char* vs_cstr = vs_source.c_str();

    GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vs_cstr, NULL);
	glCompileShader(vertexShader);

    // fragment shader

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // update
        neu::GetEngine().Update();

        neu::vec3 color{ 0, 0, 0 };
        neu::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        neu::GetEngine().GetRenderer().Clear();

        neu::vec2 mouse = neu::GetEngine().GetInput().GetMousePosition();
        neu::vec2 position = { mouse.x, mouse.y };
        float angle = neu::GetEngine().GetTime().GetTime() * 50;

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // draw
            
        glPushMatrix();
        
        glTranslatef(position.x, position.y, 0);
        glScalef(neu::math::cos(angle * 0.05), neu::math::sin(angle * 0.05), 1.0);
        glRotatef(angle, 0, 0, 1);

        glBegin(GL_TRIANGLES);
        for (int i = 0; i < points.size(); i++) {
            
            glColor3f(colors[i].r, colors[i].g, colors[i].b);
            glVertex3f(points[i].x, points[i].y, points[i].z);
            
		}
        glEnd();
        glPopMatrix();
        


        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
