#pragma once

#include "../Scenes/Scene.hpp"

class SceneManager
{
    public: 
        static void LoadScene(Scene* _scene)
        {
            scene = _scene;
            isSceneLoaded = 1;
            scene->init();
        };

        static void Update()
        {
            #ifdef DEBUG_ITERATIONS // Debugging Iterations: Unconfigured until step by step debugging is needed
                // TraceLog(LOG_INFO, "New Frame");
                // TraceLog(LOG_INFO, "Input Phase: %d", isSceneLoaded);
            #endif
            scene->input();
            #ifdef DEBUG_ITERATIONS
                // TraceLog(LOG_INFO, "New Frame");
                // TraceLog(LOG_INFO, "Update Phase: %d", isSceneLoaded);
            #endif
            scene->update();
            #ifdef DEBUG_ITERATIONS
                // TraceLog(LOG_INFO, "New Frame");
                // TraceLog(LOG_INFO, "Render Phase: %d", isSceneLoaded);
            #endif
            scene->render();
        };

        static int SceneLoaded()
        {
            return isSceneLoaded;
        };
        
    private: 
        inline static int isSceneLoaded;
        inline static Scene *scene;
};