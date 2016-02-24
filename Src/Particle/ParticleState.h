#pragma once

# define NO_S3D_USING
# include <Siv3D.hpp>

namespace effector {
	struct ParticleState {
		int texture;
		int lifespan;
		int ppsec;

		double beginVelocity;
		double endVelocity;

		s3d::Vec2 beginScale;
		s3d::Vec2 endScale;

		s3d::Vec3 beginColor;
		s3d::Vec3 endColor;

		double beginAlpha;
		double endAlpha;

		enum MeshType {
			MESH_PARALELLTOVELOCITY,
			MESH_FACETOCAMERA
		} meshType;
	};
}