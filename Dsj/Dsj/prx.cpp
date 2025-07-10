#include <src\system\core.h>
#include <src\math\ivec.h>
#include <src\debug\log.h>

#include <src\math\rectangle.h>
#include <src\system\formatter.h>


// The Parallax main
int main(int argc, const char** argv)
{
	vec2f myvec;
	myvec.x = 4.0f;
	myvec.y = 4.0f;

	char buffer[128];

	sys::formatter::snprintf_(buffer, 128, "%f, %f", myvec.x, myvec.y);

	if (myvec.x._float() == 4.0f && myvec.y._float() == 4.0f)
		pllx::Logger::getLogger().writeLine("Assertion done.");

	// todo tomrrw: impl buffer builder.
	// mouse pointer...

	pllx::Rectangle rect({ 20, 20 }, { 20, 20 });

	if (rect.Position.x.equals(20.0f) && rect.Position.y.equals(20.0f)) {
		pllx::Logger::getLogger().writeLine("Assertion done.");
	}

	pllx::Logger::getLogger().writeLine(buffer);
	

	return 0;
}