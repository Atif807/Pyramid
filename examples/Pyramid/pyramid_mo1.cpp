// This library is free and distributed under
// Mozilla Public License Version 2.0.

#include <string>
#include <iostream>
#include <vector>
#include "openGA.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

struct MySolution
{
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

struct MyMiddleCost
{
	// This is where the results of simulation
	// is stored but not yet finalized.
	double cost_A;
	double cost_B;
};

typedef EA::Genetic<MySolution,MyMiddleCost> GA_Type;
typedef EA::GenerationType<MySolution,MyMiddleCost> Generation_Type;

void init_genes(MySolution& p,const std::function<double(void)> &rnd01)
{
	for (int i = 0; i < 10; i++)
			p.x.push_back(5.12 * 2.0 * (rnd01() - 0.5));
}

bool eval_solution(
	const MySolution& p,
	MyMiddleCost &c)
{
	EA::Chronometer timer;
			timer.tic();
		constexpr double pi = 3.141592653589793238;
		c.cost_A = 10 * double(p.x.size());
		for (unsigned long i = 0; i < p.x.size(); i++){
			c.cost_A += p.x[i] * p.x[i] - 10.0 * cos(2.0 * pi * p.x[i]);}
		//std::cout<<"cost A = "<< c.cost_A <<std::endl;
		c.cost_B = timer.toc()*1000000; //timi in milliseconds
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

std::vector<double> calculate_MO_objectives(const GA_Type::thisChromosomeType &X)
{
	return {
		X.middle_costs.cost_A,
		X.middle_costs.cost_B
	};
}

void MO_report_generation(
	int generation_number,
	const EA::GenerationType<MySolution,MyMiddleCost> &last_generation,
	const std::vector<unsigned int>& pareto_front)
{
	(void) last_generation;

	std::cout<<"Generation ["<<generation_number<<"], ";
	std::cout<<"Pareto-Front {";
	for(unsigned int i=0;i<pareto_front.size();i++)
	{
		std::cout<<(i>0?",":"");
		std::cout<<pareto_front[i];
	}
	std::cout<<"}"<<std::endl;
}

void save_results(const GA_Type &ga_obj)
{
	std::ofstream output_file;
	output_file.open("./bin/result_mo1.txt");
	output_file<<"N"<<"\t"<<"Best Genes"<<"\t"<<"cost1"<<"\t"<<"cost2"<<"\n";
	std::vector<unsigned int> paretofront_indices=ga_obj.last_generation.fronts[0];
	for(unsigned int i:paretofront_indices)
	{
		const auto &X=ga_obj.last_generation.chromosomes[i];
		output_file
			<<i<<"\t"
			<<ga_obj.last_generation.chromosomes[i].genes.to_string()<<"\t"
		//	<<X.genes.y<<"\t"
			<<X.middle_costs.cost_A<<"\t"
			<<X.middle_costs.cost_B<<"\n";

	}
	output_file.close();
}

int main()
{
	EA::Chronometer timer;
	timer.tic();

	GA_Type ga_obj;
	ga_obj.problem_mode= EA::GA_MODE::NSGA_III;
	ga_obj.multi_threading=false;
	ga_obj.idle_delay_us=1; // switch between threads quickly
	ga_obj.verbose=false;
	ga_obj.population=1000;
	ga_obj.generation_max=100;
	ga_obj.calculate_MO_objectives= calculate_MO_objectives;
	ga_obj.init_genes=init_genes;
	ga_obj.eval_solution=eval_solution;
	ga_obj.mutate=mutate;
	ga_obj.crossover=crossover;
	ga_obj.MO_report_generation=MO_report_generation;
	ga_obj.crossover_fraction=0.8;
	ga_obj.mutation_rate=0.005;
	ga_obj.solve();

	std::cout<<"The problem is optimized in "<<timer.toc()<<" seconds."<<std::endl;

	save_results(ga_obj);
	return 0;
}
