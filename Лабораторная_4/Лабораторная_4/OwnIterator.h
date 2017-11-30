#pragma once
#include <string>
#include <memory>
#include "Container.h"

template<typename ValueType, typename Node>
class OwnIterator : public std::iterator<std::bidirectional_iterator_tag, ValueType> {

	friend class Container;

	OwnIterator(std::shared_ptr<Node> link) : link(link) {

	}

	std::shared_ptr<Node> link;

public:
	bool operator!=(OwnIterator const& other) const {
		return this->link != other.link;
	}

	bool operator==(OwnIterator const& other) const {
		return this->link == other.link;
	}

	OwnIterator& operator++() {
		if (link == nullptr) {
			throw std::string("Null pointer exeption");
		}
		link = link->next;
		return *this;
	}


	OwnIterator& operator--() {
		if (link == nullptr) {
			throw std::string("Null pointer exeption");
		}
		link = link->previous;
		return *this;
	}

	typename OwnIterator::reference operator*() const {
		if (link == nullptr || link->figure == nullptr) {
			throw std::string("Null pointer exeption");
		}
		return *link->figure;
	}

	// ~OwnIterator();
};