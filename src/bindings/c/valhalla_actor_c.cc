#include "tyr/actor.h"
#include "baldr/rapidjson_utils.h"
#include "midgard/logging.h"
#include "midgard/util.h"
#include "worker.h"
#include <string>
#include <cstring>
#include <memory>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <cstdlib>


// configuring multiple times is wasteful/ineffectual but not harmful
// TODO: make this threadsafe just in case its abused
const boost::property_tree::ptree configure(const std::string& config) {
  boost::property_tree::ptree pt;
  try {
    // parse the config and configure logging
    
    // TODO: move file opening etc. to the rust side
    // std::ifstream stream = std::ifstream(config_json);
    // rapidjson::read_json(stream, pt);

    rapidjson::read_json(config, pt);

    auto logging_subtree = pt.get_child_optional("mjolnir.logging");
    if (logging_subtree) {
      auto logging_config = valhalla::midgard::ToMap<const boost::property_tree::ptree&,
                                                     std::unordered_map<std::string, std::string>>(
          logging_subtree.get());
      valhalla::midgard::logging::Configure(logging_config);
    }
  } catch (...) { throw std::runtime_error("Invalid config"); }

  return pt;
}

char* string_to_c_string(const std::string& str) {
  char* cstr = (char*)malloc(str.size() + 1);
  if (cstr) {
    std::memcpy(cstr, str.c_str(), str.size() + 1);
  }
  return cstr;
}

extern "C" {

struct valhalla_actor_c {
  std::unique_ptr<valhalla::tyr::actor_t> actor;
};

valhalla_actor_c* valhalla_actor_create(const char* config, int auto_cleanup) {
  try {
    auto* handle = new valhalla_actor_c;
    handle->actor = std::make_unique<valhalla::tyr::actor_t>(configure(std::string(config)), auto_cleanup != 0);
    return handle;
  } catch (...) {
    return nullptr;
  }
}

void valhalla_actor_destroy(valhalla_actor_c* actor) {
  delete actor;
}

// methods: centroid, expansion, height, isochrone, locate, matrix, optimized_route, route, status, trace_attributes, trace_route, transit_available

char* valhalla_actor_centroid(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->centroid(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_expansion(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->expansion(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_height(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->height(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_isochrone(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->isochrone(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_locate(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->locate(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_matrix(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->matrix(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_optimized_route(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->optimized_route(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_route(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->route(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_status(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->status(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_trace_attributes(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->trace_attributes(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_trace_route(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->trace_route(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

char* valhalla_actor_transit_available(valhalla_actor_c* actor, const char* request_json) {
  if (!actor || !request_json) return nullptr;
  valhalla::Api request;
  try {
    std::string result = actor->actor->transit_available(request_json, nullptr, &request);
    return string_to_c_string(result);
  } catch (const valhalla::valhalla_exception_t& ve) {
    std::string error = valhalla::serialize_error(ve, request);
    return string_to_c_string(error);
  } catch (const std::exception& e) {
    std::string error = serialize_error({599, std::string(e.what())}, request);
    return string_to_c_string(error);
  } catch (...) {
    std::string error = serialize_error({599, std::string("Unknown exception thrown")}, request);
    return string_to_c_string(error);
  }
}

} // extern "C"