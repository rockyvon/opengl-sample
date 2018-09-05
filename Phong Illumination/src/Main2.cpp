
//// OpenGL Shader.cpp: 定义控制台应用程序的入口点。
////
//
//#include "stdafx.h"
//#include "Shader.h"
//#include "timeutils.h"
//
//static vec3 ZORO_VEC3 = vec3(0.0f);
//
//GLuint vao_rect, vbo_rect, ibo_rect;
//GLuint vao_axis, vbo_axis;
//GLuint vao_light_point, vbo_light_point, ibo_light_point;
//GLuint texture_box, texture_smile;
//ShaderManager* shader_rect;
//ShaderManager* shader_axis;
//ShaderManager* shader_light_point;
//
//#pragma region 坐标
//float vertices_rect[] =
//{
//	//前
//	//|----顶点坐标----|------颜色------|-纹理坐标-|-----法线向量----|
//	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0, 0.0, 1.0f, 1.0f, 1.0f,	//左下角
//	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0, 0.0, 1.0f, 1.0f, 1.0f,	//右下角
//	 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0, 1.0, 1.0f, 1.0f, 1.0f,	//右上角
//	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0, 1.0, 1.0f, 1.0f, 1.0f,	//左上角
//};
//
//GLuint indices_rect[] =
//{
//	0, 1, 2,	//第一个三角形
//	0, 2, 3,	//第二个三角形
//};
//
//float vertices_axis[] =
//{
//	//x axis
//	0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//	10.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//	//y axis
//	0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//	0.0f,  10.0f, 0.0f,  0.0f,  1.0f,  0.0f,
//	//z axis
//	0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//	0.0f,  0.0f,  10.0f, 0.0f,  0.0f,  1.0f,
//};
//
//float vertices_light_Point[] = 
//{ 
//	//前
//	//|----顶点坐标----|-------颜色------|
//	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,	//左下角
//	 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,	//右下角
//	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,	//右上角
//	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,	//左上角*/
//};
//
//GLuint indices_light_Point[] =
//{
//	0, 1, 2,	//第一个三角形
//	0, 2, 3,	//第二个三角形
//};
//
//#pragma endregion
//
//#pragma region 矩阵
//mat4 projection;
//#pragma endregion
//
//#pragma region resource path
//char vertex_cube_path[]		= "shader/cube.vert";
//char fragment_cube_path[]	= "shader/cube.frag";
//char vertex_axis_path[]		= "shader/axis.vert";
//char fragment_axis_path[]	= "shader/axis.frag";
//char vertex_light_point_path[]		= "shader/light_point.vert";
//char fragment_light_point_path[]	= "shader/light_point.frag";
//char texture_box_path[]		= "texture/texture3.jpg";
//char texture_smile_path[]	= "texture/texture4.png";
//#pragma endregion
//
//#pragma region 光照
//vec3 light_position = vec3(0.0f, 0.0f, -3.0f);
////环境光
//GLboolean ambient_enabled = true;
//vec3 light_ambient = vec3(1.0f, 1.0f, 1.0f) * 0.1f;
//vec3 material_ambient = vec3(0.0f, 1.0f, 0.0f);
////漫反射
//GLboolean diffuse_enabled = true;
//vec3 light_diffuse = vec3(1.0f, 1.0f, 1.0f);
//vec3 material_diffuse = vec3(0.0f, 1.0f, 0.0f);
////高光
//GLboolean specular_enabled = true;
//vec3 light_specular = vec3(1.0f, 1.0f, 1.0f);
//vec3 material_specular = vec3(1.0f, 1.0f, 1.0f);
//GLint specular_shininess = 4;
//#pragma endregion
//
//#pragma region 材质
//
//#pragma endregion
//
//
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
//mat4 initCamera() {
//	mat4 view = mat4(1.0f);
//	view = lookAt(camera_position, camera_position + camera_forward, camera_up);
//	view = rotate(view, angle_h, vec3(0, 1.0f, 0));
//	view = rotate(view, angle_v, vec3(1.0f, 0, 0));
//	return view;
//}
//
//void drawAxis() {
//	mat4 model = mat4(1.0f);
//	glBindVertexArray(vao_axis);
//	//绘制坐标轴
//	glLineWidth(2.0f);
//	glLineStipple(5, 0x1C47);
//	glEnable(GL_LINE_STIPPLE);
//
//	shader_axis->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawArrays(GL_LINES, 0, 6);
//}
//
//void drawCube(mat4 model_global) {
//	mat4 model = mat4(1.0f);
//	//绘制立方体
//	glBindVertexArray(vao_rect);
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture_box);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, texture_smile);
//
//	//前面
//	model = mat4(1.0f);
//	model = translate(model_global, vec3(0, 0, 0.5f));
//	shader_rect->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//后面
//	model = rotate(model, radians(180.0f), vec3(0, 1.0f, 0));
//	model = translate(model, vec3(0.0f, 0.0f, 1.0f));
//	shader_rect->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//左面
//	
//	model = rotate(model_global, radians(90.0f), vec3(0, 1.0f, 0));
//	model = translate(model, vec3(0, 0, 0.5f));
//	shader_rect->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//右面
//	model = rotate(model, radians(180.0f), vec3(0, 1.0f, 0));
//	model = translate(model, vec3(0.0f, 0.0f, 1.0f));
//	shader_rect->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//下面
//	
//	model = rotate(model_global, radians(90.0f), vec3(1.0f, 0, 0));
//	model = translate(model, vec3(0, 0, 0.5f));
//	shader_rect->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//上面
//	model = rotate(model, radians(180.0f), vec3(1.0f, 0.0f, 0.0f));
//	model = translate(model, vec3(0.0f, 0.0f, 1.0f));
//	shader_rect->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//}
//
//void drawLightPoint() 
//{
//	mat4 model = mat4(1.0f);
//	mat4 model_world = translate(model, light_position);
//	
//	glBindVertexArray(vao_light_point);
//
//	//前面
//	model = translate(model_world, vec3(0.0f, 0.0f, 0.5f));
//	shader_light_point->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//后面
//	model = translate(model, vec3(0.0f, 0.0f, -1.0f));
//	shader_light_point->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//左面
//	model = rotate(model_world, radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
//	model = translate(model, vec3(0.0f, 0.0f, 0.5f));
//	shader_light_point->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//右面
//	model = translate(model, vec3(0.0f, 0.0f, -1.0f));
//	shader_light_point->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//下面
//	model = rotate(model_world, radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
//	model = translate(model, vec3(0.0f, 0.0f, 0.5f));
//	shader_light_point->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	//上面
//	model = translate(model, vec3(0.0f, 0.0f, -1.0f));
//	shader_light_point->setUniformMatrix4fv("model", 1, value_ptr(model));
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *)(0 * sizeof(GL_UNSIGNED_INT)));
//	
//}
//
//void initRectBuffer()
//{
//	glGenVertexArrays(1, &vao_rect);
//	glGenBuffers(1, &vbo_rect);
//	glGenBuffers(1, &ibo_rect);
//
//	glBindVertexArray(vao_rect);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_rect);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rect), vertices_rect, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_rect);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rect), indices_rect, GL_STATIC_DRAW);
//
//	//顶点
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
//	glEnableVertexAttribArray(0);
//	//颜色
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	//法线
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(8 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//}
//
//void initAxisBuffer() 
//{
//	glGenVertexArrays(1, &vao_axis);
//	glGenBuffers(1, &vbo_axis);
//
//	glBindVertexArray(vao_axis);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_axis);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_axis), vertices_axis, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//}
//
//void initLightPointBuffer() 
//{
//	glGenVertexArrays(1, &vao_light_point);
//	glGenBuffers(1, &vbo_light_point);
//	glGenBuffers(1, &ibo_light_point);
//
//	glBindVertexArray(vao_light_point);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_light_point);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_light_Point), vertices_light_Point, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_light_point);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_light_Point), indices_light_Point, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//}
//
//void initRectTexture()
//{
//	unsigned char* data;
//	glGenTextures(1, &texture_box);
//	stbi_set_flip_vertically_on_load(true);
//	//加载第一个纹理
//	glBindTexture(GL_TEXTURE_2D, texture_box);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	GLint width, height, channel_count;
//	
//	data = stbi_load(texture_box_path, &width, &height, &channel_count, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		stbi_image_free(data);
//	}
//	else {
//		cout << "加载纹理失败:" << texture_box_path << endl;
//	}
//	
//	//加载第二个纹理
//	glGenTextures(1, &texture_smile);
//	glBindTexture(GL_TEXTURE_2D, texture_smile);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	data = stbi_load(texture_smile_path, &width, &height, &channel_count, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		stbi_image_free(data);
//	}
//	else {
//		cout << "加载纹理失败:" << texture_smile_path << endl;
//	}
//
//	//纹理坐标
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (void *)(6 * sizeof(GL_FLOAT)));
//	glEnableVertexAttribArray(2);
//
//	//指定纹理采样
//	shader_rect->setUniform1i("texture1", 0);
//	shader_rect->setUniform1i("texture2", 1);
//}
//
//void init() {
//	
//	string log_path = "log/" + TimeUtils::getCompleteTime() + ".log";
//	LogUtils::createInstance()->init(log_path.c_str());
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.5, 0.5, 0.5, 1.0);
//
//	shader_rect = ShaderManager::NewInstance();
//	shader_rect->load(vertex_cube_path, fragment_cube_path);
//	initRectBuffer();
//	shader_rect->use();
//	initRectTexture();
//	
//	shader_axis = ShaderManager::NewInstance();
//	shader_axis->load(vertex_axis_path, fragment_axis_path);
//	initAxisBuffer();
//
//	shader_light_point = ShaderManager::NewInstance();
//	shader_light_point->load(vertex_light_point_path, fragment_light_point_path);
//	initLightPointBuffer();
//}
//
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	mat4 view = initCamera();
//	
//	shader_axis->use();
//	shader_axis->setUniformMatrix4fv("projection", 1, value_ptr(projection));
//	shader_axis->setUniformMatrix4fv("view", 1, value_ptr(view));
//	drawAxis();
//
//	shader_rect->use();
//	shader_rect->setUniformMatrix4fv("view", 1, value_ptr(view));
//	shader_rect->setUniformMatrix4fv("projection", 1, value_ptr(projection));
//	shader_rect->setUniform3fv("view_position", 1, value_ptr(camera_position));
//	
//	//shader_rect->setUniform3fv("material.ambient", 1, value_ptr(material_ambient));
//	//shader_rect->setUniform3fv("material.diffuse", 1, value_ptr(material_diffuse));
//	shader_rect->setUniform3fv("material.specular", 1, value_ptr(material_specular));
//	shader_rect->setUniform1i("material.shininess", specular_shininess);
//
//	shader_rect->setUniform3fv("light.direction", 1, value_ptr(light_position));
//	shader_rect->setUniform3fv("light.ambient", 1, value_ptr(ambient_enabled ? light_ambient : ZORO_VEC3));
//	shader_rect->setUniform3fv("light.diffuse", 1, value_ptr(diffuse_enabled ? material_diffuse : ZORO_VEC3));
//	shader_rect->setUniform3fv("light.specular", 1, value_ptr(specular_enabled ? material_specular : ZORO_VEC3));
//	mat4 model1 = mat4(1.0f);
//	model1 = translate(model1, vec3(2.0f, 2.0f, 4.0f));
//	drawCube(model1);
//	
//	shader_light_point->use();
//	shader_light_point->setUniformMatrix4fv("view", 1, value_ptr(view));
//	shader_light_point->setUniformMatrix4fv("projection", 1, value_ptr(projection));
//	drawLightPoint();
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
//		case 'w':
//			cout << "w按下" << endl;
//			camera_position += camera_forward * move_speed;
//		break;
//		case 's':
//			camera_position -= camera_forward * move_speed;
//		break;
//		case '1':
//			ambient_enabled = !ambient_enabled;
//		break;
//		case '2':
//			diffuse_enabled = !diffuse_enabled;
//		break;
//		case '3':
//			specular_enabled = !specular_enabled;
//		break;
//		default:
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
//
