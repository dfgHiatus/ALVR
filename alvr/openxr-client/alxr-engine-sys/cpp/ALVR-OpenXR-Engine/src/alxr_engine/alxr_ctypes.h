#pragma once
#ifndef ALXR_ENGINE_CTYPES_H
#define ALXR_ENGINE_CTYPES_H

#ifndef ALXR_CLIENT
#define ALXR_CLIENT
#endif
#include "bindings.h"

#ifdef __cplusplus
extern "C" {;
#endif

enum ALXRGraphicsApi
{
    Auto,
    Vulkan2,
    Vulkan,
    D3D12,
    D3D11,
    OpenGLES,
    OpenGL,
    ApiCount = OpenGL
};

enum ALXRDecoderType
{
    D311VA,
    NVDEC,
    CUVID,
    VAAPI,
    CPU
};

enum ALXRTrackingSpace
{
    LocalRefSpace,
    StageRefSpace,
    ViewRefSpace
};

enum ALXRCodecType
{
    H264_CODEC,
    HEVC_CODEC
};

struct ALXRSystemProperties
{
    char         systemName[256];
    float        currentRefreshRate;
    const float* refreshRates;
    unsigned int refreshRatesCount;
    unsigned int recommendedEyeWidth;
    unsigned int recommendedEyeHeight;
};

struct ALXREyeInfo
{
    EyeFov eyeFov[2];
    float ipd;
};

struct ALXRRustCtx
{
    void (*inputSend)(const TrackingInfo* data);
    void (*viewsConfigSend)(const ALXREyeInfo* eyeInfo);
    unsigned long long (*pathStringToHash)(const char* path);
    void (*timeSyncSend)(const TimeSync* data);
    void (*videoErrorReportSend)();
    void (*batterySend)(unsigned long long device_path, float gauge_value, bool is_plugged);
    void (*setWaitingNextIDR)(const bool);
    void (*requestIDR)();

    ALXRGraphicsApi graphicsApi;
    ALXRDecoderType decoderType;

    bool verbose;
    bool disableLinearizeSrgb;
#ifdef XR_USE_PLATFORM_ANDROID
    void* applicationVM;
    void* applicationActivity;
#endif
};

struct ALXRGuardianData {
    bool shouldSync;
    float areaWidth;
    float areaHeight;
};

struct ALXRRenderConfig
{
    unsigned int eyeWidth;
    unsigned int eyeHeight;
    float refreshRate;
    float foveationCenterSizeX;
    float foveationCenterSizeY;
    float foveationCenterShiftX;
    float foveationCenterShiftY;
    float foveationEdgeRatioX;
    float foveationEdgeRatioY;
    bool enableFoveation;
};

struct ALXRDecoderConfig
{
    ALXRCodecType codecType;
    bool          enableFEC;
    bool          realtimePriority;
    unsigned int  cpuThreadCount; // only used for software decoding.
};

struct ALXRStreamConfig {
    ALXRTrackingSpace   trackingSpaceType;
    ALXRRenderConfig    renderConfig;
    ALXRDecoderConfig   decoderConfig;
};


// TODO Add the rest of the eye information
struct ALXREyeTrackingInfo{
    float a;
};

// TODO Get XR_FACE_EXPRESSION_COUNT_FB, XR_FACE_CONFIDENCE_COUNT_FB programatically
struct ALXRFaceTrackingInfo{
    float weights[63];
    // float validity[63];
    // float confidence[63];
};

#ifdef __cplusplus
}
#endif
#endif
