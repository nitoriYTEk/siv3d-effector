#include "ParticleMesh.h"
#include "MeshState.h"
	
namespace effector {
	ParalellToVelocity::ParalellToVelocity(const MeshState& state, const s3d::Quaternion& pose)
	{
		origMesh = s3d::Plane(state.size.x, state.size.y, pose);
	}

	s3d::Plane ParalellToVelocity::getMesh()
	{
		return origMesh;
	}

	FaceToCamera::FaceToCamera(const MeshState & state)
	{
		size = state.size;
	}

	s3d::Plane FaceToCamera::getMesh()
	{
		auto& camera = s3d::Graphics3D::GetCamera();
		auto targVec = (camera.pos - camera.lookat).normalize();
		return s3d::Plane(size.x, size.y, s3d::Quaternion(targVec.cross({ 0,1,0 }).normalized(), -s3d::Math::Acos(targVec.dot({ 0,1,0 }))));
	}

}