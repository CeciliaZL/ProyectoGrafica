// ===== SoundManager.h =====
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <irrKlang.h>
#include <stdio.h>
using namespace irrklang;


class SoundManager {
private:
    ISoundEngine* engine;
    float masterVolume; // volumen global (0.0 a 1.0)

public:
    SoundManager() {
        engine = createIrrKlangDevice();
        masterVolume = 1.0f;
        if (!engine)
            printf("Error al iniciar irrKlang\n");
    }

    ~SoundManager() {
        if (engine)
            engine->drop();
    }

    // Cambiar volumen global (0.0 = silencio, 1.0 = máximo)
    void setMasterVolume(float vol) {
        masterVolume = vol;
        engine->setSoundVolume(vol);
    }

    float getMasterVolume() const {
        return masterVolume;
    }

    // Música de fondo
    void playMusic(const char* filePath, bool loop = true, float volume = 1.0f) {
        ISound* music = engine->play2D(filePath, loop, false, true);
        if (music) {
            music->setVolume(volume);
            music->drop(); // liberar referencia, el motor sigue reproduciéndolo
        }
    }

    // Efectos (no se repiten)
    void playEffect(const char* filePath, float volume = 1.0f) {
        ISound* fx = engine->play2D(filePath, false, false, true);
        if (fx) {
            fx->setVolume(volume);
            fx->drop();
        }
    }

    // Sonido 3D
    void play3DSound(const char* filePath, float x, float y, float z, float volume = 1.0f) {
        vec3df pos(x, y, z);
        ISound* s3d = engine->play3D(filePath, pos, false, false, true);
        if (s3d) {
            s3d->setVolume(volume);
            s3d->setMinDistance(20.0f);  
            s3d->drop();
        }
    }

    ISound* play3DLoop(const char* filePath, float x, float y, float z, float volume = 1.0f) {
        vec3df pos(x, y, z);
        ISound* s3d = engine->play3D(filePath, pos, true, false, true);
        if (s3d) {
            s3d->setVolume(volume);
            s3d->setMinDistance(2.0f);
        }
        return s3d; // devolvemos el puntero para poder detenerlo
    }




    // Configurar posición del oyente
    void setListener(float x, float y, float z,
        float lx = 0.0f, float ly = 0.0f, float lz = -1.0f)
    {
        vec3df pos(x, y, z);
        vec3df look(lx, ly, lz);
        vec3df vel(0, 0, 0);
        vec3df up(0, 1, 0);

        engine->setListenerPosition(pos, look, vel, up);
    }
};

#endif