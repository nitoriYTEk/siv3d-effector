#pragma once

# define NO_S3D_USING
# include <Siv3D.hpp>

#include <list>
#include <memory>

#include "Particle/ParticleState.h"
#include "Particle/MeshState.h"
#include "EmitterState.h"

const int SEC_COUNT = 1000;

using namespace std;

namespace effector {

	void init();

	class Particle;
	class EmitPosition;

	class Emitter {
	public:
		Emitter(const EmitterState& estate, const ParticleState& pstate, const MeshState& mstate);

		void update();
		void render(const s3d::Vec3& pos);

	private:
		s3d::Stopwatch timer;

		ParticleState pstate;
		MeshState mstate;

		int lastTime;
		int accum;
		list<shared_ptr<Particle>> particles;

		shared_ptr<EmitPosition> posGen;
	};

}