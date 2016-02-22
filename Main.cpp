# include <Siv3D.hpp>
#include <vector>
#include <utility>
#include <tuple>

const int SEC_COUNT = 1000;

using namespace std;

class IParticle {
public:
	virtual void render(Stopwatch& timer) = 0;
};

class Flare : public IParticle {
public:
	Flare(int n) : texture(L"Assets/Particle.png", TextureDesc::For3D){
		pnum = n;

		for (int i = 0; i < pnum; i++) {
			particles.push_back(make_pair(Plane(0.2, 1.0, Quaternion::Pitch(Math::Pi / 2) * Quaternion::Roll(Math::Pi * Random())).rollPitchYaw(Quaternion::Yaw(Math::Pi * 2 * Random())).moveBy({ 0, 4, -15 }), i));
		}
	}

	void render(Stopwatch& timer) {
		int count = timer.ms() % SEC_COUNT;

		for (auto& p : particles) {
			int pCount = count + p.second * SEC_COUNT / pnum;
			if (pCount >= SEC_COUNT) {
				if (pCount - SEC_COUNT / pnum < SEC_COUNT) {
					p.first = Plane(0.2, 1.0, Quaternion::Pitch(Math::Pi / 2) * Quaternion::Roll(Math::Pi * Random())).rollPitchYaw(Quaternion::Yaw(Math::Pi * 2 * Random())).moveBy({ 0, 4, -15 });
				}
				pCount -= SEC_COUNT;
			}

			p.first.scaled((double)pCount / SEC_COUNT).drawForward(texture, ColorF(0.5, 1.0, 1.0, 0.5 * (SEC_COUNT - pCount) / SEC_COUNT));
		}
	}

private:
	int pnum;
	vector<pair<Plane, int>> particles;

	Texture texture;
};

void Main()
{
	Graphics::SetBackground(Color(0, 0, 0));

	Font font(10);

	Stopwatch timer;
	timer.start();

	IParticle* flare = new Flare(40);

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

		flare->render(timer);
	}
}