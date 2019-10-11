#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>

std::vector<std::pair<int, int>> interval_scheduling(const std::vector<std::pair<int, int>>& job_list)
{
	std::vector<std::pair<int, int>> schedule;

	int size = job_list.size();

	std::pair<int, int> last_job = *job_list.begin();

	// as the job list is already sorted, the first one always enters the list
	schedule.push_back(last_job);

	for (auto it = std::next(job_list.begin()); it != job_list.end(); it++)
	{
		/*
		 * If the job's start is greater or equal than the last one in the list,
		 * add to the answer
		 */

		if (it->first >= last_job.second)
		{
			schedule.push_back(*it);
			last_job = *it;
		}
	}

	return schedule;
}

int main()
{
	std::vector<std::pair<int, int>> job_list;
	int no_of_jobs;
	std::cout << "Digite a quantidade de tarefas: ";
	std::cin >> no_of_jobs;

	std::cout << "Insira o comeco e fim de uma tarefa, separado por espaco: \n";
	for (int i = 0; i < no_of_jobs; i++)
	{
		std::pair<int, int> aux;

		std::cin >> aux.first >> aux.second;

		job_list.push_back(aux);
	}

	// sorting by finish time (second element in the pair)
	std::sort(job_list.begin(), job_list.end(), [](auto& left, auto& right){
		return left.second < right.second; 
	});

	std::vector<std::pair<int, int>> schedule = interval_scheduling(job_list);

	std::cout << "O melhor agendamento de tarefas, com o comeco e fim, eh: \n";
	for (auto job : schedule)
	{
		std::cout << job.first << " " << job.second << "\n";
	}

}
