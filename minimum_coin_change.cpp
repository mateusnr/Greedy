#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


std::vector<int> min_coin_change(int no_coins, const std::vector<int>& coins, int value)
{
	std::vector<int> answer;

	for (int i = no_coins - 1; i >= 0; i--)
	{
		// use the largest coin less than the current value
		while (value >= coins[i])
		{
			value -= coins[i];
			answer.push_back(coins[i]);
		}
	}

	return answer;
}

int main()
{
	int no_coins, value;
	std::cout << "Digite a quantidade de moedas: ";
	std::cin >> no_coins;

	std::vector<int> coins(no_coins);
	std::cout << "Digite os valores das moedas: ";
	for (int i = 0; i < no_coins; i++)
		std::cin >> coins[i];

	std::sort(coins.begin(), coins.end());

	std::cout << "Digite o valor desejado: ";
	std::cin >> value;

	std::vector<int> answer = min_coin_change(no_coins, coins, value);

	// the values given by the algorithm might not sum up to the expected value
	int sum_of_coins = std::accumulate(answer.begin(), answer.end(), 0);

	if (sum_of_coins != value or answer.size() == 0)
	{
		std::cout << "As moedas fornecidas nao sao o suficientes para chegar ao valor esperado\n";

	}
	else
	{
		std::cout << "As moedas necessarias sao: ";
		for (int coin : answer)
		{
			std::cout << coin << " ";
		}

		std::cout << "\n";
	}

}
