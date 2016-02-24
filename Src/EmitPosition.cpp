#include "EmitPosition.h"

namespace {

	s3d::Vec3 apply(const s3d::Vec3& vec, const s3d::Quaternion& quat) {
		s3d::Mat4x4 mat = quat.toMatrix();
		return s3d::Vec3(
			vec.x * mat.r[0].m128_f32[0] + vec.y * mat.r[1].m128_f32[0] + vec.z * mat.r[2].m128_f32[0] + mat.r[3].m128_f32[0],
			vec.x * mat.r[0].m128_f32[1] + vec.y * mat.r[1].m128_f32[1] + vec.z * mat.r[2].m128_f32[1] + mat.r[3].m128_f32[1],
			vec.x * mat.r[0].m128_f32[2] + vec.y * mat.r[1].m128_f32[2] + vec.z * mat.r[2].m128_f32[2] + mat.r[3].m128_f32[2]
			);
	}

}

namespace effector {
	EmitCenter::EmitCenter()
	{

	}

	s3d::Vec3 EmitCenter::getPos(int elapsed)
	{
		return s3d::Vec3(0, 0, 0);
	}

	EmitCircleRandom::EmitCircleRandom(int c, double rmin, double rmax)
	{
		cicle = c;
		radius = rmin + (rmax - rmin) * s3d::Random();

		pose = s3d::Quaternion::RollPitchYaw(s3d::Math::TwoPi * s3d::Random(), s3d::Math::TwoPi * s3d::Random(), s3d::Math::TwoPi * s3d::Random());
	}

	s3d::Vec3 EmitCircleRandom::getPos(int elapsed)
	{
		double t = (double)(elapsed % cicle )  / cicle;
		return apply(s3d::Vec3(s3d::Math::Cos(s3d::Math::TwoPi * t), s3d::Math::Sin(s3d::Math::TwoPi * t), 0), pose) * radius;
	}
}
