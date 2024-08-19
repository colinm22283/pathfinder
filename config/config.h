#pragma once

#include <render/render.h>

#define CLEAR_COLOR (color){100,100,100,255}
#define RENDER_DEFAULT_FLAGS RENDER_FLAGS_NONE

#define AUDIO_ENABLED 0

#ifndef PEAK_ENGINE_DEBUG_MODE
    #define PEAK_ENGINE_DEBUG_MODE 0
#endif