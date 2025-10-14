
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
    std::vector<neu::vec2> texcoords;

    //OPENGL init
    points.push_back(neu::vec3(0.3f, 0.25f, 0.f));
    points.push_back(neu::vec3(0.5f, 0.1f, 0.f));
    points.push_back(neu::vec3(0.f, 0.f, 3.f));
    colors.push_back(neu::vec3(1.f, 0.f, 0.f));
    colors.push_back(neu::vec3(0.f, 1.f, 0.f));
    colors.push_back(neu::vec3(0.f, 0.f, 1.f));
	texcoords.push_back(neu::vec2(0.5f, 0.5f));
	texcoords.push_back(neu::vec2(0.5f, 1.0f));
	texcoords.push_back(neu::vec2(1.0f, 1.0f));

    //texture

	neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("Textures/beast.png");

    struct Vertex {
                neu::vec3 position;
				neu::vec3 color;
				neu::vec2 textcoords;
    };

    std::vector<Vertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{ -0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    };

    std::vector<GLuint> indices{
        0, 1, 2,
        0, 2, 3
    };
	// vertex buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // index buffer
    GLuint ibo;
	glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices.size(), indices.data(), GL_STATIC_DRAW);

	// vertex array
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, textcoords));


    /*
    GLuint vbo[3];
	glGenBuffers(3, vbo);

	//vertex buffer position
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW );

	//vertex buffer color
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);

    // vertex buffer texcoord
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec2) * texcoords.size(), texcoords.data(), GL_STATIC_DRAW);

    // vertex array
    GLuint vao;
    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    // vertex position
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// vertex color
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    // textcoords
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    */

    // vertex shader
    std::string vs_source;
    neu::file::ReadTextFile("Shaders/basic.vert", vs_source);
    const char* vs_cstr = vs_source.c_str();

    GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vs_cstr, NULL);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::string infoLog(512, '\0');  // pre-allocate space
        GLsizei length;
        glGetShaderInfoLog(vertexShader, (GLsizei)infoLog.size(), &length, &infoLog[0]);
        infoLog.resize(length);

        LOG_WARNING("Shader compilation failed: {}", infoLog);
    }

	glCompileShader(vertexShader);

    // fragment shader
	std::string fs_source;
	neu::file::ReadTextFile("Shaders/basic.frag", fs_source);
	const char* fs_cstr = fs_source.c_str();

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fs_cstr, NULL);
	glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::string infoLog(512, '\0');  // pre-allocate space
        GLsizei length;
        glGetShaderInfoLog(fragmentShader, (GLsizei)infoLog.size(), &length, &infoLog[0]);
        infoLog.resize(length);

        LOG_WARNING("Shader compilation failed: {}", infoLog);
    }

    // shader program
    GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

    // uniform
    GLint uniform = glGetUniformLocation(shaderProgram, "u_time");
    ASSERT(uniform != 1);

	GLint texUniform = glGetUniformLocation(shaderProgram, "u_texture");
	glUniform1i(texUniform, 0); //GL_TEXTURE0

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        std::string infoLog(512, '\0');  // pre-allocate space
        GLsizei length;
        glGetProgramInfoLog(shaderProgram, (GLsizei)infoLog.size(), &length, &infoLog[0]);
        infoLog.resize(length);

        LOG_WARNING("Shader Link compilation failed: {}", infoLog);
    }

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
        neu::GetEngine().GetRenderer().Clear();

        neu::vec2 mouse = neu::GetEngine().GetInput().GetMousePosition();
        neu::vec2 position = { mouse.x, mouse.y };
        float angle = neu::GetEngine().GetTime().GetTime() * 50;

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
		

        // draw
        glUniform1f(uniform, neu::GetEngine().GetTime().GetTime());
		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, (GLsizei)points.size());

        glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

        /*glPushMatrix();
        
        glScalef(neu::math::cos(angle * 0.05), neu::math::sin(angle * 0.05), 1.0);
        glRotatef(angle, 0, 0, 1);
        glTranslatef(position.x, position.y, 0);

        glBegin(GL_TRIANGLES);
        for (int i = 0; i < points.size(); i++) {
            
            glColor3f(colors[i].r, colors[i].g, colors[i].b);
            glVertex3f(points[i].x, points[i].y, points[i].z);
            
		}
        glEnd();
        glPopMatrix();*/
        


        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
