#pragma once

# define NO_S3D_USING
# include <Siv3D.hpp>

#include <utility>

namespace effector {
	class EmitPosition {
	public:
		virtual s3d::Vec3 getPos(int elapsed) = 0;
	};

	class EmitCenter : public EmitPosition {
	public:
		EmitCenter();

		s3d::Vec3 getPos(int elapsed);
	};

	class EmitCircleRandom : public EmitPosition {
	public:
		EmitCircleRandom(int c, double rmin, double rmax);

		s3d::Vec3 getPos(int elapsed);
	private:
		int cicle;
		double radius;

		s3d::Quaternion pose;
	};
}