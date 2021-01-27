/*
 * helper.cpp
 *
 *  Created on: 26 Jan 2021
 *      Author: atif
 */




#include <string>
#include <vector>
#include "openGA.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../Pyramid/pyramid.h"


int genome_length;
int file_n;
int total_level;
int level;

void create_folders(int c_level, int t_level){

			std::string str = "mkdir -p Pyramid/Results/L"+std::to_string(t_level)+"/L"+std::to_string(c_level)+"_results";
			const char *dir = str.c_str(); //"mkdir -p tmp/a/b/c";
			int f = system(dir);
			if(f == -1)
			{
				std::cout<<"Error in creating folders"<<std::endl;
			}
}

bool copyFile(const char *SRC, const char* DEST)
{
    std::ifstream src(SRC, std::ios::binary);
    std::ofstream dest(DEST, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}


int P_init = 5000;
int P_final = 200;

int update_pop(int current_l, int total_l){
	int D;
	D = ((P_init - P_final)/(total_l - 1));
	int P_new = (P_init - ((current_l - 1)*D));
	//std::cout<<"pop size = "<<P_new <<std::endl;
	return P_new;
}
int G_init = 3000;
int update_gen(int total_l){
	return (G_init / total_l);

}

struct MySolution {
	std::vector<double> x;

	std::string to_string() const {
		std::ostringstream out;
		out << "{";
		for (unsigned long i = 0; i < x.size(); i++)
			out << (i ? "," : "") << std::setprecision(10) << x[i];
		out << "}";
		return out.str();
	}
};

struct MyMiddleCost {
	// This is where the results of simulation
	// is stored but not yet finalized.
	double cost;
};

typedef EA::Genetic<MySolution, MyMiddleCost> GA_Type;
typedef EA::GenerationType<MySolution, MyMiddleCost> Generation_Type;

void init_genes(MySolution &p, const std::function<double(void)> &rnd01) {
	for (int i = 0; i < 5; i++)
		p.x.push_back(5.12 * 2.0 * (rnd01() - 0.5));
}

bool eval_solution(const MySolution &p, MyMiddleCost &c) {
	//EA::Chronometer timer;
		//timer.tic();
	constexpr double pi = 3.141592653589793238;
	c.cost = 10 * double(p.x.size());
	for (unsigned long i = 0; i < p.x.size(); i++)
		c.cost += p.x[i] * p.x[i] - 10.0 * cos(2.0 * pi * p.x[i]);
	//c.cost = timer.toc();
	//std::cout<<"cost A SO = "<< c.cost <<std::endl;
	return true;
}

MySolution mutate(const MySolution &X_base,
		const std::function<double(void)> &rnd01, double shrink_scale) {
	MySolution X_new;
	bool out_of_range;
	do {
		out_of_range = false;
		X_new = X_base;

		for (unsigned long i = 0; i < X_new.x.size(); i++) {
			double mu = 1.7 * rnd01() * shrink_scale; // mutation radius
			X_new.x[i] += mu * (rnd01() - rnd01());
			if (std::abs(X_new.x[i]) > 5.12)
				out_of_range = true;
		}
	} while (out_of_range);
	return X_new;
}

MySolution crossover(const MySolution &X1, const MySolution &X2,
		const std::function<double(void)> &rnd01) {
	MySolution X_new;
	for (unsigned long i = 0; i < X1.x.size(); i++) {
		double r = rnd01();
		X_new.x.push_back(r * X1.x[i] + (1.0 - r) * X2.x[i]);
	}
	return X_new;
}

double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X) {
	// finalize the cost
	return X.middle_costs.cost;
}

std::ofstream output_file;

void SO_report_generation(int generation_number,
		const EA::GenerationType<MySolution, MyMiddleCost> &last_generation,
		const MySolution &best_genes) {
	/*std::cout << "Generation [" << generation_number << "], " << "Best="
			<< last_generation.best_total_cost << ", " << "Average="
			<< last_generation.average_cost << ", " << "Best genes=("
			<< best_genes.to_string() << ")" << ", " << "Exe_time="
			<< last_generation.exe_time << std::endl;*/

	output_file << generation_number << ", "
			    << last_generation.average_cost << ", "
				<< last_generation.best_total_cost << ", "
	     		<<best_genes.to_string()<<"\n";
			//<< best_genes.x[0] << "\t" << best_genes.x[1] << "\t"
			//<< best_genes.x[2] << "\t" << best_genes.x[3] << "\t"
			//<< best_genes.x[4] << "\t" << "\n";
}


