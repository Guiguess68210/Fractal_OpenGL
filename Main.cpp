// Inclure les librairies glad et GLFW3
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/matrix_transform.hpp>
#include <GLM/glm/gtc/type_ptr.hpp>
// Autres librairies et classes
#include <iostream>
#include <cmath>
#include <polygone.h>
#include <segment.h>
#include <vector>
#include <algorithm>
#include <enveloppe.h>

// Paramètres du vertex shader → attributs de sommets (position, couleur, coordonnées de texture)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"	gl_Position = transform * vec4(aPos, 1.0f);\n"
"	ourColor = aColor;\n"
"}\0";

// Paramètres du fragment shader → valeurs interpolées des sommets (position, couleur, coordonnées de texture, profondeur)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

// Hauteur et largeur de la fenètre
const int WIDTH = 800;
const int HEIGH = 800;

// Direction du sens de rotation
int direction = 1;
// Vitesse de la rotation
float speed = 0.0f;
// Profondeur de récursion
int depth = 0;

// Paramètres d'intéraction des touches du clavier et de la souris
bool leftkeytable = false;
bool rightkeytable = false;
bool leftButtonMouse = false;

// Paramètres de translation
double Xtranslate = 0.0f;
double Ytranslate = 0.0f;

Polygone* polygone = new Polygone();


// Fonction définissant les dimensions de la fenêtre lorsque l'utilisateur ou l'OS la redimensionne
void framebuffer_size_callback(GLFWwindow* window, int width = WIDTH, int heigh = HEIGH)
{
	glViewport(0, 0, 1000, 1000);
}

// Intéractions avec les touches du clavier et la souris
void processInput(GLFWwindow* window)
{
	// Si echap alors fermer la fenêtre
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Si la touche directionnelle de gauche est pressée alors diminution de la profondeur
	// La valeur minimum de la profondeur est 0
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		leftkeytable = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS && leftkeytable)
	{
		leftkeytable = false;
		depth--;
		if (depth < 0)
			depth = 0;
	}
	// Si la touche directionnelle de droite est pressée alors augmentation de la profondeur
	// La valeur maximum de la profondeur est 5
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rightkeytable = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS && rightkeytable)
	{
		rightkeytable = false;
		depth++;
		if (depth > 5)
			depth = 5;
	}
	// Si la touche A est pressée alors la direction de la rotation s'effectue dans le sens trigonométrique
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		direction = 1;
	}
	// Si la touche D est pressée alors la direction de la rotation s'effectue dans le sens horaire
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		direction = -1;
	}
	// Si la touche W est pressée alors la vitesse de rotation augmente
	// La valeur maximum de la vitesse est 3.0f
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		speed += 0.1f;
		if (speed > 3.0f)
			speed = 3.0f;
	}
	// Si la touche W est pressée alors la vitesse de rotation augmente
	// La valeur minimale de la vitesse est 0.5f
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		speed -= 0.1f;
		if (speed < 0.1f)
			speed = 0.0f;
	}
	// Si on intéragit avec la souris, que l'on fait un clique gauche et que l'on reste cliqué dessus
	// L'objet va pouvoir translater dans toute la fenêtre
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double X, Y;
		glfwGetCursorPos(window, &X, &Y);
		Xtranslate = (X - WIDTH / 2.0) / 800.0;
		Ytranslate = (HEIGH / 2.0 - Y) / 800.0;
	}
	// Instanciation d'un rectangle
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		polygone = new Polygone();
		// Instanciation des points
		std::vector<Point> listPoints;
		Point a = Point(-0.433f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
		Point b = Point(-0.433f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
		Point c = Point(0.433f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f);
		Point d = Point(0.433f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f);

		listPoints.push_back(a);
		listPoints.push_back(d);
		listPoints.push_back(c);
		listPoints.push_back(b);

		enveloppe(listPoints, *polygone);
	}

	// Instanciation d'un carré
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		polygone = new Polygone();
		// Instanciation des points
		std::vector<Point> listPoints;
		Point a = Point(-0.433f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
		Point b = Point(-0.433f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
		Point c = Point(-0.183f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f);
		Point d = Point(0.183f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f);

		listPoints.push_back(a);
		listPoints.push_back(d);
		listPoints.push_back(c);
		listPoints.push_back(b);

		enveloppe(listPoints, *polygone);
	}

	// Instanciation d'un triangle
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		polygone = new Polygone();
		// Instanciation des points
		Point a = Point(-0.433f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
		Point b = Point(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
		Point c = Point(0.433f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f);

		enveloppe(a, b, c, *polygone);
	}
	// Instanciation d'une droite
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		polygone = new Polygone();
		// Instanciation des points
		Point a = Point(-0.433f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
		Point b = Point(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);

		polygone->ajouteSommet(a, nullptr);
		polygone->ajouteSommet(b, polygone->premier());
	}
}

// Implémentation des coordonnées d'un tiers de segment
Point implementation(Point a, Point b, float length)
{
	float x = a.x() + (b.x() - a.x()) * length;
	float y = a.y() + (b.y() - a.y()) * length;
	float z = 0.0f;

	Point segmentEndPoints = Point(x, y, z, 0.1f, 0.1f, 0.1f);

	return segmentEndPoints;
}

// Calcul des coordonnées du sommet le plus haut du triangle
Point caculateTriangleVertex(Point a, Point b)
{
	float segmentX = b.x() - a.x();
	float segmentY = b.y() - a.y();
	float segmentZ = 0.0f;
	// Construction du segement entre A et B
	Segment segmentEndPoints = Segment(segmentX, segmentY, segmentZ);


	// Calcul du sommet du triangle
	float triangleVertexX = (segmentEndPoints.x() * cos(glm::radians(60.0f)) - segmentEndPoints.y() * sin(glm::radians(60.0f))) + a.x();
	float triangleVertexY = (segmentEndPoints.x() * sin(glm::radians(60.0f)) + segmentEndPoints.y() * cos(glm::radians(60.0f))) + a.y();
	float trianglevertexZ = 0.0f;
	Point triangleVertex = Point(triangleVertexX, triangleVertexY, trianglevertexZ, 0.1, 0.1, 0.1);

	return triangleVertex;
}

// Lignes de division
void dividLine(Point a, Point b, int Depth)
{
	// Si le segment de ligne composé des deux extrémités des paramètres d'entrée actuels n'est plus fractal
	// L'afficher directement
	if (Depth == 0)
	{
		// Paramétrage des données du vertex shader et du/des buffer(s) avec la configuration des attributs du vertex
		float vertices[] = {
			// positions   // couleurs
			a.x(), a.y(), a.z(), a.r(), a.g(), a.b(),
			b.x(), b.y(), b.z(), b.r(), b.g(), b.b()
		};

		// Affichage des segments
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_LINES, 0, 2);
	}
	else
	{
		// Calculs des coordonnées des tiers de segments + l'angle du sommet du triangle
		Point segmentThird1 = implementation(a, b, 1.0f / 3.0f);
		Point segmentThird2 = implementation(a, b, 2.0f / 3.0f);
		Point triangleAngle = caculateTriangleVertex(segmentThird1, segmentThird2);

		// Prendre 2 points adjacents dans les 5 points pour construire la récursivité
		dividLine(a, segmentThird1, Depth - 1);
		dividLine(segmentThird1, triangleAngle, Depth - 1);
		dividLine(triangleAngle, segmentThird2, Depth - 1);
		dividLine(segmentThird2, b, Depth - 1);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGH, "Fractal_OpenGL", nullptr, nullptr);

	// Si l'ouverture de la fenêtre ne s'effectue pas ou si glad ne s'initialise pas
	if (window == nullptr)
	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Redimensionnement de la fenêtre
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Compilation du vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// Si la compilation a échoué, affichage d'un message d'erreur
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Compilation du fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	// Si la compilation a échoué, affichage d'un message d'erreur
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Compilation du programme
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Si la compilation a échoué, affichage d'un message d'erreur
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Libère de la mémoire en marquant le vertex et le fragment shader à supprimer
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Polygone* polygone = new Polygone();

	// Instanciation des points
	//Point a = Point(-0.433f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f);
	//Point b = Point (0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Point c  = Point(0.433f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f);

	//enveloppe(a, b, c, *polygone);

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Relier tableau de sommets, puis configurer les attributs de sommet.
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Attribut de position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Attribut de couleur
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	float angle = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// Couleur d'arrière plan
		glClearColor(1.0f, 1.0f, 1.0f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Animations de la forme
		glm::mat4 trans = glm::mat4(1.0f);
		// Souris
		trans = glm::translate(trans, glm::vec3(Xtranslate, Ytranslate, 0.0));
		// Touches
		trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

		angle += direction * speed;

		// Activation du shader
		glUseProgram(shaderProgram);
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		
		Sommet* vertex = polygone->premier();

		if (vertex != nullptr) {
			dividLine(vertex->coordonnees(), vertex->suivant()->coordonnees(), depth);
			vertex = vertex->suivant();
			// Récursivité 
			do
			{
				dividLine(vertex->coordonnees(), vertex->suivant()->coordonnees(), depth);
				vertex = vertex->suivant();
			} while (vertex != polygone->premier());
		}

		// Echange des buffers et interrogations des éléments (touches et souris)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Désallouer toutes les ressources une fois qu'elles ont dépassé leur objectif
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Fin et suppression de toutes les ressources GLFW précédemment allouées.
	glfwTerminate();
	return 0;
}