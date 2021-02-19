#include <Windows.h>
#include <CommCtrl.h>
#include <shellapi.h>
#include <string>
#include <fstream>
#include "Estructura de datos 2.h"

using namespace std;
struct registro {
	wchar_t imagen[200];
	SYSTEMTIME fecha;
	wchar_t Nombre[256];
	wchar_t Telefono[256];
	int turno;
	registro* siguiente;
	registro* anterior;

};
registro* inicio = NULL;
wchar_t direccion[200];

void agregar(registro* nuevo) {
	if (inicio == NULL) {
		inicio = nuevo;//el siguiente del ultimo debe ser del el primero y el anterior del primero debe ser el ultimo
		nuevo->siguiente = nuevo;
		nuevo->anterior = nuevo;

	}
	else {
		inicio->anterior->siguiente = nuevo;
		nuevo->anterior = inicio->anterior;
		nuevo->siguiente = inicio;
		inicio->anterior = nuevo;

	}

}	

BOOL CALLBACK Callbackregistromecanico(HWND handler, UINT mensaje, WPARAM  wParam, LPARAM lParam) {
	switch (mensaje)
	{
	case WM_CLOSE: {
		EndDialog(handler, 0);
		break;
	}

	default:
		break;
	}
	return false;
}
BOOL CALLBACK CallbackMecanico(HWND handler, UINT mensaje, WPARAM  wParam, LPARAM lParam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_NUEVOREGISTRO_MECANICO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG3), handler, (DLGPROC)Callbackregistromecanico);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_CLOSE: {
		EndDialog(handler, 0);
		break;
	}

	default:
		break;
	}
	return false;
}

BOOL CALLBACK Callbackprincipal(HWND handler, UINT mensaje, WPARAM  wParam, LPARAM lParam) {
	switch (mensaje)
	{
	case WM_CLOSE: {
		EndDialog(handler, 0);
		break;
	}
	
	default:
		break;
	}
	return false;
}
BOOL CALLBACK sesionCallback(HWND handler, UINT mensaje, WPARAM  wParam, LPARAM lParam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case INICIOSESION: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG2), handler, (DLGPROC)Callbackprincipal);
			break;
		}

			default:
			break;
		}
		break;
	}
	case WM_CLOSE: {
		EndDialog(handler, 0);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		break;
	}
	return false;
}

int WINAPI WinMain(HINSTANCE instancia, HINSTANCE legado, LPSTR comando, int modo) {

	DialogBox(instancia, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)sesionCallback);

	return 0;
}