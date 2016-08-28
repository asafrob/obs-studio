#pragma once

#include <obs.h>
#include <util/darray.h>

#ifdef __cplusplus
extern "C" {
#endif

struct config_data;
typedef struct config_data config_t;

struct obs_data;
typedef struct obs_data obs_data_t;

/* ------------------------------------------------------------------------- */

struct obs_frontend_source_list {
	DARRAY(obs_source_t*) sources;
};

static inline void obs_frontend_source_list_free(
		struct obs_frontend_source_list *source_list)
{
	size_t num = source_list->sources.num;
	for (size_t i = 0; i < num; i++)
		obs_source_release(source_list->sources.array[i]);
	da_free(source_list->sources);
}

/* ------------------------------------------------------------------------- */

EXPORT void *obs_frontend_get_main_window(void);
EXPORT void *obs_frontend_get_main_window_handle(void);

EXPORT char **obs_frontend_get_scene_names(void);
EXPORT void obs_frontend_get_scenes(struct obs_frontend_source_list *sources);
EXPORT obs_source_t *obs_frontend_get_current_scene(void);
EXPORT void obs_frontend_set_current_scene(obs_source_t *scene);

EXPORT void obs_frontend_get_transitions(
		struct obs_frontend_source_list *sources);
EXPORT obs_source_t *obs_frontend_get_current_transition(void);
EXPORT void obs_frontend_set_current_transition(obs_source_t *transition);

EXPORT char **obs_frontend_get_scene_collections(void);
EXPORT char *obs_frontend_get_current_scene_collection(void);
EXPORT void obs_frontend_set_current_scene_collection(const char *collection);

EXPORT char **obs_frontend_get_profiles(void);
EXPORT char *obs_frontend_get_current_profile(void);
EXPORT void obs_frontend_set_current_profile(const char *profile);

EXPORT void obs_frontend_start_streaming(void);
EXPORT void obs_frontend_stop_streaming(void);
EXPORT bool obs_frontend_streaming_active(void);

EXPORT void obs_frontend_start_recording(void);
EXPORT void obs_frontend_stop_recording(void);
EXPORT bool obs_frontend_recording_active(void);

typedef void (*obs_frontend_cb)(void *private_data);

EXPORT void *obs_frontend_add_tools_menu_qaction(const char *name);
EXPORT void obs_frontend_add_tools_menu_item(const char *name,
		obs_frontend_cb callback, void *private_data);

enum obs_frontend_event {
	OBS_FRONTEND_EVENT_STREAM_STARTED,
	OBS_FRONTEND_EVENT_STREAM_STOPPING,
	OBS_FRONTEND_EVENT_STREAM_STOPPED,
	OBS_FRONTEND_EVENT_RECORDING_STARTED,
	OBS_FRONTEND_EVENT_RECORDING_STOPPING,
	OBS_FRONTEND_EVENT_RECORDING_STOPPED,
	OBS_FRONTEND_EVENT_SCENE_CHANGED,
	OBS_FRONTEND_EVENT_SCENE_LIST_CHANGED,
	OBS_FRONTEND_EVENT_TRANSITION_CHANGED,
	OBS_FRONTEND_EVENT_TRANSITION_STOPPED,
	OBS_FRONTEND_EVENT_TRANSITION_LIST_CHANGED,
	OBS_FRONTEND_EVENT_SCENE_COLLECTION_CHANGED,
	OBS_FRONTEND_EVENT_SCENE_COLLECTION_LIST_CHANGED,
	OBS_FRONTEND_EVENT_PROFILE_CHANGED,
	OBS_FRONTEND_EVENT_PROFILE_LIST_CHANGED,
	OBS_FRONTEND_EVENT_EXIT
};

typedef void (*obs_frontend_event_cb)(enum obs_frontend_event event,
		void *private_data);

EXPORT void obs_frontend_add_event_callback(obs_frontend_event_cb callback,
		void *private_data);
EXPORT void obs_frontend_remove_event_callback(obs_frontend_event_cb callback,
		void *private_data);

typedef void (*obs_frontend_save_cb)(obs_data_t *save_data, bool saving,
		void *private_data);

EXPORT void obs_frontend_save(void);
EXPORT void obs_frontend_add_save_callback(obs_frontend_save_cb callback,
		void *private_data);
EXPORT void obs_frontend_remove_save_callback(obs_frontend_save_cb callback,
		void *private_data);

EXPORT obs_output_t *obs_frontend_get_streaming_output(void);
EXPORT obs_output_t *obs_frontend_get_recording_output(void);

EXPORT config_t *obs_frontend_get_profile_config(void);
EXPORT config_t *obs_frontend_get_global_config(void);

typedef bool (*obs_frontend_translate_ui_cb)(const char *text,
		const char **out);

EXPORT void obs_frontend_push_ui_translation(
		obs_frontend_translate_ui_cb translate);
EXPORT void obs_frontend_pop_ui_translation(void);

/* ------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif
