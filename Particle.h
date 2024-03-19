#ifndef PARTICLE_H
#define PARTICLE_H

#include "splashkit.h"
#include <algorithm> // For std::remove_if
#include <vector>

struct Particle {
    point_2d position;
    vector_2d velocity;
    color clr;
    int lifespan;
    int max_lifespan;
    int size;

    Particle(point_2d pos, vector_2d vel, color c, int life, int size);

    void update();
    void draw();
};

void update_particles(std::vector<Particle>& particles);
void draw_particles(std::vector<Particle>& particles);

Particle::Particle(point_2d pos, vector_2d vel, color c, int life, int size = 3)
        : position(pos), velocity(vel), clr(c), lifespan(life), max_lifespan(life), size(size) {}

void Particle::update() {
    position.x += velocity.x;
    position.y += velocity.y;
    velocity.y += 0.04f; // Gravity
    lifespan--;

    // Increase opacity based on the remaining lifespan
    float alpha = 1.0f - (static_cast<float>(lifespan) / static_cast<float>(max_lifespan));
    clr.a = static_cast<uint8_t>(alpha * 255);
}

void Particle::draw() {
    fill_rectangle(clr, position.x, position.y, size, size);
}

void update_particles(std::vector<Particle>& particles) {
    for (auto& p : particles) {
        p.update();
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(),
                                   [](const Particle& p) { return p.lifespan <= 0; }),
                    particles.end());
}

void draw_particles(std::vector<Particle>& particles) {
    for (auto& p : particles) {
        p.draw();
    }
}

#endif // PARTICLE_H
