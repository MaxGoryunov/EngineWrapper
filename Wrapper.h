#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <variant>
#include <tuple>
#include <iterator>
#include <stdexcept>
#include <vector>

template<typename T, typename Fret, typename ...ArgTypes>
class Wrapper {
private:
	using Arguments = std::unordered_map<std::string, int>;
	T* subject;
	Fret(T::* method)(ArgTypes...);
	Arguments arguments;

	template<std::size_t ...I>
	Fret call(std::vector<int>& values, std::index_sequence<I...>) {
		return (this->subject->*(this->method))(std::forward<ArgTypes>(values[I])...);
	}
public:
	Wrapper(
		T* subject,
		Fret(T::* method)(ArgTypes...),
		Arguments const& arguments
	) : subject(subject), method(method), arguments(arguments) {}

	auto execute(Arguments const& args) {
		int size = this->arguments.size();
		if (args.size() != this->arguments.size()) {
			throw std::invalid_argument("Incorrect number of arguments provided");
		}
		auto stored = this->arguments.begin();
		std::vector<int> values(size);
		for (int i = 0; i < size; ++i) {
			auto found = args.find(stored->first);
			if (found == args.end()) {
				throw std::invalid_argument("Some argument was not found in provided parameters");
			}
			values[std::distance(this->arguments.begin(), stored)] = found->second;
			//values.push_back(found->second); // TODO check if error is here
			stored++;
		}
		return this->call(values, std::make_index_sequence<sizeof...(ArgTypes)>{});
	}
};
