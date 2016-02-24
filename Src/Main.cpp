# include <Siv3D.hpp>

#include "Emitter.h"

Font font;

vector<shared_ptr<const Texture>> textures;

void Main()
{
	Graphics::SetBackground(Color(0, 0, 0));

	font = Font(10);

	textures.push_back(make_shared<const Texture>(L"Assets/Particle.png", TextureDesc::For3D));

	effector::EmitterState estate;
	effector::ParticleState pstate;
	effector::MeshState mstate;

	estate = { effector::EmitterState::EMIT_CENTER };
	pstate = { 0, 1500, 30, 0, 0,{ 0, 0 },{ 1, 1 },{ 0.5, 1, 1 },{ 0.5, 1, 1 }, 0.5, 0, effector::ParticleState::MESH_PARALELLTOVELOCITY };
	mstate = { { 0.2, 1.0 } };
	effector::Emitter flare(estate, pstate, mstate);

	estate = { effector::EmitterState::EMIT_CENTER };
	pstate = { 0, 2000, 10, 0.1, 0.1,{ 0, 0 },{ 1, 1 },{ 0.5, 1, 1 },{ 0.5, 1, 1 }, 1.0, 0, effector::ParticleState::MESH_FACETOCAMERA };
	mstate = { { 0.1, 0.1 } };
	effector::Emitter star(estate, pstate, mstate);

	estate = { effector::EmitterState::EMIT_CIRCLE };
	pstate = { 0, 500, 60, 0, 0,{ 1, 1 },{ 1, 1 },{ 0.5, 1, 1 },{ 0.25, 0.5, 0.5 }, 1.0, 0, effector::ParticleState::MESH_FACETOCAMERA };
	mstate = { { 0.05, 0.05 } };
	effector::Emitter satelite[3] = {
		effector::Emitter(estate, pstate, mstate),
		effector::Emitter(estate, pstate, mstate),
		effector::Emitter(estate, pstate, mstate)
	};

	Graphics3D::SetBlendStateForward(BlendState::Additive);
	Graphics3D::SetDepthStateForward(DepthState::TestOnly);

	while (System::Update())
	{
		Graphics3D::FreeCamera();
		auto& camera = Graphics3D::GetCamera();
		auto targVec = (camera.lookat - camera.pos).normalize() * -1;

		Graphics3D::SetLightForward(0, Light::Directional(targVec));

		font(s3d::Format(camera.pos, camera.up, targVec)).draw(0, 0);
		font(Profiler::FPS()).draw(0, 20);

		flare.update();
		flare.render({  0, 4, -15 });

		star.update();
		star.render({ 0, 4, -15 });

		satelite[0].update();
		satelite[0].render({ 0, 4, -15 });

		satelite[1].update();
		satelite[1].render({ 0, 4, -15 });

		satelite[2].update();
		satelite[2].render({ 0, 4, -15 });
		//emitter.render({  0.5, 4, -15 });
	}
}