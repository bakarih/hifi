//
//  AudioToolBox.h
//  interface/src/audio
//
//  Created by Stephen Birarda on 2014-12-16.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_AudioToolBox_h
#define hifi_AudioToolBox_h

#include <DependencyManager.h>
#include <GeometryCache.h>
#include <QOpenGLTexture>

class AudioToolBox : public Dependency {
    SINGLETON_DEPENDENCY
public:
    void render(int x, int y, int padding, bool boxed);
    
    bool mousePressEvent(int x, int y);
protected:
    AudioToolBox();
private:
    gpu::TexturePointer _micTexture;
    gpu::TexturePointer _muteTexture;
    gpu::TexturePointer _boxTexture;
    int _boxQuadID = GeometryCache::UNKNOWN_ID;
    QRect _iconBounds;
    qint64 _iconPulseTimeReference = 0;
};

#endif // hifi_AudioToolBox_h