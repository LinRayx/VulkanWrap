//
//  test_main.cpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#include "Engine.h"

Engine* Engine::m_Engine = nullptr;
int main() {
    
    Engine* engine = Engine::GetInstance();
    engine->Run();
    return 0;
}
