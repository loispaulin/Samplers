//
// Created by Lois Paulin on 07/12/2022.
//

#include <iostream>
#include <string>
#include <random>
#include <glm/glm.hpp>
#include "CLI11.hpp"

using namespace std;

// Compute the greatest common divisor of two numbers using the Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Check if two numbers are relatively prime
bool areRelativelyPrime(int a, int b) {
    // Two numbers are relatively prime if their greatest common divisor is 1
    return gcd(a, b) == 1;
}

float ToroidalDistance (const glm::vec2& v1, const glm::vec2& v2)
{
    glm::vec2 d = glm::abs(v1 - v2);

    for (int i = 0; i < 2; ++i){
        if (d[i] > 0.5f)
            d[i] = 1.0f - d[i];
    }

    return glm::length(d);
}


int main(int argc, const char** argv){
    CLI::App app("Rank1 generation");

    int nb_pts = 1024;
    app.add_option("-n", nb_pts, "Number of points");
    bool scramble = false;
    app.add_flag("-c", scramble, "Toggle scrambling");
    string filename;
    app.add_option("-o", filename, "Output file name")->required();
    int seed = 13374269;
    app.add_option("-s", seed);

    CLI11_PARSE(app, argc, argv);

    ofstream out(filename);
    if (out.fail()){
        cerr << "Error: Cannot write to file " << filename << endl;
        return -1;
    }

    vector<int> primes;
    for (int i = 1; i < nb_pts; ++i){
        if (areRelativelyPrime(i, nb_pts)){
            primes.push_back(i);
        }
    }
    uniform_int_distribution<int> rand(0, int(primes.size()));
    mt19937_64 gen(seed);
    glm::vec2 offset(0.f, 0.f);
    if (scramble){
        uniform_real_distribution<float> rand_pos(0.f, 1.f);
        offset[0] = rand_pos(gen);
        offset[1] = rand_pos(gen);
    }

    vector<glm::vec2> points(nb_pts);
    float min_dist = 0.f;

    float seuil_dist = 0.02f * sqrt(1024.f) / sqrt(float(nb_pts));
    int nb_tries = 0;
    int step;
    while(min_dist < seuil_dist) {
        step = primes[rand(gen)];
        glm::ivec2 dir(1, step);
        min_dist = 2.f;
        points[0] = glm::vec2(0.f, 0.f);
        for (int i = 1; i < nb_pts; ++i) {
            points[i] = (glm::vec2(i * dir % nb_pts)) / float(nb_pts);
            min_dist = min(min_dist, ToroidalDistance(glm::vec2(0.f, 0.f), points[i]));
        }
        nb_tries += 1;
    }
    cout << nb_tries << " " << min_dist << endl;
    for(const auto& p : points) {
        out << fmod(p[0]+offset[0], 1.) << " " << fmod(p[1]+offset[1], 1.) << endl;
    }

    return 0;
}