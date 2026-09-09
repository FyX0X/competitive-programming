#include <iostream>
#include <vector>

int playerCount;
int queryCount;
std::vector<int> player_query;
std::vector<int> round_query;


void getInput();
std::pair<int, int> getOpponentsRange(int player, int round);

int main()
{
	getInput();

	for (size_t i = 0; i < queryCount; i++)
	{
		auto result = getOpponentsRange(player_query[i], round_query[i]);
		std::cout << result.first << " " << result.second << "\n";
	}
}



void getInput()
{
	// gets the input for the problem
	std::cin >> playerCount >> queryCount;
	player_query.resize(queryCount);
	round_query.resize(queryCount);

	for (size_t i = 0; i < queryCount; i++)
	{
		std::cin >> player_query[i] >> round_query[i];
	}


}

std::pair<int, int> getOpponentsRange(int player, int round)
{
	// at round R, # poss opponents = 2^R

	int opponentsCount = 1 << round - 1; // 2^round
	int playerIndex = (player - 1);		// convert to 0-based index

	int lowerBound = playerIndex >> round-1;
	lowerBound ^= 1;								// flip last bit to get opponent block
	lowerBound = lowerBound << round - 1;			// shift back filling with 0s
	int upperBound = lowerBound + opponentsCount - 1;
	return { lowerBound + 1, upperBound + 1 }; // convert back to 1-based index

}


