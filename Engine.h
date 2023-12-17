#pragma once

#include <functional>
#include "Wrapper.h"

class Engine {
private:
	using Arguments = std::unordered_map<std::string, int>;
	std::unordered_map<std::string, std::function<int(Arguments const&)>> commands;
public:
	Engine() = default;

	template<typename T, typename ...ArgTypes>
	void register_command(Wrapper<T, ArgTypes...>* wrapper, std::string const& name) {
		this->commands[name] = [wrapper](Arguments const& arguments) {
			try {
				return wrapper->execute(arguments);
			}
			catch (std::exception& e) {
				throw std::runtime_error(e.what());
			}
		};
	}

	int execute(std::string const& name, Arguments const& arguments) {
		auto found = this->commands.find(name);
		if (found != this->commands.end()) {
			return (found->second)(arguments);
		}
		else {
			throw std::runtime_error(
				std::string("Requested command ") +
				name + std::string(" was not found")
			);
		}
	}
};