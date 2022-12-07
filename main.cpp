#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <exploragram/optimal_transport/optimal_transport_2d.h>
#include <geogram/basic/command_line.h>
#include <geogram/basic/command_line_args.h>

#include "CLI11.hpp"


using namespace std;

int main(int argc, const char** argv) {
    CLI::App app("BNOT sampling");

    string filename;
    app.add_option("-o", filename, "Output file name")->required();
    int N = 8;
    app.add_option("-n", N, "Number of points. (Default=" + to_string(N) +")");
    int seed = 13374269;
    app.add_option("-s", seed, "RNG seed. (Default=" + to_string(seed) + ")");

    CLI11_PARSE(app, argc, argv);

    mt19937_64 rng(seed);
    uniform_real_distribution<double> unif(0, 1);

    vector<double> points(2*N);
    for(double& v : points){
        v = unif(rng);
    }
    for(int i = 0; i < N; ++i){
        cout << points[2*i] << " " << points[2*i + 1] << endl;
    }
    cout << endl;


    GEO::initialize();
    GEO::CmdLine::import_arg_group("standard");
    GEO::CmdLine::import_arg_group("algo");
    GEO::CmdLine::import_arg_group("opt");

    GEO::Mesh mesh(2);
    mesh.vertices.set_dimension(2);
    mesh.vertices.create_vertices(4);
    mesh.vertices.point_ptr(0)[0] = 0.;
    mesh.vertices.point_ptr(0)[1] = 0.;
    mesh.vertices.point_ptr(1)[0] = 1.;
    mesh.vertices.point_ptr(1)[1] = 0.;
    mesh.vertices.point_ptr(2)[0] = 1.;
    mesh.vertices.point_ptr(2)[1] = 1.;
    mesh.vertices.point_ptr(3)[0] = 0.;
    mesh.vertices.point_ptr(3)[1] = 1.;

    std::vector<GEO::index_t> facet = {0u,1u,2u,3u};
    mesh.facets.create_polygon(4, facet.data());

    vector<double> centroids(2*N);
    GEO::compute_Laguerre_centroids_2d(&mesh, N, points.data(), centroids.data());

    for(int i = 0; i < N; ++i){
        cout << centroids[2*i] << " " << centroids[2*i + 1] << endl;
    }

    return 0;
}
