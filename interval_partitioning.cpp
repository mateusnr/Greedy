#include <iostream>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>

using job=std::pair<int, int>;

int interval_partitioning(std::vector<job> &job_list, std::map<int, std::vector<job>>& classrooms)
{
	// min heap to maintain finish times
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> p_queue;

	int rooms = 1;
	// we need to sort the job list by start time
	std::sort(job_list.begin(), job_list.end());

	p_queue.push({job_list[0].second, rooms});
	classrooms[rooms].push_back(job_list[0]);

	for (auto job = std::next(job_list.begin()); job != job_list.end(); job++)
	{
		int earliest_finish_time = p_queue.top().first;
		int curr_room = p_queue.top().second;
	
		if (job->first >= earliest_finish_time)
		{
			classrooms[curr_room].push_back(*job);	
			p_queue.pop();
			p_queue.push({job->second, curr_room});
		}
		else
		{
			rooms++;
			classrooms[rooms].push_back(*job);
			p_queue.push({job->second, rooms});
		}
	}


	return rooms;
}

int main()
{
	std::vector<job> job_list;
	std::map<int, std::vector<job>> classrooms;
	int no_jobs;

	std::cout << "Digite a quantidade de tarefas: ";
	std::cin >> no_jobs;

	std::cout << "Insira a entrada e saida das tarefas, separada por espaco:\n";
	for (int i = 0; i < no_jobs; i++)
	{
		std::pair<int, int> job;

		std::cin >> job.first >> job.second;

		job_list.push_back(job);
	}

	int answer = interval_partitioning(job_list, classrooms);
	std::cout << "Numero de salas necessarias: " << answer << "\n";

	std::cout << "\n";

	for (int i = 1; i <= classrooms.size(); i++)
	{
		std::cout << "Sala " << i << ":\n";
		for (auto job : classrooms[i])
		{
			std::cout << job.first << "->" << job.second << "\n";
		}

	}

	
}
