#include "Particle.h"
#include "ParticleMesh.h"
#include "ParticleState.h"

namespace {
	template <typename T> T interpolate(const T& lkey, const T& rkey, double t) {
		return lkey * (1 - t) + rkey * t;
	}

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
	Particle::Particle(const s3d::Vec3& pos, const ParticleState& pstate, const MeshState& mstate) {
		timer.start();

		position = pos;

		pose = s3d::Quaternion::RollPitchYaw(s3d::Math::TwoPi * s3d::Random(), s3d::Math::TwoPi * s3d::Random(), s3d::Math::TwoPi * s3d::Random());
		nVelocity = apply({ 0,0,1 }, pose);


		state = make_shared<ParticleState>(pstate);
		texture = textures[state->texture];

		switch (pstate.meshType)
		{
		case ParticleState::MESH_FACETOCAMERA:
			origMesh = make_shared<FaceToCamera>(mstate);
			break;
		case ParticleState::MESH_PARALELLTOVELOCITY:
			origMesh = make_shared<ParalellToVelocity>(mstate, pose);
			break;
		}
	}
	
	bool Particle::update() {
		int elapsed = timer.ms();
		if (elapsed < state->lifespan) {
			double t = (double)elapsed / state->lifespan;
			s3d::Vec3 v0 = nVelocity * state->beginVelocity;
			s3d::Vec3 v1 = nVelocity * state->endVelocity;
			mesh = origMesh->getMesh().scaled(interpolate(state->beginScale, state->endScale, t)).movedBy(position).movedBy(v0 * t + t * t / 2 * (v1 - v0));
			color = s3d::ColorF(interpolate(state->beginColor, state->endColor, t), interpolate(state->beginAlpha, state->endAlpha, t));
			return false;
		}
		else {
			return true;
		}
	}

	void Particle::render(const s3d::Vec3& pos) const {
		mesh.movedBy(pos).drawForward(*texture, color);
	}
}