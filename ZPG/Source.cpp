#include <GL/glew.h>
#include "Application.h"

int main()
{
	DependencyResolver::GetInstance().Register();

	if (!Application::GetInstance().Initialize())
		exit(EXIT_FAILURE);

 	Application::GetInstance().Run();
	return 0;
}
