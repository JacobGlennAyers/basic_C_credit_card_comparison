#include <stdio.h>
#include <math.h>

float line_intersection_solver(float, float, float, float);
int generic_test_intersection();
int parallel_test_intersection();

void compound_interest_solver(float, float, float, float, float*, float*);
int monthly_compound_interest_test();
int daily_compound_interest_test();

void credit_card_interest_calculator(float, float, float, float, float, float*, float*);

int main(){
	
	// Testing 1 2 3 ...
	printf("Running Math Solver Tests!\n\n");
	if ( generic_test_intersection() && parallel_test_intersection() ){
		printf("Line Intersection tests have passed!\n");
	}
	
	if ( monthly_compound_interest_test() && daily_compound_interest_test() ){
		printf("Compound Interest tests have passed!\n");
	}
	
	// Question 1
	float AmEx_cashback = 0.05;
	float AmEx_annual = -695.0;
	float Visa_Flagship_cashback = 0.03;
	float Visa_Flagship_annual = -49.0;
	float travel_card_intersection = line_intersection_solver(AmEx_cashback, AmEx_annual,
																Visa_Flagship_cashback, Visa_Flagship_annual);
	printf("You will have to spend $%1.2f to benefit from American Express Platinum over Visa Flagship Rewards.\n", travel_card_intersection);
	
	// Question 2
	float principal_payment = 790.0;
	float Visa_Flagship_late_fee = 20.0;
	float other_late_fee = 40.0;
	float Visa_Flagship_APR = 0.18;
	float AmEx_Platinum_APR = 0.29;
	float WF_APR = 0.30;
	
	float Flagship_Total;
	float Flagship_Diff;
	credit_card_interest_calculator(principal_payment, Visa_Flagship_APR, 12, 1.0/4, 
									Visa_Flagship_late_fee, &Flagship_Total, &Flagship_Diff);
	printf("If you fail to pay your Flagship Rewards for 3 months with an initial balance of $%1.2f \nYou will end up paying an extra $%1.2f\n", principal_payment, Flagship_Diff);
	
	float AmEx_Total;
	float AmEx_Diff;
	credit_card_interest_calculator(principal_payment, AmEx_Platinum_APR, 12, 1.0/4, 
									other_late_fee, &AmEx_Total, &AmEx_Diff);
	printf("If you fail to pay your American Express Platinum for 3 months with an initial balance of $%1.2f \nYou will end up paying an extra $%1.2f\n", principal_payment, AmEx_Diff);
	
	float WF_Total;
	float WF_Diff;
	credit_card_interest_calculator(principal_payment, WF_APR, 12, 1.0/4, 
									other_late_fee, &WF_Total, &WF_Diff);
	printf("If you fail to pay your Active or Autograph card for 3 months with an initial balance of $%1.2f \nYou will end up paying an extra $%1.2f\n", principal_payment, WF_Diff);
	
	// Question 3
	float autograph_card_total;
	float autograph_diff;
	float autograph_principal = 400.0;
	credit_card_interest_calculator(autograph_principal, WF_APR, 12, 1.0/12, other_late_fee, &autograph_card_total, &autograph_diff);
	
	float makeup_rewards_payment = line_intersection_solver(0.03, 0, 0, autograph_diff);
	printf("You will have to spend $%1.2f to break even with the rewards in the 0.03 cashback category from your missed payment on $%1.2f that cost $%1.2f\n", 
			makeup_rewards_payment, autograph_principal, autograph_diff);
	
	return 0;
}

float line_intersection_solver(float m1, float b1, float m2, float b2){
	if (m1 == m2){
		printf("Parallel Lines do no intersect in Euclidean Space! Returning 0\n");
		return 0;
	}
	return (b2 - b1)/(m1 - m2);
}

int generic_test_intersection(){
	// Assume not passing until proven otherwise...
	int pass = 0;
	
	// Solution found via external testing...
	float solution = 10.0;
	
	float slope1 = 2.0;
	float y_intercept1 = -5;
	
	float slope2 = 1.0;
	float y_intercept2 = 5;
	
	if (solution == line_intersection_solver(slope1, y_intercept1, slope2, y_intercept2)){
		pass = 1;
	}
	
	return pass;
}

int parallel_test_intersection(){
	int pass = 0;
	
	float slope1 = 2.0;
	float y_intercept1 = -5;
	
	float slope2 = 2.0;
	float y_intercept2 = 5;
	
	if (0 == line_intersection_solver(slope1, y_intercept1, slope2, y_intercept2)){
		pass = 1;
	}
	return pass;
	
}

void compound_interest_solver(float principal_pay, float interest_rate, float application_rate, 
							  float time_period_count, float *final_amount, float *fee_payment){
	
	float base = ( 1 + (interest_rate/application_rate) );
	float exponent = time_period_count*application_rate;
	
	*final_amount = principal_pay*pow(base, exponent);
	*fee_payment = *final_amount - principal_pay;
}

int monthly_compound_interest_test(){
	int pass = 0;
	float P = 1000.0;
	float r = 0.35;
	float n = 12;
	float t = 2;
	// Ground Truth
	float A = 1993.6875;
	// Outputs
	float final_payment;
	float difference;
	compound_interest_solver(P, r, n, t, &final_payment, &difference);
	if ( (int) A == (int) final_payment ){
		pass = 1;
	}
	return pass;
}

int daily_compound_interest_test(){
	int pass = 0;
	float P = 1000.0;
	float r = 0.35;
	float n = 365;
	float t = 2;
	// Ground Truth
	float A = 2013.0774;
	// Outputs
	float final_payment;
	float difference;
	compound_interest_solver(P, r, n, t, &final_payment, &difference);
	if ((int) A == (int) final_payment){
		pass = 1;
	}
	return pass;
}

void credit_card_interest_calculator(float principal_pay, float interest_rate, float application_rate, 
									 float time_period_count, float late_fee, float *final_amount, float *fee_payment){
	// Works assuming a whole number number of months
	int month_count = application_rate * time_period_count;
	*final_amount = principal_pay;
	int cur_month;
	for (cur_month = 0; cur_month < month_count; cur_month++){
		compound_interest_solver(*final_amount, interest_rate, 12.0, 1.0/12, final_amount, fee_payment);
		*final_amount += late_fee;
	}
	*fee_payment = *final_amount - principal_pay;
}

