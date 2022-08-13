#ifndef VOXEL_GENERATE_DISTANCE_NORMALMAP_TASK_H
#define VOXEL_GENERATE_DISTANCE_NORMALMAP_TASK_H

#include "../../util/tasks/threaded_task.h"
#include "../voxel_mesher.h"
#include "distance_normalmaps.h"

namespace zylann::voxel {

// Renders textures providing extra details to far away voxel meshes.
// This is separate from the meshing task because it takes significantly longer to complete. It has different priority
// so most of the time we can get the mesh earlier and affine later with the results.
class GenerateDistanceNormalmapTask : public IThreadedTask {
public:
	// Input

	std::vector<transvoxel::CellInfo> cell_infos;
	// TODO Optimize: perhaps we could find a way to not copy mesh data? The only reason is because Godot wants a
	// slightly different data structure potentially taking unnecessary doubles because it uses `Vector3`...
	std::vector<Vector3f> mesh_vertices;
	std::vector<Vector3f> mesh_normals;
	std::vector<int> mesh_indices;
	Ref<VoxelGenerator> generator;
	std::shared_ptr<VoxelDataLodMap> voxel_data;
	Vector3i origin_in_voxels;
	Vector3i block_size;
	uint8_t tile_resolution;
	uint8_t lod_index;
	bool octahedral_encoding;

	// Output (to be assigned so it can be populated)
	std::shared_ptr<VoxelMesher::VirtualTextureOutput> virtual_textures;

	// Identification
	Vector3i block_position;
	uint32_t volume_id;

	void run(ThreadedTaskContext ctx) override;
	void apply_result() override;
	int get_priority() override;
	bool is_cancelled() override;

private:
};

} // namespace zylann::voxel

#endif // VOXEL_GENERATE_DISTANCE_NORMALMAP_TASK_H