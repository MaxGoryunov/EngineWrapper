#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include <vector>

template<typename T, typename Fret, typename ...ArgTypes> 
class Wrapper {
private:
	using Arguments = std::unordered_map<std::string, std::variant<ArgTypes...>>;
	T* subject;
	Fret(T::*method)(ArgTypes...);
	Arguments arguments;
public:
	Wrapper(
		T* subject,
		Fret(T::* method)(ArgTypes...),
		Arguments arguments
	) : subject(subject), method(method), arguments(arguments) {}

	Fret execute(Arguments args) {
		int size = this->arguments.size();
		if (args.size() != this->arguments.size()) {
			throw std::invalid_argument("Incorrect number of arguments provided, given "
				+ args.size() + ", expected " + this->arguments.size()
			);
		}
		auto stored = this->arguments.begin();
		auto end = args.end();
		std::vector values(size);
		for (int i = 0; i < size; ++i) {
			auto found = args.find(stored->first);
			if (found == end) {
				throw std::invalid_argument("Argument "
					+ stored->first + " was not found in provided arguments"
				);
			}
			values[i] = found->second;
		}
	}
};