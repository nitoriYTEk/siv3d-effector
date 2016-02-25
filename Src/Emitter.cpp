#include "Emitter.h"
#include "EmitPosition.h"
#include "Particle/Particle.h"

vector<shared_ptr<const s3d::Texture>> textures;

namespace effector {

	void init() {
		textures.push_back(make_shared<const s3d::Texture>(L"Assets/Particle.png", s3d::TextureDesc::For3D));
	}

	Emitter::Emitter(const EmitterState& estate, const ParticleState& pstate, const MeshState& mstate) {
		this->pstate = pstate;
		this->mstate = mstate;

		timer.start();
		lastTime = timer.ms();
		accum = 0;

		switch (estate.emitterType)
		{
		case EmitterState::EMIT_CENTER:
			posGen = make_shared<EmitCenter>();
			break;
		case EmitterState::EMIT_CIRCLE:
			posGen = make_shared<EmitCircleRandom>(5000, 0.08, 0.12);
			break;
		}
	}

	void Emitter::update() {
		int time = timer.ms();
		accum += time - lastTime;
		lastTime = time;

		while (accum >= SEC_COUNT / pstate.ppsec) {
			accum -= SEC_COUNT / pstate.ppsec;
			particles.push_back(make_shared<Particle>(posGen->getPos(time), pstate, mstate));
		}

		particles.remove_if([](shared_ptr<Particle>& p) {
			return p->update();
		});
	}

	void Emitter::render(const s3d::Vec3& pos) {
		for (auto& p : particles) {
			p->render(pos);
		}
	}

}