#include "renderer.h"
namespace pllx {

	Renderer& Renderer::singleton() {
		static Renderer renderer{};
		return renderer;

	}

}