#ifndef SNAPSHOT_CLIENTE
#define SNAPSHOT_CLIENTE

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <vector>
#include "../Texturas/texture_manager.h"
#include "../world.h"
#include "worm.h"
#include "beam.h"
#include "explosion.h"
#include "../Proyectiles/projectile_generator.h"

#include <memory>

using namespace SDL2pp;

// Simula la "imagen" del estado del juego.
class SnapshotCliente {
    private:
    std::map<int, std::shared_ptr<Worm>> worms;
    std::vector<Beam> beams;
    int _id_camera;
    uint32_t id_turno_actual;
    std::vector<std::unique_ptr<ProjectileClient>> projectiles;
    std::vector<int> sonidos;
    std::vector<ExplosionCliente> explosiones;
 
    public:
    //Constructor
    SnapshotCliente(int id_camera);

    std::map<int, std::shared_ptr<Worm>> get_worms();

    //Agrega un gusano a la lista de gusanos
    void add_worm(std::shared_ptr<Worm> worm, int id);

    void add_beam(Beam beam);

    void add_projectile(std::unique_ptr<ProjectileClient> projectil);

    void add_sound(int sound_code);

    void add_explosion(ExplosionCliente explosion);

/*
    void present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        int& window_width,
                        int& window_height,
                        float& x_scale,
                        float& y_scale);
*/

    void apply_to_world(World& world);

    void agregar_turno_actual(uint32_t id);

    void imprimir_posiciones();

    void actulizar_camara(uint32_t id);


    
};

#endif
