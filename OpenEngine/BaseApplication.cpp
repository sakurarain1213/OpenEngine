#include "BaseApplication.h"
#include<stdio.h>
int My::BaseApplication::Initialize()
{
    m_bQuit = false;

    return 0;
}


// Finalize all sub modules and clean up all runtime temporary files.
void My::BaseApplication::Finalize()
{
}


// One cycle of the main loop
void My::BaseApplication::Tick()
{
    printf("sd\n");
}

bool My::BaseApplication::IsQuit()
{
    return m_bQuit;
}

int My::BaseApplication::GetName() {
    return 0;
}