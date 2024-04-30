#include <stdlib.h>
#include <stdio.h>
#include <sklc_lib/Window.h>
#include <sklc_lib/utils/logger.h>

// Test function to create a window and process messages
void TestWindowSystem() {

    // Create a window
    Window* window = CreateSklcWindow(800, 600, "Test Window");
    if (!window) {
        SKLERROR("Failed to create window.");
        return;
    }

    // Main message loop
    while (!window->ShouldClose) {
        ProcessSklcWindowMessages();
    }

    // Clean up and destroy the window
    DestroySklcWindow(window);
}

int main() {
    TestWindowSystem();
    return 0;
}