// This library is free and distributed under
// Mozilla Public License Version 2.0.

#include <string>
#include <iostream>
#include <vector>
#include "openGA.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

int genome_len;
int file_n;
int total_level;
int level;

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

int a=0;
void read_L1_ind(MySolution& p)
{
          std::ifstream inFile;
          std::string s;
          std::vector< double > vd;
          double d = 0.0;
          int file_num = file_n;

          std::string file;
         file = std::to_string(file_num);
         std::string t_level;
         t_level = std::to_string(total_level);
         //std::cout << "total level "<< t_level <<std::endl;
         int previous_l = level-1;
         std::string pre;
         pre = std::to_string(previous_l);
         //std::cout<<"previous "<<previous_l <<std::endl;
         std::string file_name = "Pyramid/mo/L"+t_level+"/L"+pre+"_final/"+file+"_promoted_ind.txt";
         //std::cout<<file_name <<std::endl;
    inFile.open(file_name);
    if (!inFile) {
            std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

for (int lineno = 0; getline (inFile,s) && lineno < 1000; lineno++)
{      //std::cout<< "inside loop "<<a<<std::endl;
        if (lineno == a)
        {// std::cout << s << std::endl;
                //std::cout<< "inside if "<<a<<std::endl;
    std::size_t pos = 0;
    std::size_t pos1 = 0;
    std::size_t pos2 = 0;
    //std::vector< double > vd;
    //double d = 0.0;
    while (pos < s.size())
    {   if ((pos = s.find_first_of (',',pos)) != std::string::npos)
            s[pos] = ' ';}
    while (pos1 < s.size())
        { if ((pos1 = s.find_first_of ('{',pos1)) != std::string::npos)
            s[pos1] = ' ';}
   while (pos2 < s.size())
        { if ((pos2 = s.find_first_of ('}',pos2)) != std::string::npos)
            s[pos2] = ' ';}

            std::stringstream ss(s);
     while (ss >> d)
        vd.push_back (d);
     //     for (int i = 0; i <int( vd.size())-1; ++i) //-1 because last one is the fitness
        //          p.x.push_back(vd[i]);
             }
     }
     //std::cout << s << std::endl;
               //for (int i=0; i <p.x.size(); i++)
                //cout << p.x[i] << endl;
         inFile.close();
         for (int i = 0; i <int( vd.size())-1; ++i) //-1 because last one is the fitness
                  p.x.push_back(vd[i]);

     a= a+1;
     }




typedef EA::Genetic<MySolution,MyMiddleCost> GA_Type;
typedef EA::GenerationType<MySolution,MyMiddleCost> Generation_Type;

void init_genes(MySolution& p,const std::function<double(void)> &rnd01)
{
	  if(level > 1)
	   {
	                   read_L1_ind(p);}

	        int len = genome_len;
	        for(int i=0;i<len;i++)
	                p.x.push_back(5.12*2.0*(rnd01()-0.5));
	        //std::cout << p.x.size() << std::endl;
	        //for(int i=0; i<p.x.size(); i++)
	        //cout << p.x[i] <<endl;

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
		c.cost_B = timer.toc()*10000000; //timi in microseconds
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
	//output_file<<"N"<<"\t"<<"Best Genes"<<"\t"<<"cost1"<<"\t"<<"cost2"<<"\n";
	std::vector<unsigned int> paretofront_indices=ga_obj.last_generation.fronts[0];
	for(unsigned int i:paretofront_indices)
	{
		const auto &X=ga_obj.last_generation.chromosomes[i];
		output_file
			<<i<<", "
			<<X.middle_costs.cost_A<<", "
			<<X.middle_costs.cost_B<<", "
			<<ga_obj.last_generation.chromosomes[i].genes.to_string()<<"\n";
		//	<<X.genes.y<<"\t"



	}
	output_file.close();
}

int main(int, char *argv[])
{

	level = atoi(argv[1]);
	total_level = atoi(argv[2]);
	genome_len = atoi(argv[5]);
	file_n = atoi(argv[7]);

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
	ga_obj.solve(level, total_level);

	std::cout<<"The problem is optimized in "<<timer.toc()<<" seconds."<<std::endl;

	save_results(ga_obj);
	return 0;
}
