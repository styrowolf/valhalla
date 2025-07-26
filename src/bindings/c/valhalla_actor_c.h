#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct valhalla_actor_c valhalla_actor_c;

/// Create a new Valhalla actor.
/// @param config_json JSON string for the Valhalla config.
/// @param auto_cleanup If nonzero, auto cleanup after each request.
/// @return Pointer to opaque actor handle, or NULL on error.
valhalla_actor_c* valhalla_actor_create(const char* config_json, int auto_cleanup);

/// Destroy the actor and free resources.
void valhalla_actor_destroy(valhalla_actor_c* actor);

/// Call the route method; returns newly allocated string (must be freed by caller).
/// @param actor Actor handle.
/// @param request_json JSON string for the route request.
/// @return Result string (JSON format) or NULL on error.
char* valhalla_actor_route(valhalla_actor_c* actor, const char* request_json);

#ifdef __cplusplus
}
#endif