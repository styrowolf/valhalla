#include <iostream>
#include <baldr/graphreader.h>
#include <cxxopts.hpp>
#include <boost/property_tree/ptree.hpp>
#include <filesystem>
#include "rapidjson/document.h"
#include "baldr/rapidjson_utils.h"

using namespace valhalla::baldr;


int main(int argc, char** argv) {
  // args
  uint64_t way_id;
  float predicted_speed;
  uint32_t live_speed;
  std::string config_file_path;
  try {
    // clang-format off
    cxxopts::Options options(argv[0],
                             " - Provides utilities for dumping shortcuts.");

    options.add_options()
        ("h,help", "Print this help message.")
        ("c,config", "Path to the json configuration file.",
            cxxopts::value<std::string>(config_file_path));
    // clang-format on

    auto cmd_args = options.parse(argc, argv);

    boost::property_tree::ptree pt;
    if (cmd_args.count("config") && std::filesystem::is_regular_file(config_file_path)) {
        rapidjson::read_json(config_file_path, pt);
    } else {
        std::cerr << "Configuration is required" << std::endl;
        return EXIT_FAILURE;
    }

    valhalla::baldr::GraphReader reader(pt.get_child("mjolnir"));
    auto tileset = reader.GetTileSet();
    auto tile_ids = reader.GetTileSet();

    // 2. Iterate through each tile
    for (const auto& tile_id : tile_ids) {
        if (!reader.DoesTileExist(tile_id)) continue;

        auto tile = reader.GetGraphTile(tile_id);
        if (!tile) continue;

        // 3. Iterate through all directed edges in the tile
        uint32_t edge_count = tile->header()->directededgecount();
        for (uint32_t edge_idx = 0; edge_idx < edge_count; ++edge_idx) {
            const DirectedEdge* edge = tile->directededge(edge_idx);
            
            if (edge->is_shortcut()) {
                GraphId shortcut_id = tile_id;
                shortcut_id.set_id(edge_idx);
                auto edges = reader.RecoverShortcut(shortcut_id);
                std::cout << shortcut_id;
                for (const auto& edge_id : edges) {
                    std::cout << "," << edge_id;
                }
                std::cout << std::endl;
            }
        }
  }

  } catch (std::exception& e) {
    std::cerr << "Unable to parse command line options because: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_FAILURE;
}