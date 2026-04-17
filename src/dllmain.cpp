#include "pch.h"
#include "core/hooks.h"
#include "core/jvm_wrapper.h"

static HMODULE g_hModule = nullptr;

DWORD WINAPI BapeInit(LPVOID param) {
    // 1. Iniciar consola para debug (opcional, quitar en producción)
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    printf("[Bape] Cargando cliente interno...\n");

    // 2. Adjuntar a la JVM
    if (!JvmWrapper::init()) {
        printf("[Bape] Error: No se pudo encontrar la JVM de Minecraft.\n");
        FreeLibraryAndExitThread(g_hModule, 0);
        return 0;
    }

    // 3. Iniciar Hooks (wglSwapBuffers para el menú)
    if (!Hooks::init()) {
        printf("[Bape] Error: No se pudieron activar los hooks de renderizado.\n");
        FreeLibraryAndExitThread(g_hModule, 0);
        return 0;
    }

    printf("[Bape] Inyección exitosa. Presiona INSERT para el menú.\n");

    // Bucle principal para mantener la DLL cargada
    while (!(GetAsyncKeyState(VK_DELETE) & 1)) {
        Sleep(100);
    }

    // Cleanup
    Hooks::shutdown();
    JvmWrapper::shutdown();
    
    printf("[Bape] Cliente descargado.\n");
    FreeLibraryAndExitThread(g_hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_hModule = hModule;
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, BapeInit, nullptr, 0, nullptr);
    }
    return TRUE;
}
