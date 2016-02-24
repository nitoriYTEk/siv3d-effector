#pragma once

# define NO_S3D_USING
# include <Siv3D.hpp>

#include <vector>
#include <memory>

using namespace std;

extern vector<shared_ptr<const s3d::Texture>> textures;

namespace effector {

	struct ParticleState;
	struct MeshState;
	class ParticleMesh;

	class Particle {
	public:
		Particle(const s3d::Vec3& pos, const ParticleState& state, const MeshState& mstate);

		bool update();
		void render(const s3d::Vec3& pos) const;
	protected:
		s3d::Stopwatch timer;
		shared_ptr<const s3d::Texture> texture;

		s3d::Vec3 position;
		s3d::Vec3 nVelocity;
		s3d::Quaternion pose;

		shared_ptr<ParticleState> state;
		shared_ptr<ParticleMesh> origMesh;

		s3d::Plane mesh;
		s3d::ColorF color;
	};
}
