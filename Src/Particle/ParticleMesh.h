#pragma once

# define NO_S3D_USING
# include <Siv3D.hpp>

namespace effector{
	struct MeshState;

	class ParticleMesh {
	public:
		virtual s3d::Plane getMesh() = 0;
	};

	class FaceToCamera : public ParticleMesh {
	public:
		FaceToCamera(const MeshState& state);
		s3d::Plane getMesh();
	private:
		s3d::Vec2 size;
	};

	class ParalellToVelocity : public ParticleMesh {
	public:
		ParalellToVelocity(const MeshState& state, const s3d::Quaternion& pose);
		s3d::Plane getMesh();
	private:
		s3d::Plane origMesh;
	};
}