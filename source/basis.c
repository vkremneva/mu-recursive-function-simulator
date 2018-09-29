#include "basis.h"

bool Z(struct Arguments args) {return 0;}

int64_t S(int64_t x) {return x+1;}

int64_t P(int64_t k, int64_t m, int64_t *args) {
	if (k > m) {
		fprintf(stderr, "Incorrect argument: in P[k, m] k shoul be less than m\n");
		_Exit(1);
	}

	if (sizeof(args) < m) {
		fprintf(stderr, "Incorrect arguments: in P[k, m](x1, ..., xt) m = t\n"
				  "Here m = %lld, t=%i", m, sizeof(args));
		_Exit(1);
	}

	return args[k-1];
}

int64_t O(struct Function h, struct Operand g, struct Arguments arg){
	struct Arguments args_for_h;
	args_for_h.arity = g.arity;

	for (int i = 0; i < g.arity; i++)
		args_for_h.args[i] = evaluate(g.func[i], arg);

	return evaluate(h, args_for_h);
}

int64_t R(struct Function h, struct Function g, struct Arguments arg){
	if (arg.arity <= 1) {
		fprintf(stderr, "Error: Arity can't be 1 or less. Was %d.\n", arg.arity);
		_Exit(1);
	}

	int64_t arg0;
	struct Arguments step_arg, final_arg;

	if (arg.args[0] == 0) {
		step_arg.arity = arg.arity - (int8_t)1;
		for (int i = 0; i < step_arg.arity; i++)
			step_arg.args[i] = arg.args[i + 1];

		return evaluate(g, step_arg);
	} else {
		step_arg.arity = arg.arity;
		for (int i = 0; i < step_arg.arity; i++)
			step_arg.args[i] = arg.args[i];
		step_arg.args[0] -= 1;

		arg0 = R(h, g, step_arg);

		final_arg.arity = arg.arity + (int8_t)1;
		final_arg.args[0] = arg0;
		for (int i = 0; i < arg.arity; i++)
			final_arg.args[i+1] = arg.args[i];

		return evaluate(h, final_arg);
	}
}

int64_t M(struct Function g, struct Arguments arg) {
	struct Arguments new_arg;

	new_arg.arity = arg.arity;
	for (int i = 1; i < new_arg.arity; i++)
		new_arg.args[i] = arg.args[i];
	new_arg.args[0] = -1;

	do {
		new_arg.args[0]++;
	} while (evaluate(g, new_arg) != 0);

	return new_arg.args[0];
}