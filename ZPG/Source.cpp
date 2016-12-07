#include <GL/glew.h>
#include "Application.h"

#include <time.h>

int main()
{
	srand(time(0));

	DependencyResolver::GetInstance().Initialize();

	if (!Application::GetInstance().Initialize())
		exit(EXIT_FAILURE);

 	Application::GetInstance().Run();
	return 0;
}
