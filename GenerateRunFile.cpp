#include <iostream>
#include <string>
#include <fstream>

class GenerateRunFile
{

private:
	std::string FG_HOME = "";
	std::string FG_ROOT = "";
	std::string FG_SCENERY = "";
	std::string aircraft_name = "c172p";
	std::string aircraft_path = "";
	std::string distance_unit = "feet";
	std::string angle_unit = "deg";
	std::string airport_id = "";
	std::string runway_id = "";
	bool start_with_pause = false;
	bool fdm_network = false;
	double initial_altitude = 0.0;
	double initial_airspeed = 0.0;
	double initial_heading = 0.0;
	double initial_longitude = 0.0;
	double initial_lattitude = 0.0;
	double offset_distance = 0.0;
	double offset_azimuth = 0.0;
	double max_fps = 15; // default
	std::string run_command = ".\\bin\\fgfs";

public:
	GenerateRunFile(std::string &flightgear_path)
	{
		FG_HOME = flightgear_path;
		FG_ROOT = flightgear_path + "\\data";
		FG_SCENERY = FG_ROOT + "\\Scenery";
	}
	~GenerateRunFile(){};

	void generate()
	{
		std::ofstream bashFileStream;
		bashFileStream.open("flightgear_run.bat", std::ios_base::out | std::ios_base::trunc);
		bashFileStream << "cd " << FG_HOME << "\n"
					   << "SET FG_ROOT=" << FG_ROOT << std::endl;

		// generate the main command here
		if (aircraft_path != "")
			run_command += " --fg-aircraft=" + aircraft_path;
		run_command += " --aircraft=" + aircraft_name;
		if (fdm_network)
			run_command += " --fdm=network,localhost,5501,5502,5503";
		run_command += " --in-air --disable-ai-models --disable-clouds --disable-sound";
		if (start_with_pause)
			run_command += " --enable-freeze";
		if (airport_id != "")
			run_command += " --airport=" + airport_id;
		if (runway_id != "")
			run_command += " --runway=" + runway_id;
		run_command += " --altitude=" + std::to_string(initial_altitude) + " --heading=" + std::to_string(initial_heading);
		if (initial_airspeed != 0.0)
			run_command += " --vc=" + std::to_string(initial_airspeed);
		if (initial_longitude != 0.0)
			run_command += " --lon=" + std::to_string(initial_longitude);
		if (initial_lattitude != 0.0)
			run_command += " --lat=" + std::to_string(initial_lattitude);
		run_command += " --offset-distance=" + std::to_string(offset_distance) + " --offset-azimuth=" + std::to_string(offset_azimuth);

		bashFileStream << run_command << std::endl;

		bashFileStream.close();
	}

	void aircraftName(const std::string &model_name) { this->aircraft_name = model_name; }
	void aircraftDirectory(const std::string &model_path) { this->aircraft_path = model_path; }
	void airportID(const std::string &airport_id) { this->airport_id = airport_id; }
	void runwayID(const std::string &runway_id) { this->runway_id = runway_id; }
	void initialAltitudeFeet(const double &altitude_ft) { this->initial_altitude = altitude_ft; }
	void initialAirspeedKnots(const double &airspeed_kts) { this->initial_airspeed = airspeed_kts; }
	void initialHeadingDeg(const double &heading_deg) { this->initial_heading = heading_deg; }
	void initialLongitudeDeg(const double &lon_deg) { this->initial_longitude = lon_deg; }
	void initialLattitudeDeg(const double &lat_deg) { this->initial_lattitude = lat_deg; }
	void offsetDistnaceNM(const double &offset_distance_nm) { this->offset_distance = offset_distance_nm; }
	void offsetAzimuthDeg(const double &offset_azimuth_deg) { this->offset_azimuth = offset_azimuth_deg; }
	void createFdmNetwork() { this->fdm_network = true; }
	void enableFreeze() { this->start_with_pause = true; }
	void maxFPS(const int &fps_hz) { this->max_fps = fps_hz; }
};

int main(int argc, char *argv[])
{

	std::string flightgear_location = "C:\\Program Files\\FlightGear 2020.3";
	GenerateRunFile fg(flightgear_location);

	std::string aircraft_name = "c172p", airport_id = "KSFO", runway_id = "10L";

	double altitude = atof(argv[1]);
	double heading = atof(argv[2]);

	fg.aircraftName(aircraft_name);
	fg.airportID(airport_id);
	fg.runwayID(runway_id);
	fg.initialAltitudeFeet(altitude);
	fg.initialAirspeedKnots(0.0);
	fg.initialHeadingDeg(heading);
	//fg.initialLattitudeDeg(lat);
	//fg.initialLongitudeDeg(lon);
	fg.offsetDistnaceNM(5.5);
	fg.offsetAzimuthDeg(0.0);
	fg.enableFreeze();
	fg.createFdmNetwork();

	fg.generate();

	system("flightgear_run.bat");

	return 0;
}
