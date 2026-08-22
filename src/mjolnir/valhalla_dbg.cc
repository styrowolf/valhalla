#include <iostream>
#include <baldr/graphreader.h>
#include <cxxopts.hpp>
#include <boost/property_tree/ptree.hpp>
#include <filesystem>
#include "rapidjson/document.h"
#include "baldr/rapidjson_utils.h"
#include "tyr/actor.h"
#include "worker.h"
#include <cstdint>

using namespace valhalla::baldr;


int main(int argc, char** argv) {
  std::string config_file_path;
  std::string operation;
  try {
    // clang-format off
    cxxopts::Options options(argv[0],
                             " - Provides utilities for dumping shortcuts.");

    options.add_options()
        ("h,help", "Print this help message.")
        ("c,config", "Path to the json configuration file.",
            cxxopts::value<std::string>(config_file_path));
        ("o,operation", "Operation to perform (e.g., dump_shortcuts).",
            cxxopts::value<std::string>(operation)->default_value(""));
    // clang-format on

    auto cmd_args = options.parse(argc, argv);

    boost::property_tree::ptree pt;
    if (cmd_args.count("config") && std::filesystem::is_regular_file(config_file_path)) {
        rapidjson::read_json(config_file_path, pt);
    } else {
        std::cerr << "Configuration is required" << std::endl;
        return EXIT_FAILURE;
    }

    if (cmd_args.count("help")) {
      std::cout << options.help() << std::endl;
      return EXIT_SUCCESS;
    }

    auto actor = valhalla::tyr::actor_t(pt, true);
    for (std::string line; std::getline(std::cin, line);) {
      valhalla::Api request;
      try {
        auto res = actor.trace_attributes(line, nullptr, &request);
        std::cout << res << '\n';
      } catch (const valhalla::valhalla_exception_t& ve) {
        std::string error = valhalla::serialize_error(ve, request);
        std::cout << error << '\n';
      } catch (const std::exception& e) {
        std::string error = serialize_error({599, std::string(e.what())}, request);
        std::cout << error << '\n';
      } catch (...) {
        std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
        std::cout << error << '\n';
      }
    } 
  } catch (...) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
