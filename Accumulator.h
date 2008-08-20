#ifndef _ACCUMULATOR_H_
#define _ACCUMULATOR_H_

#include <vector>
#include "Game.h"

template <typename S>
class Accumulator
{
private:
	int num;
	std::vector<S> previousStates;
public:
	explicit Accumulator(int n = 3) : num(0), previousStates(n) {}
	
	void restore(S& state, uint64_t frame)
	{
		uint64_t diff = Game::currentFrame() - frame;
		
		if (diff == 0)
		{
			rotate(previousStates.begin() + 1, previousStates.end(), previousStates.begin());
			previousStates[0] = state;
			if (num < previousStates.size())
				++num;
		}
		
		if (diff > num)
			diff = 0;
		
		if (num >= previousStates.size())
			state = previousStates[diff];
	}
};

#endif /* _ACCUMULATOR_H_ */
