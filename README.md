# Purpose of the code

A small python to generate an input for  Zeo++ to change the radii of the zeo++ software. It is based on the distance where the interatomic potential energy is $1.5 k_BT$ which has been tested to be relevant for diffusion purposes in this publication: <https://pubs.acs.org/doi/full/10.1021/acs.jpcc.1c05959>. 

# INPUTs

The **temperature** to determine the radius according to the $1.5 k_BT$ energy threshold given by the above-mentioned article.

The interatomic potential is modeled by a Lennard-Jones potential described using the Raspa2 self-interaction potential parameters **forcefield file** given in the ```force_field_mixing_rules.def```. For instance, the plain UFF forcefield, the Dreiding+UFF forcefield (the Dreiding forcefield is specifically adapted for organic matters like in MOFs) and a zeolite universal forcefield taken from (Vujic_2016: <https://iopscience.iop.org/article/10.1088/0965-0393/24/4/045002>).

The eventual **adsorbate element symbol** in case of a mixing rule applied to calculate the LJ parameters.

# Output

Generate a radius file for Zeo++ read by the ```readRadTable``` function of ```networkinfo.cc``` in Zeo++.
The radius file consists in a two column data file sperated by spaces with the element symbol followed by the radius value. Example in radTable or Hung_2021