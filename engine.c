#include <tonc.h>

#include "engine.h"

// obj globals
OBJ_ATTR obj_buffer[MAX_OBJS];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;
int active_objs = MIN_OBJS;

void copy_objs() {
	oam_copy(oam_mem, obj_buffer, active_objs);
}

void init_sprites() {
	oam_init(obj_buffer, 128);
}


OBJ_ATTR* new_obj() {
	int i;
	for (i = 0; i < active_objs; i++) {
		if (!OBJ_VISIBLE(obj_buffer[i])) {
			ENGINE_DEBUGFMT("found an empty obj: %d", i);
			return &obj_buffer[i];
		}
	}
	ENGINE_DEBUG("expanding active objs");
	active_objs *= 2;
	if (active_objs > MAX_OBJS) {
		ENGINE_DEBUG("too many objs! resetting");
		swi_call(0x00);
	} else if (OBJ_VISIBLE(obj_buffer[i])) {
		ENGINE_DEBUG("you didn't clean up the objs! resetting");
		swi_call(0x00);
	}
	return &obj_buffer[i];
}

void delete_sprite(sprite_t *s) {
	oam_init(s->obj, 1);
	s->obj = NULL;
	if ((active_objs / 2) < MIN_OBJS) { return; }
	for (int i = active_objs / 2; i < active_objs; i++) {
		if (OBJ_VISIBLE(obj_buffer[i])) {
			return;
		}
	}
	oam_init(&obj_buffer[active_objs / 2], active_objs - (active_objs / 2));
	active_objs /= 2;
}

void place_sprite(sprite_t *s, camera_t *c) {
	bool exist = s->obj != NULL;
	int screen_x = SCREEN_X(*s, *c);
	int screen_y = SCREEN_Y(*s, *c);
	
	ENGINE_DEBUGFMT("sprite in world at %d, %d on screen at %d, %d, exist: %d, height: %d", s->x, s->height, screen_x, screen_y, exist, SPRITE_HEIGHT(*s));
	
	if ((screen_y + SPRITE_HEIGHT(*s) < 0) ||
	    (screen_y > SCREEN_HEIGHT) ||
	    (screen_x + SPRITE_WIDTH(*s) < 0) ||
	    (screen_x > SCREEN_WIDTH)) {
		if (exist) {
			ENGINE_DEBUG("sprite left! deleting it");
			delete_sprite(s);
		}
		return;
	} else {
		if (!exist) {
			ENGINE_DEBUG("sprite on screen and needs to be created");
			s->obj = new_obj();
		}
	}
	obj_set_attr(s->obj,
	             s->shape | ATTR0_REG,
	             s->size,
	             ATTR2_PALBANK(s->palbank) | s->tile);
	obj_set_pos(s->obj, screen_x, screen_y);
}
