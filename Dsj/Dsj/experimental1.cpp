#include <cstdio>
#include "System.h"
#include <sysutil/sysutil_sysparam.h>
#include <cell/sysmodule.h>
#include <sys\process.h>
#include <sys\prx.h>
#include <sys\syscall.h>
#include <sys\vm.h>
#include <sys\dbg.h>
#include <cell/gcm.h>
#include <cell/dbgfont.h> 
#include <memory>
#include "include\odps3lib.h"
#include <sys\synchronization.h>

#define Import using namespace

using namespace System;
using namespace System::Diagnostics;
using namespace System::Text;
using namespace System::Collections;
using namespace System::IO;
using namespace System::Serialization::TOMLANG;

static const Date end_time{ 0, 0, 0, 28, 11, 2024 };

int main2()
{
	using namespace System::Diagnostics;
	using namespace System::Text;
	using namespace System::Collections;
	using namespace System::IO;
	using namespace System::Serialization::TOMLANG;
	byte randomData[2048];
	VariableStorage storage(randomData);
	storage.ReserveType<byte>();		//  sensibility = 80
	storage.ReserveType<bool>();		//  nopresence = false
	storage.ReserveType<bool>();		//  displayposition = false
	storage.ReserveType<bool>();		//  disableparticles = false
	storage.ReserveType<byte>();		//  language = 0
	storage.ReserveType<char*>();		//  custom_resources_path = "default"
	storage.ReserveType<byte>();		// mouse_sensibility = 50
	storage.ReserveType<byte>();		// mouse_tick_rate_pms = 10
	storage.ReserveType<byte>();		// keyboard_tick_rate_pms = 10

	storage.ReserveType<bool>();	//dont_render_fire = false
	storage.ReserveType<bool>();	//disable_ind = false
	storage.ReserveType<bool>();	//render_sky_details = true
	storage.ReserveType<bool>();	//thirdcamera_rot_lock_disabled = true
	storage.ReserveType<bool>();	//render_fog = true
	storage.ReserveType<byte>();	//hand_object_z_axis = 5
	storage.ReserveType<byte>();	//model_render_distance = 90
	storage.ReserveType<byte>();	//third_person_field_of_view = 120
	storage.ReserveType<byte>();	//field_of_view = 80
	storage.ReserveType<bool>();	//hurt_effects = false
	storage.ReserveType<bool>();	//user_interface_sfx_silence = false
	storage.ReserveType<bool>();	//dim_menus = false
	storage.ReserveType<char*>();	//skybox_texture = "skybox.png"
	storage.ReserveType<bool>();	//render_skybox = false
	storage.ReserveType<bool>();	//hud_toggle_feature = false


	storage.ReserveType<bool>();	//zoom_enabled = false
	storage.ReserveType<char*>();	//turn_up = "none"
	storage.ReserveType<char*>();	//turn_back = "none"
	storage.ReserveType<char*>();	//third_person_quick = "none"
	storage.ReserveType<char*>();	//hold_alternative = "none"
	storage.ReserveType<char*>();	//zoom = "none"
	storage.ReserveType<char*>();	//use_alternative = "none"
	storage.ReserveType<char*>();	//peek_back = "none"


	storage.ReserveType<byte>();	//accent_component_r = 128
	storage.ReserveType<byte>();	//accent_component_g = 128
	storage.ReserveType<byte>();	//accent_component_b = 128

	storage.ReserveType<byte>();	//mystical_font = 0
	storage.ReserveType<bool>();	//use_default_resources = false
	storage.ReserveType<bool>();	//prefer_displaying_developer_item_ids = false
	storage.ReserveType<bool>();	//discord_feature = false
	storage.ReserveType<bool>();	//should_output_developer_trace = false

	*(byte*)storage[0] = 80;
	*(bool*)storage[1] = true;
	*(bool*)storage[2] = true;


	Debugger::WriteLine("%i", *(byte*)storage[0]);
	Debugger::WriteLine("%i", *(bool*)storage[1]);
}


int mainDateTime() {

	uint64_t current = System::Marshal::packTuple(28, 10, 24);
	uint64_t date = System::Marshal::packTuple(28, 11, 24);

	double packed = Date::pack(end_time);
	Date unpacked{ Date::unpack(packed) };
	System::Diagnostics::Debugger::WriteLine(
		"Day: %i\n"
		"Month: %i\n"
		"Year: %i\n"
		"Hour: %i\n"
		"Minute: %i\n"
		"Second: %i\n",
		unpacked.day, unpacked.month, unpacked.year, unpacked.hour, unpacked.minute, unpacked.second);
}


int main3() {
	using namespace System::IO;
	using namespace System::Diagnostics;
	FileStream stream;


	char buffer[2048]{ 0 };
	Debugger::WriteLine("(%x)", FileStream::OpenReadWrite(stream, "/dev_hdd0/game/NPUB91431/config.toml"));
	stream.readSequence(0, buffer);
	std::string toml(buffer);

	//Debugger::WriteLine(buffer);

	size_t globalIndex = 0;
	size_t lineStartIndex = 0;
	size_t pos = 0;
	std::string line;
	int entries = 0;

	while ((pos = toml.find('\n')) != std::string::npos) {
		line = toml.substr(0, pos);
		lineStartIndex = globalIndex;

		if (!line.empty()) {
			const char* data = line.c_str();

			int gap = line.find('=');
			if (gap == -1 && line[0] == '[') {

			}
		}

		globalIndex += pos + 1;
		toml.erase(0, pos + 1);
	}
	stream.close();
}

int main() {
	System::IO::FileStream stream;
	HResult result = FileStream::OpenTruncateRw(stream, "/dev_hdd0/tmp/test_toml.txt", 0);
	if (result == 0) {

		StreamWriter writer(stream);
		
	}
	else {
		Debugger::WriteLine("%x", result, 0);
	}
	stream.close();

}