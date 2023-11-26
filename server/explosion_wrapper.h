#ifndef EXPLOSION_WRAPPER_H
#define EXPLOSION_WRAPPER_H

class ExplosionWrapper {
private:
    float x_pos;
    float y_pos;
    float radius;
    uint32_t id;
public:
    ExplosionWrapper(float x_pos, float y_pos, float radius, uint32_t id_) :
                    x_pos(x_pos), y_pos(y_pos), radius(radius), id(id_) {}
    
    float get_x() {
        return x_pos;
    }

    float get_y() {
        return y_pos;
    }

    float get_radius() {
        return radius;
    }
    uint32_t get_id(){
        return this->id;
    }
};

#endif
