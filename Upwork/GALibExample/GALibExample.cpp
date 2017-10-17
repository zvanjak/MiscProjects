//#pragma warning(disable:4996)

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#include "ga/ga.h"

/*
1. Program reads some input parameters which are stored in a struct called test_input
2. The objective function fees this test_input struct into the conduct_analysis function and produces a result
3. Elements of the result struct are used to calculate FITNESS which gives a result for the objective function

The task at hand is to set up the optimisation inputs for this problem

I tried:
1. Define genome MyGenome which is a derived class from GAGenome
2. Define some code in mutation / cross / initialisation

What is needed:
1. Amend the code to correctly set up the optimisation problem for test_input variables. Each variable from test_input must be optimised with lower_bound and upper_bound being the bounded variable
2. Test each of the functions mutate, initialise and cross to ensure they compile correctly
3. test an .evolve() problem and print out results to console
4. some of the variables need to be rounded to a specific increment - to a multiple of variable round_factor. What is the way to implement this? i.e. should I optimise the multiple and then have a function which
translates this int x to an actually usable value by multiplying it by the rounding

i.e. say there is a value which needs to go in increments of 0.05 in the calculation of the fitness function

to optimise is i can optimise an int value and then multiply this int by 0.05 to create the actually usable value. How to do this?

*/

struct param_i
{ /// INT - OPTIMISABLE PARAMETER
	param_i()
	{
	}

	param_i(std::string n, int i, int LB, int UB, int R)
	{
		param_name = n;
		val_i = i;
		lower_bound = LB;
		upper_bound = UB;
		round_factor = R;
	}

	param_i(bool on_off, std::string n, int i, int LB, int UB, int R)
	{
		if (on_off == true)
		{
			param_name = n;
			val_i = i;
			lower_bound = LB;
			upper_bound = UB;
			round_factor = R;
		}
		if (on_off == false)
		{
			param_name = n;
			val_i = i;
			lower_bound = i;
			upper_bound = i;
			round_factor = R;
		}
	}

	void calc_rounded_param()
	{
		val_i_rounded = round_factor * val_i;
	}

	std::string param_name;
	int val_i;
	int val_i_rounded;
	int lower_bound;
	int upper_bound;
	int round_factor;
};


struct param_f
{ /// FLOAT -OPTIMISABLE PARAMETER
	param_f()
	{
	}

	param_f(std::string n, float f, float LB, float UB, float R)
	{
		param_name = n;
		val_f = f;
		lower_bound = LB;
		upper_bound = UB;
		round_factor = R;
	}

	param_f(bool on_off, std::string n, float f, float LB, float UB, float R)
	{
		if (on_off == true)
		{
			param_name = n;
			val_f = f;
			lower_bound = LB;
			upper_bound = UB;
			round_factor = R;
		}
		if (on_off == false)
		{
			param_name = n;
			val_f = f;
			lower_bound = f;
			upper_bound = f;
			round_factor = R;
		}
	}

	void calc_rounded_param()
	{
		val_f_rounded = round_factor * val_f;
	}

	std::string param_name;
	float val_f;
	float val_f_rounded;
	float lower_bound; /// LOWER CONSTRAINT
	float upper_bound; /// LOWER CONSTRAINT
	float round_factor; /// STEP - i.e. all values have to be rounded off to this value
};


struct param_d
{ /// FLOAT -OPTIMISABLE PARAMETER
	param_d()
	{
	}

	param_d(std::string n, double d, double LB, double UB, double R)
	{
		param_name = n;
		val_d = d;
		lower_bound = LB;
		upper_bound = UB;
		round_factor = R;
	}

	param_d(bool on_off, std::string n, double d, double LB, double UB, double R)
	{
		if (on_off == true)
		{
			param_name = n;
			val_d = d;
			lower_bound = LB;
			upper_bound = UB;
			round_factor = R;
		}
		if (on_off == false)
		{
			param_name = n;
			val_d = d;
			lower_bound = d;
			upper_bound = d;
			round_factor = R;
		} /// if off -- lower and upper bound are set to the variable value -- i.e. it is not optimised, always fixed
	}

	void calc_rounded_param()
	{
		val_d_rounded = round_factor * val_d;
	}

	std::string param_name;
	double val_d;
	double val_d_rounded;
	double lower_bound; /// LOWER CONSTRAINT
	double upper_bound; /// LOWER CONSTRAINT
	double round_factor; /// STEP - i.e. all values have to be rounded off to this value
};


struct param_b
{ /// BOOL - OPTIMISABLE PARAMETER
	param_b()
	{
	}

	param_b(std::string n, bool b)
	{
		param_name = n;
		val_b = b;
	}

	param_b(bool on_off, std::string n, bool b)
	{
		if (on_off == true)
		{
			param_name = n;
			val_b = b;
		}
		if (on_off == false)
		{
			param_name = n;
			val_b = b;
			lower_bound = b;
			upper_bound = b;
		}
	}

	std::string param_name;
	int val_b;
	bool lower_bound = false;
	bool upper_bound = true;
};


struct test_input_bucket_1
{
	int objective_function_id;		/// always fixed
	std::string chemical;			/// always fixed

	param_f param_1_RISK_PCT;		//= param("RISK_PCT", 0.5 , 0.25, 0.75);
	param_i param_2_PYR_BUCKETS;	//= param("PYR_BUCKETS",20 , 10, 40);
};


struct test_input_bucket_2
{
	double start_point;				/// always fixed
	double end_point;				/// always fixed

	param_b param_3_COST_ON_OFF;	//= param("COST_ON_OFF",false);
	param_d param_4_VOL;			//  = param("VOL",0.501, 0.251,0.751)
};

struct ga_input_atom
{
	int pop_sz = 50;
	double xover = 0.5;
	double np_mutation = 0.5;
	int generations = 100;
	int recordfreq = 10;
	int flushfreq = 10;
};

struct test_input
{
	test_input_bucket_1 INPUT_BUCKET_1;
	test_input_bucket_2 INPUT_BUCKET_2;
	ga_input_atom GA_INPUT;
};

struct test_result_atom
{
	double returns = 0.0;
	double stdev = 0.0;
};

namespace tester_methods
{
	test_result_atom conduct_analysis(test_input);
}

namespace load_and_set_settings
{
	test_input load_input_params();
	void set_GA_params(ga_input_atom INPUT, GASteadyStateGA& GA);
}

float Objective(GAGenome&);

/*
namespace objective_functions{
float objective_function_1(GAGenome &genome);  /// one of the parameters in test_input represents which objective function to use
float objective_function_2(GAGenome &genome);  /// one of the parameters in test_input represents which objective function to use
}
*/

/// CUSTOM GENOME SETUP BELOW

struct MyGenome : public GAGenome
{
	GADefineIdentity ("MyGenome",201);

	static void	Init(GAGenome&);
	static int	Mutate(GAGenome&, float);
	static float Compare(const GAGenome&, const GAGenome&);
	static float Evaluate(GAGenome&);
	static int Cross(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);

	int write(std::ostream & os) const;

	MyGenome()
	{
		initializer(Init);
		evaluator(Evaluate);
		crossover(Cross);
		mutator(Mutate);
		std::cout << "mutator == " << mutr << std::endl;
	}

	// we'll use values passed in T to initialize our variables for optimization
	MyGenome(test_input T)
	{
		// we have to create variables for our representation

		// first, the float and double values
		GABin2DecPhenotype map;

		// we have param_f and param_d
		float fVarLowBound = T.INPUT_BUCKET_1.param_1_RISK_PCT.lower_bound;
		float fVarUpperBound = T.INPUT_BUCKET_1.param_1_RISK_PCT.upper_bound;
		float fVarResolution = T.INPUT_BUCKET_1.param_1_RISK_PCT.round_factor;

		// we have to calculate number of bits for representing our float number; 
		int   fVarNumDistinctValues = (fVarUpperBound - fVarLowBound) / fVarResolution;			// how many distinc values we have?
		int	fVarNumBits = log2(fVarNumDistinctValues) + 1;
		
		map.add(fVarNumBits, fVarLowBound, fVarUpperBound);
		
		// we have one param_d
		double dVarLowBound = T.INPUT_BUCKET_2.param_4_VOL.lower_bound;
		double dVarUpperBound = T.INPUT_BUCKET_2.param_4_VOL.upper_bound;
		float dVarResolution = T.INPUT_BUCKET_2.param_4_VOL.round_factor;

		// again, calculation of number of bits for representing our float number; 
		int  dVarNumDistinctValues = (dVarUpperBound - dVarLowBound) / dVarResolution;			// how many distinc values we have?
		int	dVarNumBits = log2(dVarNumDistinctValues) + 1;
		map.add(dVarNumBits, dVarLowBound, dVarUpperBound);

		// and finally, one param_n
		// generally, integers are kind of "hard" for genetic algorithms, unless the range of the variable is multiply of 2 (ie. 15, or 64), in which case translation to binary representation is easy :)
		// here, and following your lead about possibility of all variables being floats, I will just approx with another float variable
		int nVarLowBound = T.INPUT_BUCKET_1.param_2_PYR_BUCKETS.lower_bound;
		int nVarUpperBound = T.INPUT_BUCKET_1.param_2_PYR_BUCKETS.upper_bound;

		int  nVarNumDistinctValues = (nVarUpperBound - nVarLowBound);			
		int	nVarNumBits = log2(dVarNumDistinctValues) + 1;
		map.add(nVarNumBits, nVarLowBound, nVarUpperBound);

		floatVal = new GABin2DecGenome(map);

		// four our single boolean var, we are going to use standard binary representation
		// we have a single bool variable, so length is 1
		boolVars = new GA1DBinaryStringGenome(1);

		initializer(Init);
		evaluator(Evaluate);
		crossover(Cross);
		mutator(Mutate);
		std::cout << "in parametrised constructor == " << mutr << std::endl;
	}

	// modified copy ctor to call copy ctor on memeber variables for representation
	MyGenome(const MyGenome& orig)
	{
		floatVal = new GABin2DecGenome(*orig.floatVal);
		boolVars = new GA1DBinaryStringGenome(*orig.boolVars);
		copy(orig);
	}

	virtual ~MyGenome()
	{
		delete floatVal;
		delete boolVars;
	}

	MyGenome& operator=(const GAGenome& orig)
	{
		if (&orig != this) copy(orig);
		return *this;
	}

	int MyGenome::equal(const GAGenome& g) const
	{
		MyGenome& genome = (MyGenome&)g;
		return ((*floatVal == *genome.floatVal) && (*boolVars== *genome.boolVars));
	}

	virtual GAGenome* clone(CloneMethod) const
	{
		return new MyGenome(*this);
	}

	virtual void copy(const GAGenome& c)
	{
		if (&c != this && sameClass(c)) {
			GAGenome::copy(c);
			MyGenome & bc = (MyGenome &)c;
			floatVal->copy(*(bc.floatVal));
			boolVars->copy(*(bc.boolVars));
		}
	}

	GABin2DecGenome			*floatVal;		// we'll use this for both float and double and integer vars

	GA1DBinaryStringGenome	*boolVars;	// this will hold values for ALL the boolean variables for optimization
};

void MyGenome::Init(GAGenome& G)
{
	/// THIS SHOULD TAKE INTO ACCOUNT THE test_input INPUT and declare its default parameters
	// nope, it is already handled in ctor, during construction of representation objects

	MyGenome& g = (MyGenome &)G;
	//    G.INPUT_BUCKET_1.param_1_RISK_PCT.calc_rounded_param();

	g.floatVal->initialize();
	g.boolVars->initialize();
	g._evaluated = gaFalse;
}

int MyGenome::write(std::ostream & os) const 
{
	os << "input 1 param 1 (RISK PCT) " << floatVal->phenotype(0) << "\n";
	os << "input 1 param 2 (PYR_BUCKETS)" << floatVal->phenotype(2) << "\n";
	os << "input 2 param 3 (COST_ON OFF) " << boolVars->gene(0) << "\n";
	os << "input 2 param 4  (VOL) " << floatVal->phenotype(1) << "\n";

	return os.fail() ? 1 : 0;
}

int MyGenome::Mutate(GAGenome& G, float pmut)
{
	MyGenome& child = (MyGenome &)G;

	// we'll perform mutation by performing mutation of constituent parts of our genome
	int nmut = child.floatVal->mutate(pmut) + child.boolVars->mutate(pmut);
	if (nmut) child._evaluated = gaFalse;
	return nmut;
}

float MyGenome::Compare(const GAGenome& p1, const GAGenome& p2)
{
	MyGenome& sis = (MyGenome &)p1;
	MyGenome& bro = (MyGenome &)p2;
	return 0.5 * (sis.floatVal->compare(bro) + sis.boolVars->compare(bro));
}

float MyGenome::Evaluate(GAGenome& G)
{
	/* your evaluation here */
	MyGenome& g = (MyGenome &)G;
	
	/// EVALUATE - should collect parameters into an test_input struct and feed them into conduct analysis function
	test_input INPUT;

	// we transfer values from our representation to test_input structure, for objective function evaluation
	INPUT.INPUT_BUCKET_1.param_1_RISK_PCT.val_f = g.floatVal->phenotype(0);
	INPUT.INPUT_BUCKET_2.param_4_VOL.val_d = g.floatVal->phenotype(1);
	INPUT.INPUT_BUCKET_1.param_2_PYR_BUCKETS.val_i = (int)g.floatVal->phenotype(2);	// we have to cast this to int
	INPUT.INPUT_BUCKET_2.param_3_COST_ON_OFF.val_b = g.boolVars->gene(0);

	test_result_atom RESULT = tester_methods::conduct_analysis(INPUT);

	float FITNESS = RESULT.returns * RESULT.stdev;
	return FITNESS;
}


int MyGenome::Cross(const GAGenome& p1, const GAGenome& p2, GAGenome* c1, GAGenome* c2)
{
	// oimplementation of sexual crossover
	MyGenome& mom = (MyGenome&)p1;
	MyGenome& dad = (MyGenome&)p2;
	int n = 0;

	GAGenome::SexualCrossover strcross = mom.floatVal->sexual();
	GAGenome::SexualCrossover b2dcross = mom.boolVars->sexual();

	if (c1 && c2) {
		MyGenome& sis = (MyGenome&)*c1;
		MyGenome& bro = (MyGenome&)*c2;
		
		(*strcross)(*mom.floatVal, *dad.floatVal, sis.floatVal, bro.floatVal);
		(*b2dcross)(*mom.boolVars, *dad.boolVars, sis.boolVars, bro.boolVars);
		
		sis._evaluated = gaFalse;
		bro._evaluated = gaFalse;
		
		n = 2;
	}
	else if (c1) {
		MyGenome& sis = (MyGenome&)*c1;

		(*strcross)(*mom.floatVal, *dad.floatVal, sis.floatVal, 0);
		(*b2dcross)(*mom.boolVars, *dad.boolVars, sis.boolVars, 0);

		sis._evaluated = gaFalse;

		n = 1;
	}
	else if (c2) {
		MyGenome& bro = (MyGenome&)*c2;

		(*strcross)(*mom.floatVal, *dad.floatVal, 0, bro.floatVal);
		(*b2dcross)(*mom.boolVars, *dad.boolVars, 0, bro.boolVars);

		bro._evaluated = gaFalse;

		n = 1;
	}

	return n;
}


int main()
{
	test_input INPUT = load_and_set_settings::load_input_params();

	MyGenome genome(INPUT); // test default constructor (if we have one)
	MyGenome genome2; // test default constructor (if we have one)
	std::cout << "genome after creation:\n" << genome << std::endl;

	genome.initialize(); // test the initializer
	std::cout << "genome after initialization:\n" << genome << std::endl;

	genome.mutate(0.01); /// GIVES COMPILATION ERROR
	std::cout << "genome after mutation:\n" << genome << std::endl;
	
	GASimpleGA ga(genome);
	GASigmaTruncationScaling scaling;

	int popsize = 50;
	int ngen = 100;
	float pmut = 0.01;
	float pcross = 0.6;

	ga.populationSize(popsize);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);
	ga.scaling(scaling);
	ga.scoreFrequency(10);
	ga.flushFrequency(50);
	ga.evolve(15);

	// Dump the results of the GA to the screen.

	genome = ga.statistics().bestIndividual();
	std::cout << "the ga found an optimum at the point: ";
	std::cout << genome << std::endl;

	return 0;
}


float Objective(MyGenome& g)
{
	test_input INPUT; /// need to figure out how to pass this with genome

	// we transfer values from our representation to test_input structure, for objective function evaluation
	INPUT.INPUT_BUCKET_1.param_1_RISK_PCT.val_f = g.floatVal->phenotype(0);
	INPUT.INPUT_BUCKET_2.param_4_VOL.val_d = g.floatVal->phenotype(1);
	INPUT.INPUT_BUCKET_1.param_2_PYR_BUCKETS.val_i = (int)g.floatVal->phenotype(2);	// we have to cast this to int
	INPUT.INPUT_BUCKET_2.param_3_COST_ON_OFF.val_b = g.boolVars->gene(0);

	test_result_atom RESULT = tester_methods::conduct_analysis(INPUT);
	float FITNESS = RESULT.returns * RESULT.stdev;
	return FITNESS;
}


test_result_atom tester_methods::conduct_analysis(test_input INP)
{
	test_result_atom RESULT;

	RESULT.returns = 0.10 + INP.INPUT_BUCKET_1.param_1_RISK_PCT.val_f +
		INP.INPUT_BUCKET_1.param_2_PYR_BUCKETS.val_i +
		INP.INPUT_BUCKET_2.param_3_COST_ON_OFF.val_b +
		INP.INPUT_BUCKET_2.param_4_VOL.val_d; /// PLACEHOLDER CALCULATION

	RESULT.stdev = 0.05 + INP.INPUT_BUCKET_1.param_1_RISK_PCT.val_f +
		INP.INPUT_BUCKET_1.param_2_PYR_BUCKETS.val_i +
		INP.INPUT_BUCKET_2.param_3_COST_ON_OFF.val_b +
		INP.INPUT_BUCKET_2.param_4_VOL.val_d; /// PLACEHOLDER CALCULATION

	return RESULT;
}


test_input load_and_set_settings::load_input_params()
{
	test_input INPUT;

	INPUT.INPUT_BUCKET_1.objective_function_id = 1;
	INPUT.INPUT_BUCKET_1.chemical = "ABCDE";

	INPUT.INPUT_BUCKET_2.start_point = 1;
	INPUT.INPUT_BUCKET_2.end_point = 21;

	INPUT.GA_INPUT.pop_sz = 30;
	INPUT.GA_INPUT.xover = 0.7;
	INPUT.GA_INPUT.np_mutation = 0.01;
	INPUT.GA_INPUT.generations = 100;
	INPUT.GA_INPUT.recordfreq = 10;
	INPUT.GA_INPUT.flushfreq = 10;

	std::vector<bool> param_switches;
	param_switches.resize(4);

	param_switches[0] = true;
	param_switches[1] = true;
	param_switches[2] = true;
	param_switches[3] = true;

	INPUT.INPUT_BUCKET_1.param_1_RISK_PCT = param_f(param_switches[0], "RISK_PCT", 0.5, 0.25, 0.75, 0.05);
	INPUT.INPUT_BUCKET_1.param_2_PYR_BUCKETS = param_i(param_switches[1], "PYR_BUCKETS", 20, 10, 40, 5);

	INPUT.INPUT_BUCKET_2.param_3_COST_ON_OFF = param_b(param_switches[2], "COST_ON_OFF", false);
	INPUT.INPUT_BUCKET_2.param_4_VOL = param_d(param_switches[3], "VOL", 0.501, 0.251, 0.751, 0.001);

	return INPUT;
}
