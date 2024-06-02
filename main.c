// Glitch shader by Apfelstrudel Technologien.

#include "raylib.h"

int main(void) {
    // Init window & camera.
    const int winW = 800;
    const int winH = 450;

    InitWindow(winW, winH, "3D Glitch Shader.");

    Camera cam3d = {{0.0f, 5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};

    // Load shader and create post processing texture.
    Shader gShader = LoadShader(0, "glitch.fs");

    int tLocSh = GetShaderLocation(gShader, "time");

    RenderTexture2D target = LoadRenderTexture(winW, winH);

    // Update glitch properties.
    Vector2 winRes = {winW, winH};

    float chromaMult = 0.009;
    float gMult = 0.001;
    float tMult = 1.0;

    SetShaderValue(gShader, GetShaderLocation(gShader, "winRes"), &winRes, SHADER_UNIFORM_VEC2);

    SetShaderValue(gShader, GetShaderLocation(gShader, "chromaMult"), &chromaMult, SHADER_UNIFORM_FLOAT);
    SetShaderValue(gShader, GetShaderLocation(gShader, "gMult"), &gMult, SHADER_UNIFORM_FLOAT);
    SetShaderValue(gShader, GetShaderLocation(gShader, "tMult"), &tMult, SHADER_UNIFORM_FLOAT);

    // Main loop.
    while (!WindowShouldClose()) {
        // Update camera.
        UpdateCamera(&cam3d, CAMERA_ORBITAL);

        // 3D Code.
        BeginTextureMode(target);
            ClearBackground(BLACK);

            BeginMode3D(cam3d);
                DrawCube((Vector3) {0, 0, 0}, 2.0f, 2.0f, 2.0f, WHITE);
            EndMode3D();
        EndTextureMode();

        // Render post processing shader and FPS.
        BeginDrawing();
            ClearBackground(BLACK);

            float time = GetTime();

            SetShaderValue(gShader, tLocSh, &time, SHADER_UNIFORM_FLOAT);

            BeginShaderMode(gShader);
                DrawTextureRec(target.texture, (Rectangle) {0, 0, (float) target.texture.width, (float) -target.texture.height}, (Vector2) {0, 0}, WHITE);
            EndShaderMode();

            DrawFPS(1, 1);
        EndDrawing();
    }

    // Unload and close.
    UnloadShader(gShader);
    UnloadRenderTexture(target);

    CloseWindow();

    return 0;
}
