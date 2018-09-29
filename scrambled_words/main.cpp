#include <vector>
#include <algorithm>
#include <string>
#include <fstream>


bool check(const std::string& dict_word, const std::string& word)
{
	std::string temp_dict = dict_word;
	std::string temp_word = word;

	if (temp_dict.length() != temp_word.length())	return false;

	//sort words from z to a
	std::sort(temp_dict.begin(), temp_dict.end(), [](char a, char b) {return a > b; });
	std::sort(temp_word.begin(), temp_word.end(), [](char a, char b) {return a > b; });

	if (temp_dict == temp_word)return true;

	return false;

}


int main()
{
	//load dictionary into a vector
	std::vector<std::string> dictionary;
	{
		std::ifstream file("dictionary.txt");
		std::string line;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				continue;
			}

			dictionary.push_back(line);
		}
		file.close();
	}

	//load scrambled words into a vector
	std::vector<std::string> scrambled_words;
	{
		std::ifstream file("scrambled-words.txt");
		std::string line;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				continue;
			}

			scrambled_words.push_back(line);
		}
		file.close();
	}

	//sort the scrambled words
	std::vector<std::string> result;
	for (const std::string& word : scrambled_words)
	{
		for (const std::string& dict_word : dictionary)
		{
			if (check(dict_word, word)) {
				result.push_back(dict_word);
				break;
			}
		}
	}

	//output the words to a file
	{
		std::ofstream file("result.txt");
		for (auto& word : result) file << word;

		file.close();
	}

	return 0;
}