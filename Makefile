# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 18:38:23 by motero            #+#    #+#              #
#    Updated: 2024/02/28 00:41:49 by olimarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

#=============================================================================#
#                                 HEADERS                                     #
#=============================================================================#

LIBS_DIR = libs/

HDR_NAME = cub3D.h parsing.h structures.h colors.h mlx_engine.h settings.h
HDR_DIR = includes/
HDRS = $(addprefix $(HDR_DIR), $(HDR_NAME))
HDR_INC = -I includes

#================================================================flx=============#
#                                 LIBRARIES                                     #
#=============================================================================#

LIBFT_DIR = $(LIBS_DIR)libft/
LIBFT_HDIR = $(LIBFT_DIR)includes/
LIBFT_HDIR_INC = -I $(LIBFT_HDIR)
LIB_BINARY = -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_HDIR)/libft.a
HDR_INC += $(LIBFT_HDIR_INC)

#=============================================================================#
#                                 MiniLIBX                                    #
#=============================================================================#

MINILIBX_HDIR = $(LIBS_DIR)minilibx-linux/
MINILIBX_HDIR_INC = -I $(MINILIBX_HDIR)
MINILIBX_BINARY = -Lmlx_linux -lmlx_Linux -L$(MINILIBX_HDIR) -Imlx_linux -lXext -lX11 -lm -lz
MINILIBX = $(MINILIBX_HDIR)libmlx.a
HDR_INC += $(MINILIBX_HDIR_INC)


#=============================================================================#
#                               SOURCES                                       #
#=============================================================================#

SRCS_DIR_project = sources/

SRCS_RAW_NAME_DIRECTORIES = sources/assets/ \
sources/bsp_builder/ \
sources/bsp_builder/bsp/ \
sources/bsp_builder/bsp_segments/ \
sources/bsp_builder/map_cut/ \
sources/bsp_builder/portals/ \
sources/canvas/ \
sources/canvas/canvas_hooks/ \
sources/canvas/matrix_abstractions/ \
sources/canvas/specialized_canvas/ \
sources/canvas/specialized_canvas/Button/ \
sources/canvas/specialized_canvas/Game/ \
sources/canvas/specialized_canvas/UI/ \
sources/canvas/specialized_canvas/map_editor/ \
sources/canvas/specialized_canvas/map_editor/map_editor_events/ \
sources/colors/ \
sources/draw_utils/ \
sources/game/ \
sources/game/djiskra/ \
sources/game/entity/ \
sources/game/entity/default/ \
sources/game/entity/monsters/ \
sources/game/entity/monsters/penguin/ \
sources/game/entity/player/ \
sources/game/entity/torch/ \
sources/game/entity/torch/logic/ \
sources/game/init/ \
sources/game/init/precalculations/ \
sources/game/init/precalculations/sector/ \
sources/game/init/precalculations/segment/ \
sources/game/logic/ \
sources/game/logic/camera/ \
sources/game/physics/ \
sources/game/physics/collision/ \
sources/game/physics/collision/corrections/ \
sources/game/raycasting/ \
sources/game/render/ \
sources/game/render/billboard/ \
sources/game/render/lights/ \
sources/game/render/post_processing/ \
sources/game/render/post_processing/shaders/ \
sources/game/render/post_processing/shaders/deffered_shadowing/ \
sources/game/render/post_processing/shaders/displacements_effects/ \
sources/game/render/render3d/ \
sources/game/render/render3d/drawing/ \
sources/game/render/render3d/drawing/portals/ \
sources/game/render/render3d/drawing/texture_mapping/ \
sources/game/render/render3d/drawing/wall/ \
sources/game/render/render3d/utils/ \
sources/map_to_edges/ \
sources/math_utils/ \
sources/matrix/ \
sources/mlx_engine/ \
sources/mlx_hooks/ \
sources/parsing/ \
sources/structures_utils/ \
sources/structures_utils/circular_queue/ \
sources/structures_utils/list_utils/ \
sources/structures_utils/segments_utils/ \
sources/structures_utils/tree/ \
sources/structures_utils/color_utils/ \
sources/structures_utils/dynamic_array/ \
sources/structures_utils/sparse_array/ \
sources/error/ \
sources/ressources/ \
sources/ressources/textures/ \
sources/ressources/textures/texture_manager/ \
sources/ressources/textures/textures/

SRCS_NAME_DIRECTORIES = $(patsubst sources/%,%,$(SRCS_RAW_NAME_DIRECTORIES))

SRCS_RAW_ALL = sources/assets/assets_loading.c \
sources/bsp_builder/bsp/separator.c \
sources/bsp_builder/bsp/segments_utils.c \
sources/bsp_builder/bsp_segments/bsp_segments.c \
sources/bsp_builder/bsp_segments/bsp_segments_nodes.c \
sources/bsp_builder/bsp_segments/bsp_segments_tree.c \
sources/bsp_builder/lst_array_container.c \
sources/bsp_builder/map_cut/map_cut.c \
sources/bsp_builder/map_cut/segment_cutter.c \
sources/bsp_builder/map_cut/map_cut_utils.c \
sources/bsp_builder/portals/portals.c \
sources/bsp_builder/portals/portal_utils.c \
sources/bsp_builder/bsp.c \
sources/canvas/canvas_hooks/canvas_events.c \
sources/canvas/canvas_management.c \
sources/canvas/canvas_operations.c \
sources/canvas/canvas_valid_types.c \
sources/canvas/initialize_canvas_setups.c \
sources/canvas/initialize_canvas_setups2.c \
sources/canvas/matrix_abstractions/add_matrix_to_canvas.c \
sources/canvas/merge_canvas.c \
sources/canvas/multi_buffering_canvas.c \
sources/canvas/specialized_canvas/Button/button_buttonpress.c \
sources/canvas/specialized_canvas/Button/button_events.c \
sources/canvas/specialized_canvas/Button/button_keypressing.c \
sources/canvas/specialized_canvas/Button/button_mousemotion.c \
sources/canvas/specialized_canvas/Button/button_render.c \
sources/canvas/specialized_canvas/Game/game_events.c \
sources/canvas/specialized_canvas/Game/game_keypressing.c \
sources/canvas/specialized_canvas/Game/game_mousemotion.c \
sources/canvas/specialized_canvas/Game/game_render.c \
sources/canvas/specialized_canvas/Game/game_buttonpress.c \
sources/canvas/specialized_canvas/UI/ui_buttonpress.c \
sources/canvas/specialized_canvas/UI/ui_events.c \
sources/canvas/specialized_canvas/UI/ui_keypressing.c \
sources/canvas/specialized_canvas/UI/ui_mousemotion.c \
sources/canvas/specialized_canvas/UI/ui_render.c \
sources/canvas/specialized_canvas/free_specialized_canvas.c \
sources/canvas/specialized_canvas/init_specialized_intermediary_canvas.c \
sources/canvas/specialized_canvas/map_editor/map_editor_events/map_editor_events.c \
sources/canvas/specialized_canvas/map_editor/map_editor_events/map_editor_keypressing.c \
sources/canvas/specialized_canvas/map_editor/map_editor_events/map_editor_mousemotion.c \
sources/canvas/specialized_canvas/map_editor/map_editor_events/map_editor_buttonpress.c \
sources/canvas/specialized_canvas/map_editor/map_editor_events/map_editor_render.c \
sources/canvas/specialized_canvas/init_specialized_canvas_basic.c \
sources/canvas/specialized_canvas/init_specialized_final_canvas.c \
sources/canvas/canvas_member_functions.c \
sources/canvas/draw_canvas_operation.c \
sources/canvas/reorder_canvas.c \
sources/colors/colors_main.c \
sources/draw_utils/alignment_methods.c \
sources/draw_utils/draw_canvas_operation.c \
sources/draw_utils/draw_line.c \
sources/draw_utils/draw_map_basics.c \
sources/draw_utils/draw_on_mlx.c \
sources/draw_utils/draw_shapes.c \
sources/draw_utils/draw_map_to_mlx.c \
sources/draw_utils/draw_utils.c \
sources/draw_utils/layers_manager.c \
sources/draw_utils/initialize_canvas_list.c \
sources/game/entity/default/entity_default.c \
sources/game/entity/entities_manager.c \
sources/game/entity/monsters/penguin/entity_penguin.c \
sources/game/entity/monsters/penguin/entity_penguin_draw.c \
sources/game/entity/monsters/penguin/entity_penguin_logic.c \
sources/game/entity/player/entity_player.c \
sources/game/entity/player/entity_player_logic.c \
sources/game/entity/torch/entity_torch.c \
sources/game/entity/torch/logic/entity_torch_logic.c \
sources/game/fps_counter.c \
sources/game/game_destroy.c \
sources/game/game_init.c \
sources/game/game_loop.c \
sources/game/init/game_precalculations.c \
sources/game/init/precalculations/sector/compute_sector_center.c \
sources/game/init/precalculations/sector/compute_sector_floor_ceiling.c \
sources/game/init/precalculations/segment/compute_segment_floor_ceil.c \
sources/game/init/precalculations/segment/compute_segment_normal.c \
sources/game/init/precalculations/segment/compute_segment_orientation.c \
sources/game/init/precalculations/segment/compute_segment_oriented_textures.c \
sources/game/init/precalculations/segment/compute_segment_size.c \
sources/game/logic/camera/game_camera.c \
sources/game/logic/camera/game_sector_edit_height.c \
sources/game/physics/apply_physics.c \
sources/game/physics/collision/collision_cylinder.c \
sources/game/physics/collision/corrections/collison_correction_sliding.c \
sources/game/physics/collision/intersection_segment_circle.c \
sources/game/raycasting/raycaster.c \
sources/game/raycasting/raycaster_utils.c \
sources/game/raycasting/raycasting_launch_ray.c \
sources/game/render/billboard/draw_billboard.c \
sources/game/render/billboard/draw_transparent_surface.c \
sources/game/render/game_render.c \
sources/game/render/lights/compute_lights_visibility.c \
sources/game/render/lights/light_destroy.c \
sources/game/render/lights/lights_init.c \
sources/game/render/post_processing/shaders/deffered_shadowing/calc_light_cone.c \
sources/game/render/post_processing/shaders/deffered_shadowing/calc_light_distance_attenuation.c \
sources/game/render/post_processing/shaders/deffered_shadowing/calc_light_intensity.c \
sources/game/render/post_processing/shaders/deffered_shadowing/calc_light_normal_diffuse.c \
sources/game/render/post_processing/shaders/displacements_effects/displacement_tilt.c \
sources/game/render/post_processing/shaders/displacements_effects/displacement_wave_effect.c \
sources/game/render/post_processing/shaders/shader_camera_displacement.c \
sources/game/render/post_processing/shaders/shader_deffered_shadowing.c \
sources/game/render/post_processing/shaders/shader_lens_flare.c \
sources/game/render/post_processing/shaders/shader_normal_view.c \
sources/game/render/post_processing/shaders/shader_posterization.c \
sources/game/render/post_processing/game_post_processing.c \
sources/game/render/render3d/drawing/portals/portals_offsets.c \
sources/game/render/render3d/drawing/portals/render_portal.c \
sources/game/render/render3d/drawing/texture_mapping/draw_textured_surface.c \
sources/game/render/render3d/drawing/texture_mapping/texture_mapping_utils.c \
sources/game/render/render3d/drawing/wall/render_wall.c \
sources/game/render/render3d/render3d_destroy.c \
sources/game/render/render3d/render3d_draw.c \
sources/game/render/render3d/render3d_flush.c \
sources/game/render/render3d/render3d_init.c \
sources/game/render/render3d/utils/bsp.c \
sources/game/render/render3d/utils/clipping.c \
sources/game/render/render3d/utils/projections.c \
sources/game/render/render3d/utils/transform_camera_relative.c \
sources/map_to_edges/extract_edges.c \
sources/map_to_edges/identify_diagonals.c \
sources/map_to_edges/utilities_for_extraction.c \
sources/map_to_edges/process_map.c \
sources/math_utils/segments_intersection.c \
sources/math_utils/lerp.c \
sources/math_utils/point_partitioning.c \
sources/math_utils/random.c \
sources/matrix/points_transformations.c \
sources/matrix/matrix_operations.c \
sources/matrix/matrix_transformations.c \
sources/matrix/point_vec_conversions.c \
sources/matrix/vector_matrix_conversions.c \
sources/mlx_engine/mlx_init.c \
sources/mlx_hooks/boutonpress_events.c \
sources/mlx_hooks/general_events.c \
sources/mlx_hooks/keypress_events.c \
sources/mlx_hooks/mlx_hooks.c \
sources/mlx_hooks/mousemotion_events.c \
sources/parsing/check_color_range.c \
sources/parsing/check_map.c \
sources/parsing/check_valid_file.c \
sources/parsing/free_parsing_text.c \
sources/parsing/main_parsing.c \
sources/parsing/parsing_colors.c \
sources/parsing/parsing_text.c \
sources/parsing/parsing_textures.c \
sources/parsing/store_into_data_struct.c \
sources/parsing/transform_map_for_flood.c \
sources/parsing/transform_map_for_flood_utils.c \
sources/parsing/valid_colors.c \
sources/parsing/validate_textures.c \
sources/parsing/verif_wall_player.c \
sources/parsing/initialize_player.c \
sources/parsing/parse_map.c \
sources/structures_utils/circular_queue/circular_queue.c \
sources/structures_utils/list_utils/additional_fonctions.c \
sources/structures_utils/segments_utils/segment_tree_utils.c \
sources/structures_utils/segments_utils/segment_list_utils.c \
sources/structures_utils/segments_utils/segment_math_utils.c \
sources/structures_utils/tree/tree.c \
sources/structures_utils/color_utils/color_math.c \
sources/structures_utils/dynamic_array/dynamic_array_add.c \
sources/structures_utils/dynamic_array/dynamic_array_destroy.c \
sources/structures_utils/dynamic_array/dynamic_array_get.c \
sources/structures_utils/dynamic_array/dynamic_array_growth.c \
sources/structures_utils/dynamic_array/dynamic_array_init.c \
sources/structures_utils/dynamic_array/dynamic_array_new_element.c \
sources/structures_utils/dynamic_array/dynamic_array_remove.c \
sources/structures_utils/sparse_array/sparse_array_add.c \
sources/structures_utils/sparse_array/sparse_array_destroy.c \
sources/structures_utils/sparse_array/sparse_array_get.c \
sources/structures_utils/sparse_array/sparse_array_growth.c \
sources/structures_utils/sparse_array/sparse_array_init.c \
sources/structures_utils/sparse_array/sparse_array_remove.c \
sources/structures_utils/sparse_array/sparse_array_remove_all.c \
sources/error/fatal_error.c \
sources/main.c \
sources/ressources/textures/texture_manager/texture_manager_destroy.c \
sources/ressources/textures/texture_manager/texture_manager_init.c \
sources/ressources/textures/texture_manager/texture_manager_update.c \
sources/ressources/textures/textures/texture_destroy.c \
sources/ressources/textures/textures/texture_get_frame.c \
sources/ressources/textures/textures/texture_init.c \
sources/ressources/textures/textures/texture_update.c \
sources/ressources/textures/textures/textures_set.c

SRCS_ALL = $(patsubst sources/%,%,$(SRCS_RAW_ALL))

SRCS_NAME_project = $(SRCS_ALL)

SRCS_PROJECT = $(addprefix $(SRCS_DIR_project), $(SRCS_NAME_project))

#=============================================================================#
#                             		GNL                                       #
#=============================================================================#

GNL_DIR = $(LIBS_DIR)gnl/
GNL_HDIR = $(GNL_DIR)
GNL_HDIR_INC = -I $(GNL_HDIR)
GNL_NAME = get_next_line.c \
			get_next_line_utils.c
GNL = $(addprefix $(GNL_DIR), $(GNL_NAME))
GNL_OBJ = $(GNL:.c=.o)
HDR_INC += $(GNL_HDIR_INC)



#=============================================================================#
#                                OBJECTS                                      #
#=============================================================================#

OBJS_PATH = objs/
OBJS_NAME = $(SRCS_NAME_project:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

#=============================================================================#
#                          COMPILATOR & FLAGS                                 #
#=============================================================================#

CC = cc
CFLAGS = -Wall -Wextra -flto
LIBA = ar rc
LIBS = ranlib

ifneq ($(no_error), true)
	CFLAGS += -Werror
endif

ifeq ($(fast), true)
	CFLAGS += -Ofast
endif

ifeq ($(little_endian), true)
	CFLAGS += -D LITTLE_ENDIAN
endif


RM = rm -Rf

#=============================================================================#
#                                 Profiler                                    #
#=============================================================================#

PROFILE = project_prof

OBJS_PATH_PROFILER = objs_prof/
OBJS_NAME_PROFILER = $(SRCS_NAME_project:.c=.o)
OBJS_PROFILER = $(addprefix $(OBJS_PATH_PROFILER), $(OBJS_NAME_PROFILER))

PROFILER_FLAG = -pg

#=============================================================================#
#                                 Fsanitize                                    #
#=============================================================================#

SANITIZE = project_sanitize

OBJS_PATH_SANITIZE = objs_sanitize/
OBJS_NAME_SANITIZE = $(SRCS_NAME_project:.c=.o)
OBJS_SANITIZE = $(addprefix $(OBJS_PATH_SANITIZE), $(OBJS_NAME_SANITIZE))

SANITIZE_FLAG = -g3 -fsanitize=address -fno-omit-frame-pointer

#=============================================================================#
#                                 Valgrind                                    #
#=============================================================================#

VALGND = project_valgrind

OBJS_PATH_VALGND = objs_valgrind/
OBJS_NAME_VALGND = $(SRCS_NAME_project:.c=.o)
OBJS_VALGND = $(addprefix $(OBJS_PATH_VALGND), $(OBJS_NAME_VALGND))

VALGND_FLAG = -g3

#=============================================================================#
#                                 Callgrind                                    #
#=============================================================================#

CALLGND = project_callgrind

OBJS_PATH_CALLGND = objyRatio
OBJS_PATH_GDB = objs_gdb/
OBJS_NAME_GDB = $(SRCS_NAME_project:.c=.o)
OBJS_GDB = $(addprefix $(OBJS_PATH_GDB), $(OBJS_NAME_GDB))

GDB_FLAG = -g

#=============================================================================#
#                                COLOURS                                      #
#=============================================================================#

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NONE = \033[0m

bold := $(shell tput bold)
normal := $(shell tput sgr0)

#=============================================================================#
#                                RULES                                        #
#=============================================================================#

bonus : all

all: check_libft check_mlx project ${NAME} ${HDRS}
		@echo "\n $(GREEN) $(bold) \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/"
		@echo "\t \t[ $(GREEN)✔$(NONE)] $(bold)Project is ready [ $(GREEN)✔$(NONE)]"
		@echo "$(GREEN) $(bold) /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ \n"

check_libft:
		@echo "\n[ $(BLUE)$(bold)CHECKING LIBFT$(NONE)]"
		@echo "============================================="
		@make -sC $(LIBFT_DIR)

check_mlx:
		@echo "\n[ $(BLUE)$(bold)CHECKING MINILIBX$(NONE)]"
		@echo "============================================="
		@make -sC $(MINILIBX_HDIR)

project:
		@echo "\n == $(bold)$(YELLOW)CHECKING PROJECT$(normal)=="
		@echo "==============================================="

run:
	make
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./$(NAME)

$(OBJS_PATH):
		@mkdir -p $(addprefix $(OBJS_PATH), $(SRCS_NAME_DIRECTORIES))
		@echo "\t [ $(GREEN)✔$(NONE)] $@directories"

$(OBJS_PATH)%.o: $(SRCS_DIR_project)%.c $(HDRS)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(HDR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project"

$(NAME): $(GNL_OBJ) $(OBJS_PATH) $(OBJS) $(HDRS)
		@echo $(SRCS_ALL)
		@$(CC) $(CFLAGS) $(GNL_OBJ) $(OBJS) $(LIB_BINARY) $(MINILIBX_BINARY) $(HDR_INC) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project"

malloc_test: $(OBJS_PATH) ${GNL_OBJ} $(OBJS)
		@make -C libft
		$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} ${GNL_OBJ} $(LIB_BINARY) -L. -lmallocator

#=============================================================================#
#                                RULES   PROFILER                             #
#=============================================================================#

#To xecute as follows :make sanitizer var="1 2 3"

prof: fclean check_libft project ${PROFILE} ${HDRS} run_prof execute_profiler

execute_profiler :
		@gprof -b ${PROFILE} gmon.out > analysis.txt
		@echo "\t[ $(GREEN) Profling done!$(NONE) ]"
		@echo "========================================"
		@cat analysis.txt

run_prof: project_prof
	@echo "\n[ $(BLUE)$(bold)Executing binary$(NONE) ]"
	./project_prof $(var)

$(OBJS_PATH_PROFILER):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_PROFILER)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(PROFILER_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_prof"

$(PROFILE) : $(OBJS_PATH_PROFILER) $(OBJS_PROFILER) $(LIBFT) $(HDRS)
		@echo " \n[$(bold)$(YELLOW) PROFILER COMPILATION $(NONE)]"
		$(CC) $(CFLAGS) $(PROFILER_FLAG) $(OBJS_PROFILER) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_prof"

#=============================================================================#
#                                RULES   SANITIZER                            #
#=============================================================================#

#to launch as folows  : make sanitizer var="1 2 3"
sanitizer: fclean check_libft project ${SANITIZE} ${HDRS} run_san

run_san: project_sanitize
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"		@echo "\t [ $(GREEN)✔$(NONE)] $@directories"
$(SANITIZE) : $(OBJS_PATH_SANITIZE) $(OBJS_SANITIZE) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)FSANITIZE COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(SANITIZE_FLAG) $(OBJS_SANITIZE) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_sanitize"

#make run_sanitize with good run

#=============================================================================#
#                                RULES  VALGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
valgnd: fclean check_libft project ${VALGND} ${HDRS} run_valgnd

run_valgnd: project_valgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with valgrind$(NONE)]\n"
	@valgrind ./project_valgrind $(var)

$(OBJS_PATH_VALGND):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_VALGND)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_valgrind"

$(VALGND) : $(OBJS_PATH_VALGND) $(OBJS_VALGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)VALGND COMPILATION"
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(OBJS_VALGND) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_valgrind"


#=============================================================================#
#                                RULES  CALLLGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
callgnd: fclean check_libft project ${VALGND} ${HDRS} run_callgnd

run_callgnd: project_callgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with callgrind$(NONE)]\n"
	@valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes  ./project_callgrind $(var)
	@kcachegrind callgrind.out.*

$(OBJS_PATH_CALLGND):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_CALLGND)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_callgrind"

$(CALLGND) : $(OBJS_PATH_CALLGND) $(OBJS_CALLGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)CALLGND COMPILATION]"
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(LIB_BINARY) $(OBJS_CALLGND) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_callgrind"

#=============================================================================#
#                                RULES   GDB                                  #
#=============================================================================#

#to launch as folows  : make BDG
bdg: fclean check_libft project ${BDG} ${HDRS} run_bdg

run_bdg: project_gdb
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"
	gdb project_gdb $(var)

$(OBJS_PATH_GDB):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_GDB)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_gdb"

$(BDG) : $(OBJS_PATH_GDB) $(OBJS_GDB) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)BDG COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(OBJS_GDB) $(LIB_BINARY)  -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_gdb"

#=============================================================================#
#                                COMMANDS                                     #
#=============================================================================#

clean:
		@echo "[ $(RED)$(bold)STARTING CLEAN$(NONE) ]"
		@echo "==================================="
		@${RM} $(OBJS_PATH) $(OBJS_PATH_PROFILER) $(OBJS_PATH_SANITIZE) $(OBJS_PATH_VALGND) $(OBJS_CALLGND) $(OBJS_PATH_GDB) $(GNL_OBJ)
		@rm -rf analysis.txt gmon.out callgrind.out.* ${PROFILE}
		@echo "\t[ $(RED)✗$(NONE) ] $(OBJ_DIR) directory"
		@make -sC $(LIBFT_DIR) clean

fclean: clean
		@rm -f ${NAME} ${PROFILE} ${SANITIZE} ${VALGND} ${CALLGND} ${BDG}
		@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
		@make -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
