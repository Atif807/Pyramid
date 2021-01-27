/*
 * pyramid.h
 *
 *  Created on: 26 Jan 2021
 *      Author: atif
 */

#ifndef PYRAMID_PYRAMID_H_
#define PYRAMID_PYRAMID_H_

class Pyramid {

	int total_levels = 2;
	int genome_length = 30;
	int hyper_mutation = 0;

public:
	int get_total_levels();
	void set_total_levels(int l);

	int get_genome_length();
	void set_genome_length(int l);

	void set_hyper_mutation(int h);
	int get_hyper_mutation();


};


#endif /* PYRAMID_PYRAMID_H_ */
