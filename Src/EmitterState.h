#pragma once

# define NO_S3D_USING
# include <Siv3D.hpp>

namespace effector {
	struct EmitterState {
		enum PositionType {
			EMIT_CENTER,
			EMIT_CIRCLE
		}emitterType;
	};
}