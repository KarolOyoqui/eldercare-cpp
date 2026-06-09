#include <iostream>
#include "Menu.h"

bool checkFiles()
{
	// Implementación mínima: en un sistema real verificaría la existencia y permisos
	return true;
}

int main()
{
	if (!checkFiles()) {
		std::cerr << "Error: archivos necesarios no disponibles.\n";
		return 1;
	}

	Menu menu;
	menu.run();

	return 0;
}
