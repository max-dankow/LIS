#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

void read_data(std::vector<int> &data, size_t &element_number)
{
    data.reserve(element_number);

    for (size_t i = 0; i < element_number; ++i)
    {
        int input_value;
        std::cin >> input_value;
        data.push_back(input_value);
    }
}

void count_LIS(std::vector<int> &index, const std::vector<int> &data,
               size_t element_number)
{
    std::vector<int> ending(element_number + 1, INT_MAX);
    std::vector<int> min_position(element_number + 1, INT_MAX);
    std::vector<int> previous(element_number, INT_MAX);

    index.clear();
    ending[0] = INT_MIN;
    previous[0] = INT_MAX;
    size_t max_index = 0;

    for (size_t i = 0; i < element_number; ++i)
    {
        size_t current_pos = (std::lower_bound(ending.begin(), ending.end(), data[i]) - ending.begin());

        if (ending[current_pos - 1] < data[i] && ending[current_pos] > data[i])
        {
            ending[current_pos] = data[i];
            min_position[current_pos] = i;

            if (ending[current_pos] > ending[max_index])
                max_index = current_pos;

            previous[i] = min_position[current_pos - 1];
        }
    }

    size_t i = min_position[max_index];
    while (i != INT_MAX)
    {
        index.push_back(data[i]);
        i = previous[i];
    }

    std::reverse(index.begin(), index.end());
}

void write_answer(const std::vector<int> &answer)
{
    for (auto result:answer)
    {
        std::cout << result << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t element_number;
    std::cin >> element_number;

    std::vector<int> data;
    read_data(data, element_number);

    std::vector<int> answer;

    count_LIS(answer, data, element_number);
    write_answer(answer);

    return 0;
}
