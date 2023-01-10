#include <forcefield.hpp> // define forcefield parameters
#include <chrono>

// Set key constants
#define R 8.31446261815324e-3 // kJ/mol/K
#define one_over_six 0.166666666666666667

double energy_lj_opt(double &epsilon, double sigma_6, double &inv_distance_6, double &inv_cutoff_6, double &inv_distance_12, double &inv_cutoff_12) {
  return epsilon*sigma_6*( sigma_6 * (inv_distance_12 - inv_cutoff_12) - inv_distance_6 + inv_cutoff_6 );
}

int main(int argc, char* argv[]) {
  // Set up Input Variables
  std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
  if(argc == 2 && strcmp(argv[1], "--help")==0){
    printf("[USAGE] %s STRUCT FFIELD TEMPER MIXING \n", argv[0]);
    printf("Parameters need to be put in this exact order (a parsing tool will be added soon)\n");
    printf("    STRUCT = Path to material cif file (e.g. KAXQIL_clean.cif)\n");
    printf("    FFIELD = Path to Raspa type forcefield file (e.g. forcefield.def)\n");
    printf("    TEMPER = Temperature in K used in the Boltzmann average (e.g. 298.0)\n");
    printf("    ADSORB = Atomic element tag since only works for monoatomic adsorbent now (e.g. Xe)\n");
    printf("    MIXING = If set to MIX it uses Lorentz-Berthelot rules to mix the LJ parameters else it uses self-interaction parameters\n");
    printf("[TEST] %s forcefield/UFF.def 298 Xe MIX > radTable/rad_uff_298K_mix_Xe.rad  \n", argv[0]);
    printf("[TEST] %s forcefield/UFF.def 298 Xe nomix > radTable/rad_uff_298K.rad  \n", argv[0]);
    exit(0);
  }

  std::string forcefield_path = argv[1];
  double temperature = std::stod(argv[2]);
  std::string element_guest_str = argv[3];
  bool mix = false;
  if (argv[4]) {if ( std::string(argv[4])=="MIX") {mix=true;}}
  double surface_limit = 1.5;
  if (argv[5]) {surface_limit = std::stod(argv[5]);}
  double T_limit = surface_limit*temperature;
  double T_limit_inv = 1/T_limit;


  // Read Forcefield Infos
  ForceField::Parameters ff_params;
  if (forcefield_path != "DEFAULT") {
    ff_params.read_lj_from_raspa(forcefield_path);
  }
  vector<vector<double>> FF_parameters;
  if (mix) {FF_parameters = ff_params.generate_cross_parameters(element_guest_str);}
  double epsilon=0, sigma=0;
  for (int atom_number=1; atom_number<ff_params.N_host-1; atom_number++){
    if (mix) {
      epsilon = FF_parameters[atom_number][0];
      sigma = FF_parameters[atom_number][1];
    }
    else {
      epsilon = ff_params.host_epsilons[atom_number];
      sigma = ff_params.host_sigmas[atom_number];
    }
    double energy_ratio = epsilon*T_limit_inv;
    double Q = energy_ratio*(std::sqrt(1 + (4/energy_ratio))-2);
    double new_radius = 0.5*sigma*std::pow(Q,one_over_six);
    gemmi::Element el_host(atom_number);
    if (new_radius == new_radius) {
      std::cout << el_host.name() << " " << new_radius << std::endl;
    }
    else {
      
    }
  }
  // Adsorption infos from forcefield dictionary
  // double sigma_guest = ff_params.get_sigma(element_guest_str, true);
}
