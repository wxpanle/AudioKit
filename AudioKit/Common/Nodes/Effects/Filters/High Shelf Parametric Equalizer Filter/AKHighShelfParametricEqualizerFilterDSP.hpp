//
//  AKHighShelfParametricEqualizerFilterDSP.hpp
//  AudioKit
//
//  Created by Aurelius Prochazka, revision history on Github.
//  Copyright © 2018 AudioKit. All rights reserved.
//

#pragma once

#import <AVFoundation/AVFoundation.h>

typedef NS_ENUM(AUParameterAddress, AKHighShelfParametricEqualizerFilterParameter) {
    AKHighShelfParametricEqualizerFilterParameterCenterFrequency,
    AKHighShelfParametricEqualizerFilterParameterGain,
    AKHighShelfParametricEqualizerFilterParameterQ,
    AKHighShelfParametricEqualizerFilterParameterRampTime
};

#ifndef __cplusplus

void* createHighShelfParametricEqualizerFilterDSP(int nChannels, double sampleRate);

#else

#import "AKSoundpipeDSPBase.hpp"

class AKHighShelfParametricEqualizerFilterDSP : public AKSoundpipeDSPBase {
private:
    struct _Internal;
    std::unique_ptr<_Internal> _private;
 
public:
    AKHighShelfParametricEqualizerFilterDSP();
    ~AKHighShelfParametricEqualizerFilterDSP();

    float centerFrequencyLowerBound = 12.0;
    float centerFrequencyUpperBound = 20000.0;
    float gainLowerBound = 0.0;
    float gainUpperBound = 10.0;
    float qLowerBound = 0.0;
    float qUpperBound = 2.0;

    float defaultCenterFrequency = 1000;
    float defaultGain = 1.0;
    float defaultQ = 0.707;

    int defaultRampTimeSamples = 10000;

    // Uses the ParameterAddress as a key
    void setParameter(AUParameterAddress address, float value, bool immediate) override;

    // Uses the ParameterAddress as a key
    float getParameter(AUParameterAddress address) override;
    
    void init(int _channels, double _sampleRate) override;

    void destroy();

    void process(AUAudioFrameCount frameCount, AUAudioFrameCount bufferOffset) override;
};

#endif
