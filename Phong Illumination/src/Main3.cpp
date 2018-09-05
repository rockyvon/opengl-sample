// OpenGL Shader.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include "Shader.h"
//#include "timeutils.h"
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//static vec3 ZERO_VEC3 = vec3(0.0f);
//
//ShaderManager* shader_model;
//
//
//
//#pragma region 正方形顶点坐标
//unsigned int vao_cube, vbo_cube, tex_cube_dif, tex_cube_spe;
//float vertices_cube[32] = {
//	//|----顶点坐标----|-----法线坐标------|----纹理坐标-----|
//	-0.5f, -0.5f, 0.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,//左下角
//	 0.5f, -0.5f, 0.0f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f,//右下角
//	 0.5f,  0.5f, 0.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,//右上角
//	-0.5f,  0.5f, 0.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f//左上角
//};
//#pragma endregion
//
//#pragma region 矩阵
//mat4 projection;
//#pragma endregion
//
//#pragma region 资源文件路径
//char vertex_model_path[] = "shader/cube.vert";
//char fragment_model_path[] = "shader/cube.frag";
//char model_path[] = "model/nanosuit/nanosuit.obj";
//char cube_texture_diffuse_path[] = "texture/container.png";
//char cube_texture_specular_path[] = "texture/container_specular.png";
//#pragma endregion
//
//#pragma region 光照
////平行光
//LightDirectional ld(vec3(0.0f, -1.0f, -1.0f), vec3(1.0f), vec3(1.0f), vec3(1.0f));
//GLboolean ld_enabled = true;
////点光源
//LightPoint lp1(vec3(3.0f), 1.0f, 0.09f, 0.032f, vec3(0.2f), vec3(0.2f), vec3(1.0f));
//GLboolean lp_enabled = true;
//
////材质
//int shininess = 32;
//#pragma endregion
//
//#pragma region screen
//GLint screen_width = 600, screen_height = 600;
//GLint view_width = 600, view_height = 600;
//#pragma endregion
//
//#pragma region speed
//GLfloat move_speed = 1.0f;
//GLfloat yaw_speed = 0.01f;
//GLfloat pitch_speed = 0.01f;
//#pragma endregion
//
//#pragma region camera
//vec3 camera_position = vec3(0, 0, 10.0f);
//vec3 camera_forward = vec3(0, 0, -1.0f);
//vec3 camera_up = vec3(0, 1.0f, 0);
//#pragma endregion
//
//#pragma region program attribute
//
//GLfloat max_pitch_angle = 45.0f;
//
//GLfloat angle_h = 0;
//GLfloat angle_v = 0;
//
//GLint last_x = -1;
//GLint last_y = -1;
//
//#pragma endregion
//
//mat4 initCamera() 
//{
//	mat4 view = mat4(1.0f);
//	view = lookAt(camera_position, camera_position + camera_forward, camera_up);
//	view = rotate(view, angle_h, vec3(0, 1.0f, 0));
//	view = rotate(view, angle_v, vec3(1.0f, 0, 0));
//	return view;
//}
//
//void initCubeVertex() 
//{
//	glGenVertexArrays(1, &vao_cube);
//	glGenBuffers(1, &vbo_cube);
//	glBindVertexArray(vao_cube);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//}
//
//void initCubeTexture() 
//{
//	glGenTextures(1, &tex_cube_dif);
//	glBindTexture(GL_TEXTURE_2D, tex_cube_dif);
//	// 为当前绑定的纹理对象设置环绕、过滤方式
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// 加载并生成纹理
//	int width, height, nrChannels;
//	unsigned char *data = stbi_load(cube_texture_diffuse_path, &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture:" << cube_texture_diffuse_path << std::endl;
//	}
//	stbi_image_free(data);
//
//	glGenTextures(1, &tex_cube_spe);
//	glBindTexture(GL_TEXTURE_2D, tex_cube_spe);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	data = stbi_load(cube_texture_specular_path, &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture:" << cube_texture_specular_path << std::endl;
//	}
//	stbi_image_free(data);
//}
//
//void drawCube(mat4 model_world) {
//	glBindVertexArray(vao_cube);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, tex_cube_dif);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, tex_cube_spe);
//	
//	shader_model->setUniform1i("material.texture_diffuse", 0);
//	shader_model->setUniform1i("material.texture_specular", 1);
//	shader_model->setUniform1i("material.shininess", 32);
//
//	//前面
//	mat4 model = translate(model_world, vec3(0.0f, 0.0f, 0.5f));
//	shader_model->setUniform3fv("model", 1, value_ptr(model));
//	glDrawArrays(GL_TRIANGLES, 0, 4);
//	//后面
//	model = rotate(model, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
//	model = translate(model, vec3(0.0f, 0.0f, 1.0f));
//	glDrawArrays(GL_POLYGON, 0, 4);
//	
//}
//
//void init() 
//{
//	string log_path = "log/" + TimeUtils::getCompleteTime() + ".log";
//	LogUtils::createInstance()->init(log_path.c_str());
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.5, 0.5, 0.5, 1.0);
//	shader_model = ShaderManager::NewInstance();
//	shader_model->load(vertex_model_path, fragment_model_path);
//	shader_model->use();
//	initCubeVertex();
//	initCubeTexture();
//	
//}
//
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	mat4 view = initCamera();
//
//	shader_model->use();
//	shader_model->setUniformMatrix4fv("projection", 1, value_ptr(projection));
//	shader_model->setUniformMatrix4fv("view", 1, value_ptr(view));
//
//	shader_model->setUniform3fv("camera_position", 1, value_ptr(camera_position));
//
//	shader_model->setUniform3fv("light_directional.direction", 1, value_ptr(ld.direction));
//	shader_model->setUniform3fv("light_directional.ambient", 1, value_ptr(ld.ambient));
//	shader_model->setUniform3fv("light_directional.diffuse", 1, value_ptr(ld.diffuse));
//	shader_model->setUniform3fv("light_directional.specular", 1, value_ptr(ld.specular));
//	
//	shader_model->setUniform3fv("light_point.position", 1, value_ptr(lp1.position));
//	shader_model->setUniform3fv("light_point.ambient", 1, value_ptr(lp1.ambient));
//	shader_model->setUniform3fv("light_point.diffuse", 1, value_ptr(lp1.diffuse));
//	shader_model->setUniform3fv("light_point.specular", 1, value_ptr(lp1.specular));
//	shader_model->setUniform1f("light_point.c", lp1.constant);
//	shader_model->setUniform1f("light_point.l", lp1.linear);
//	shader_model->setUniform1f("light_point.q", lp1.quadratic);
//
//	mat4 model = mat4(1.0f);
//	drawCube(model);
//
//	glutSwapBuffers();
//}
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	projection = perspective(radians(45.0f), float(view_width / view_height), 0.1f, 100.0f);
//	//projection = ortho(-2.0f, 2.0f, -2.0f, 2.0f, 1.5f, 20.0f);
//}
//
//void idle() {
//	glutPostRedisplay();
//}
//
//void mouse(int button, int state, int x, int y) {
//
//}
//
//void mouse_motion(int x, int y) {
//	if (last_x < 0) {
//		last_x = x;
//	}
//	if (last_y < 0) {
//		last_y = y;
//	}
//	angle_h += (x - last_x) * yaw_speed;
//	angle_v += (y - last_y) * pitch_speed;
//	last_x = x;
//	last_y = y;
//}
//
//void keyboard(unsigned char button, int x, int y) {
//	switch (button)
//	{
//	case 'w':
//		cout << "w按下" << endl;
//		camera_position += camera_forward * move_speed;
//		break;
//	case 's':
//		camera_position -= camera_forward * move_speed;
//		break;
//	case '1':
//		ld_enabled = !ld_enabled;
//		break;
//	case '2':
//		lp_enabled = !lp_enabled;
//		break;
//	case '3':
//		
//		break;
//	default:
//		break;
//	}
//}
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowSize(screen_width, screen_height);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("第一个窗口");
//	GLuint result = glewInit();
//	if (result != GLEW_OK) {
//		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(result));
//		return 1;
//	}
//	init();
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutIdleFunc(idle);
//	glutMouseFunc(mouse);
//	glutMotionFunc(mouse_motion);
//	glutKeyboardFunc(keyboard);
//	glutMainLoop();
//	return 0;
//}
